#include <bitset>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 1000;
const int MAXQ = 1000000;

int n, m, q;
bool empty[MAXN][MAXN];
bitset<MAXN> f[MAXN][MAXN], g[MAXN][MAXN];
int sr[MAXQ], sc[MAXQ], tr[MAXQ], tc[MAXQ];
bool ans[MAXQ];

void rec(int from, int to, const vector<int>& remain) {
	if (from > to) return;
	int mid = (from + to) / 2;
	for (int i = mid; i >= from; i--) {
		for (int j = m - 1; j >= 0; j--) {
			f[i][j] = 0;
			if (empty[i][j]) {
				if (i == mid) {
					f[i][j][j] = 1;
				} else {
					f[i][j] |= f[i + 1][j];
				}
				if (j != m - 1) {
					f[i][j] |= f[i][j + 1];
				}
			}
		}
	}
	for (int i = mid; i <= to; i++) {
		for (int j = 0; j < m; j++) {
			g[i][j] = 0;
			if (empty[i][j]) {
				if (i == mid) {
					g[i][j][j] = 1;
				} else {
					g[i][j] |= g[i - 1][j];
				}
				if (j != 0) {
					g[i][j] |= g[i][j - 1];
				}
			}
		}
	}
	vector<int> remain_left, remain_right;
	for (int i : remain) {
		if (tr[i] < mid) {
			remain_left.push_back(i);
		} else if (sr[i] > mid) {
			remain_right.push_back(i);
		} else {
			ans[i] = (f[sr[i]][sc[i]] & g[tr[i]][tc[i]]).any();
		}
	}
	rec(from, mid - 1, remain_left);
	rec(mid + 1, to, remain_right);
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
	vector<int> remain(q);
	for (int i = 0; i < q; i++) {
		cin >> sr[i] >> sc[i] >> tr[i] >> tc[i];
		assert(sr[i] >= 1 && sr[i] <= n);
		assert(sc[i] >= 1 && sc[i] <= m);
		assert(tr[i] >= 1 && tr[i] <= n);
		assert(tc[i] >= 1 && tc[i] <= m);
		sr[i]--; sc[i]--; tr[i]--; tc[i]--;
		assert(empty[sr[i]][sc[i]]);
		assert(empty[tr[i]][tc[i]]);
		remain[i] = i;
	}
	rec(0, n - 1, remain);
	for (int i = 0; i < q; i++) {
		printf("%s\n", ans[i] ? "YES" : "NO");
	}
	return 0;
}
