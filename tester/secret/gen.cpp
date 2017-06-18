#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };

struct Maze {
	int n, sx, sy, dir;
	long long sxx, syy;
	unique_ptr<Maze> inner;
	int tx, ty;
	vector<vector<bool>> white;
	vector<vector<int>> f;

	Maze(int n, int sx, int sy, int dir, long long sxx, long long syy, unique_ptr<Maze> inner)
		: n(n), sx(sx), sy(sy), dir(dir), sxx(sxx), syy(syy), inner(move(inner)),
		tx(-1), ty(-1), white(n, vector<bool>(n)), f(n, vector<int>(n))
	{
		assert((n & (n - 1)) == 0);
		assert(sx >= 0 && sx < n);
		assert(sy >= 0 && sy < n);
		assert(dir >= 0 && dir < 4);
	}

	bool inside(int x, int y) {
		return x >= 0 && x < n && y >= 0 && y < n;
	}

	void generate() {
		assert(inside(sx, sy));
		white[sx][sy] = true;

		int x = sx + dx[dir], y = sy + dy[dir];
		if (!inside(x, y)) {
			tx = sx;
			ty = sy;
			return;
		}
		white[x][y] = true;

		while (inside(x + dx[dir], y + dy[dir])) {
			int xx, yy;
			do {
				int d = rand() % 4;
				if (d == (dir ^ 1)) d = dir;
				xx = x + dx[d];
				yy = y + dy[d];
			} while (!inside(xx, yy));
			white[xx][yy] = true;
			x = xx;
			y = yy;
		}

		tx = x;
		ty = y;
	}

	void add_obstacle() {
		assert(!(tx == sx && ty == sy));
		white[tx][ty] = false;
	}

	void init_f() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f[i][j] = (i > 0 ? f[i - 1][j] : 0) + (j > 0 ? f[i][j - 1] : 0)
					- (i > 0 && j > 0 ? f[i - 1][j - 1] : 0) + white[i][j];
			}
		}
	}

	int square_sum(int x, int y, int k) {
		return f[x + k - 1][y + k - 1]
			- (x > 0 ? f[x - 1][y + k - 1] : 0)
			- (y > 0 ? f[x + k - 1][y - 1] : 0)
			+ (x > 0 && y > 0 ? f[x - 1][y - 1] : 0);
	}

	void write_square(stringstream& ss, int x, int y, int k, string& sp) {
		if (sx >= x && sx < x + k && sy >= y && sy < y + k) {
			if (k == 1 || (sp == "W" && square_sum(x, y, k) == k * k)) {
				ss << sp;
				return;
			}
		} else {
			int s = square_sum(x, y, k);
			if (s == 0) {
				ss << "B";
				return;
			}
			if (s == k * k) {
				ss << "W";
				return;
			}
		}

		ss << "(";
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				write_square(ss, x + j * k / 2, y + i * k / 2, k / 2, sp);
			}
		}
		ss << ")";
	}

	string to_string() {
		string sp = inner ? inner->to_string() : string("W");
		init_f();
		stringstream ss;
		write_square(ss, 0, 0, n, sp);
		return ss.str();
	}
};

unique_ptr<Maze> rec(int logn, int step, int dir, int obstacle_depth) {
	assert(logn >= 0);
	int k = min(logn, step);
	unique_ptr<Maze> inner = logn > k ? rec(logn - k, step, dir, obstacle_depth - 1) : unique_ptr<Maze>(nullptr);

	int n = 1 << k;
	int sx = rand() % n;
	int sy = rand() % n;

	if (obstacle_depth == 0) {
		if (sx + dx[dir] < 0 || sx + dx[dir] >= n || sy + dy[dir] < 0 || sy + dy[dir] >= n) {
			sx -= dx[dir];
			sy -= dy[dir];
		}
	}

	long long sxx = (((long long) sx) << (logn - k)) + (inner ? inner->sxx : 0);
	long long syy = (((long long) sy) << (logn - k)) + (inner ? inner->syy : 0);
	unique_ptr<Maze> maze(new Maze(n, sx, sy, dir, sxx, syy, move(inner)));
	maze->generate();
	if (obstacle_depth == 0) {
		maze->add_obstacle();
	}
	return maze;
}

string gen(int logn, int step, bool ans, long long& sx, long long& sy, long long& tx, long long& ty) {
	int obstacle_depth = rand() % ((logn - 1) / step);
	if (ans) obstacle_depth = -1;
	unique_ptr<Maze> begin = rec(logn - 1, step, 3, obstacle_depth);
	unique_ptr<Maze> end = rec(logn - 1, step, 0, -1);

	sx = begin->sxx;
	sy = begin->syy;
	tx = (1LL << (logn - 1)) + end->sxx;
	ty = (1LL << (logn - 1)) + end->syy;

	stringstream ss;
	ss << "(";
	ss << begin->to_string();
	ss << "WB";
	ss << end->to_string();
	ss << ")";
	return ss.str();
}

int main(int argc, char **argv) {
	if (argc < 5) {
		fprintf(stderr, "Usage: ./gen <log-n> <step> <ans> <seed>\n");
		return 1;
	}

	int logn = atoi(argv[1]);
	int step = atoi(argv[2]);
	bool ans = (bool) atoi(argv[3]);
	int seed = atoi(argv[4]);

	assert(logn >= 3 && logn <= 60);
	assert(step >= 2 && step <= min(12, logn - 1));

	srand(seed);
	long long n = 1LL << logn;
	long long sx, sy, tx, ty;
	string p = gen(logn, step, ans, sx, sy, tx, ty);
	assert(p.length() <= 200000);

	printf("%lld\n", n);
	printf("%s\n", p.c_str());
	printf("%lld %lld\n", sx + 1, sy + 1);
	printf("%lld %lld\n", tx + 1, ty + 1);
	return 0;
}
