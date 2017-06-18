#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXV = 200000;

long long sx, sy, dx, dy;

int v = 0, sv = -1, dv = -1;
vector<int> adj[MAXV];
long long xx[MAXV];
long long yy[MAXV];
long long size[MAXV];
bool white[MAXV];
bool visited[MAXV];

const char* rec(
	long long x, long long y, long long n, const char *p,
	deque<int>& top, deque<int>& left, deque<int>& bottom, deque<int>& right
) {
	char c = *p++;

	if (c == 'B' || c == 'W') {
		if (sx >= x && sx < x + n && sy >= y && sy < y + n) {
			assert(sv == -1);
			sv = v;
		}

		if (dx >= x && dx < x + n && dy >= y && dy < y + n) {
			assert(dv == -1);
			dv = v;
		}

		xx[v] = x;
		yy[v] = y;
		size[v] = n;
		white[v] = c == 'W';

		while (!top.empty() && xx[top.front()] < x + n) {
			adj[v].push_back(top.front());
			adj[top.front()].push_back(v);
			if (xx[top.front()] + size[top.front()] > x + n) break;
			top.pop_front();
		}

		while (!left.empty() && yy[left.front()] < y + n) {
			adj[v].push_back(left.front());
			adj[left.front()].push_back(v);
			if (yy[left.front()] + size[left.front()] > y + n) break;
			left.pop_front();
		}

		bottom.push_back(v);
		right.push_back(v);
		v++;
		return p;
	}

	assert(c == '(');
	assert(n >= 2);

	deque<int> midh, midv;
	p = rec(x, y, n / 2, p, top, left, midh, midv);
	p = rec(x + n / 2, y, n / 2, p, top, midv, midh, right);
	p = rec(x, y + n / 2, n / 2, p, midh, left, bottom, midv);
	p = rec(x + n / 2, y + n / 2, n / 2, p, midh, midv, bottom, right);
	assert(*p == ')');
	return p + 1;
}

int main() {
	long long n;
	string p;
	cin >> n >> p;
	assert(n >= 2 && n <= (1LL << 60));
	assert((n & (n - 1)) == 0); // n is power of two
	assert(p.length() >= 1 && p.length() <= 200000);

	cin >> sx >> sy >> dx >> dy;
	assert(sx >= 1 && sx <= n && sy >= 1 && sy <= n);
	assert(dx >= 1 && dx <= n && dy >= 1 && dy <= n);
	sx--; sy--; dx--; dy--;

	deque<int> top, left, bottom, right;
	int read = rec(0, 0, n, p.c_str(), top, left, bottom, right) - p.c_str();
	assert(read == p.length());

	assert(sv != -1 && white[sv]);
	assert(dv != -1 && white[dv]);

	queue<int> q;
	q.push(sv);
	visited[sv] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == dv) break;
		for (int v : adj[u]) if (!visited[v] && white[v]) {
			q.push(v);
			visited[v] = true;
		}
	}
	printf("%s\n", visited[dv] ? "POSSIBLE" : "IMPOSSIBLE");
	return 0;
}
