#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

const int MAXN = 1000;

const int dr[2] = { 0, 1 };
const int dc[2] = { 1, 0 };

int n, m, q;
bool empty[MAXN][MAXN];
int age[MAXN][MAXN];
int now;

bool path_exists(int sr, int sc, int tr, int tc) {
	if (sr == tr && sc == tc) return true;
	now++;
	queue<pair<int, int>> q;
	q.emplace(sr, sc);
	age[sr][sc] = now;
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();
		if (r == tr && c == tc) break;
		for (int i = 0; i < 2; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (nr < n && nc < m && empty[nr][nc] && age[nr][nc] != now) {
				q.emplace(nr, nc);
				age[nr][nc] = now;
			}
		}
	}
	return age[tr][tc] == now;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> q;
	assert(n >= 1 && n <= 1000);
	assert(m >= 1 && m <= 1000);
	assert(q >= 1 && q <= 1000000);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		assert((int) s.length() == m);
		for (int j = 0; j < m; j++) {
			empty[i][j] = s[j] == '.';
		}
	}
	for (int i = 0; i < q; i++) {
		int sr, sc, tr, tc;
		cin >> sr >> sc >> tr >> tc;
		assert(sr >= 1 && sr <= n);
		assert(sc >= 1 && sc <= m);
		assert(tr >= 1 && tr <= n);
		assert(tc >= 1 && tc <= m);
		sr--; sc--; tr--; tc--;
		assert(empty[sr][sc]);
		assert(empty[tr][tc]);
		bool ans = path_exists(sr, sc, tr, tc);
		printf("%s\n", ans ? "YES" : "NO");
	}
	return 0;
}
