# include <bits/stdc++.h>
using namespace std;
const int MN = 201;
vector <pair <int, char> > opening[MN];
vector <pair <int, char> > closing[MN];
char val[128];
typedef long long res_t;
res_t dp[MN][MN];
const res_t inf = 1e18;
set <pair <res_t, pair <int, int> > > dijkstra_queue;
void enque(int start, int end, res_t value) {
	if (dp[start][end] > value) {
		dijkstra_queue.erase(make_pair(dp[start][end], make_pair(start, end)));
		dp[start][end] = value;
		dijkstra_queue.insert(make_pair(dp[start][end], make_pair(start, end)));
	}
}
int main() {
	val['['] = 1;
	val[']'] = -1;
	val['{'] = 2;
	val['}'] = -2;
	val['('] = 3;
	val[')'] = -3;
	val['<'] = 4;
	val['>'] = -4;
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	fprintf(stderr, "n = %d m = %d\n", n, m);
	for (int i = 0; i < m; ++i) {
		int a, b;
		char c;
		scanf("%d%d %c", &a, &b, &c);
		c = val[(int)c];
		if (c > 0)
			opening[b].push_back(make_pair(a, c));
		else
			closing[a].push_back(make_pair(b, -c));
	}
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k)
			dp[i][k] = inf;
	for (int i = 1; i <= n; ++i)
		enque(i, i, 0);
	int turns = 0;
	while (dijkstra_queue.size()) {
		turns++;
		auto curr = *dijkstra_queue.begin();
		dijkstra_queue.erase(dijkstra_queue.begin());
		int start = curr.second.first, end = curr.second.second;
		assert(dp[start][end] < inf);
		for (int i = 1; i <= n; ++i) {
			enque(start, i, dp[start][end] + dp[end][i]);
			enque(i, end, dp[i][start] + dp[start][end]);
		}
		for (auto x : opening[start])
			for (auto y : closing[end]) {
				if (x.second == y.second)
					enque(x.first, y.first, dp[start][end] + 2);
			}
	}
	fprintf(stderr, "%d / %d turns\n", turns, n * n);
	if (dp[s][t] == inf) {
		printf("-1\n");
		fprintf(stderr, "-1\n");
	}
	else {
		printf("%lld\n", dp[s][t]);
		fprintf(stderr, "%lld = %.3Le\n", dp[s][t], (long double)dp[s][t]);
	}
}