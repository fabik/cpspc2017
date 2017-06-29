# define private public
# include <bitset>
# undef private
# include <type_traits>
# include <bits/stdc++.h>
using namespace std;
#define REP(x, n)     for(int x=0;x<(n);x++)

#define popcount __builtin_popcountl // l na końcu!!!

template <size_t rozmiar>
int tab_size(const bitset<rozmiar> & B) {
	return sizeof(B._M_w) / sizeof(B._M_w[0]);
}

template <size_t rozmiar>
int count(const bitset<rozmiar> &B) {
  int size = tab_size(B);
  int result = 0;
	REP(i, size)
		result += popcount(B._M_w[i]);
	return result;
}

const int MN = 1e5 + 1;
const int FRAME = 1 << 14;

bitset <FRAME> under1[MN], under2[MN];

vector <int> g1[MN], g2[MN];

void dfs(int x, vector <int> g[], bitset<FRAME> under[], int low) {
	for (auto y : g[x]) {
		dfs(y, g, under, low);
		under[x] |= under[y];
	}
	if (x >= low && x < low + FRAME)
		under[x][x - low] = 1;
}

void read(int n, vector <int> g[]) {
	for (int i = 2; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		g[x].push_back(i);
	}
}

int ans[MN];

int main() {
	int n;
	scanf("%d", &n);
	read(n, g1);
	read(n, g2);
	for (int low = 1; low <= n; low += FRAME) {
		if (low != 1)
			for (int i = 1; i <= n; ++i) {
				under1[i].reset();
				under2[i].reset();
			}
		dfs(1, g1, under1, low);
		dfs(1, g2, under2, low);
		for (int i = 1; i <= n; ++i) {
			ans[i] += count(under1[i] & under2[i]);
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i] - 1);
	printf("\n");
	return 0;
}
