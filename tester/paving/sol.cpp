#include <cassert>
#include <iostream>

using namespace std;

const int MAXNM = 100000;
const int md = 1000000007;

int parent[MAXNM*4];
int dfu_rank[MAXNM*4];

int get_root(int x) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = get_root(parent[x]);
}

void merge(int x, int y) {
	x = get_root(x);
	y = get_root(y);
	if (x != y) {
		if (dfu_rank[x] < dfu_rank[y]) {
			parent[x] = y;
		} else if (dfu_rank[y] < dfu_rank[x]) {
			parent[y] = x;
		} else {
			parent[x] = y;
			dfu_rank[y]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	assert(N >= 1 && N <= 100000);
	assert(M >= 1 && M <= 100000);
	assert(K >= 0 && K <= 100000);
	for (int i = 0; i < (N+M)*2; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < K; i++) {
		int r, c, g;
		cin >> r >> c >> g;
		assert(r >= 1 && r <= N);
		assert(c >= 1 && c <= M);
		assert(g == 0 || g == 1);
		r--; c--;
		if (g ^ ((r % 2 == 0) && (c % 2 == 0))) {
			merge(r, N+c);
			merge(N+M + r, N+M + N+c);
		} else {
			merge(r, N+M + N+c);
			merge(N+M + r, N+c);
		}
	}
	int sets_count = 0;
	for (int i = 0; i < N+M; i++) {
		if (get_root(i) == get_root(N+M + i)) {
			cout << 0 << endl;
			return 0;
		}
		if (parent[i] == i) {
			sets_count++;
		}
	}
	int ans = 1;
	for (int i = 0; i < sets_count - 1; i++) {
		ans = (ans * 2) % md;
	}
	cout << ans << endl;
	return 0;
}
