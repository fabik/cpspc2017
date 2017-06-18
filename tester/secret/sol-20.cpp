#include <cassert>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int xx[4] = { -1, 1, 0, 0 };
const int yy[4] = { 0, 0, -1, 1 };

const int MAXN = 1024;

char grid[MAXN][MAXN];
bool visited[MAXN][MAXN];

const char* rec(int x, int y, int n, const char *p) {
	char c = *p++;
	if (c == 'B' || c == 'W') {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				grid[x + i][y + j] = c;
			}
		}
		return p;
	}
	assert(c == '(');
	assert(n >= 2);
	p = rec(x, y, n / 2, p);
	p = rec(x + n / 2, y, n / 2, p);
	p = rec(x, y + n / 2, n / 2, p);
	p = rec(x + n / 2, y + n / 2, n / 2, p);
	assert(*p == ')');
	return p + 1;
}

int main() {
	int n;
	string p;
	cin >> n >> p;
	assert(n >= 2 && n <= 1024);
	assert((n & (n - 1)) == 0); // n is power of two
	assert(p.length() >= 1 && p.length() <= 200000);
	int read = rec(0, 0, n, p.c_str()) - p.c_str();
	assert(read == p.length());

	long long sx, sy, dx, dy;
	cin >> sx >> sy >> dx >> dy;
	assert(sx >= 1 && sx <= n && sy >= 1 && sy <= n);
	assert(dx >= 1 && dx <= n && dy >= 1 && dy <= n);
	sx--; sy--; dx--; dy--;

	assert(grid[sx][sy] == 'W');
	assert(grid[dx][dy] == 'W');

	queue<pair<int, int>> q;
	q.push(make_pair(sx, sy));
	visited[sx][sy] = true;

	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		if (x == dx && y == dy) break;
		for (int i = 0; i < 4; i++) {
			int nx = x + xx[i], ny = y + yy[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < n
				&& grid[nx][ny] == 'W' && !visited[nx][ny]
			) {
				q.push(make_pair(nx, ny));
				visited[nx][ny] = true;
			}
		}
	}

	printf("%s\n", visited[dx][dy] ? "POSSIBLE" : "IMPOSSIBLE");
	return 0;
}
