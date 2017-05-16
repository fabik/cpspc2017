#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int MAXNM = 5000;
const int md = 1000000007;

int N, M, K;
int colors[MAXNM][MAXNM];
int ans;

bool check() {
	for (int r = 0; r < N - 1; r++) {
		for (int c = 0; c < M - 1; c++) {
			if ((colors[r][c] ^ colors[r][c+1] ^ colors[r+1][c] ^ colors[r+1][c+1]) != 1) {
				return false;
			}
		}
	}
	return true;
}

void dfs(int r, int c) {
	if (c == M) {
		r++;
		c = 0;
	}
	if (r == N) {
		if (check()) {
			ans++;
			if (ans >= md) {
				ans -= md;
			}
		}
		return;
	}
	if (colors[r][c] == -1) {
		colors[r][c] = 0;
		dfs(r, c+1);
		colors[r][c] = 1;
		dfs(r, c+1);
		colors[r][c] = -1;
	} else {
		dfs(r, c+1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M >> K;
	assert(N >= 1 && N <= 100000);
	assert(M >= 1 && M <= 100000);
	assert(K >= 0 && K <= 100000);
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			colors[r][c] = -1;
		}
	}
	for (int i = 0; i < K; i++) {
		int r, c, g;
		cin >> r >> c >> g;
		assert(r >= 1 && r <= N);
		assert(c >= 1 && c <= M);
		assert(g == 0 || g == 1);
		r--; c--;
		colors[r][c] = g;
	}
	dfs(0, 0);
	cout << ans << endl;
	return 0;
}
