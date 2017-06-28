# include <bits/stdc++.h>
using namespace std;
const int MN = 201;
vector <pair <int, char> > opening[MN], closing[MN];
typedef long long res_t;
char val[128];
const res_t inf = 1e18;
//a, b, c, d --> dp[a][d] min= dp[b][c] + 2
//-1 i, k, l --> dp[i][k] min= dp[i][j] + dp[j][k]
struct rule {
	int a, b, c, d;
	rule(int a_, int b_, int c_, int d_) : a(a_), b(b_), c(c_), d(d_) {}
};
vector <rule> rules;
res_t dp[MN][MN];
int main() {
	val['('] = 1;
	val[')'] = -1;
	val['<'] = 2;
	val['>'] = -2;
	val['['] = 3;
	val[']'] = -3;
	val['{'] = 4;
	val['}'] = -4;
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 0; i < m; ++i) {
		int x, y;
		char c;
		scanf("%d%d %c", &x, &y, &c);
		c = val[(int)c];
		if (c > 0)
			opening[x].push_back(make_pair(y, c));
		else
			closing[x].push_back(make_pair(y, -c));
	}
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k)
			dp[i][k] = inf;
	for (int i = 1; i <= n; ++i)
		dp[i][i] = 0;
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k) 
			for (auto x : opening[i])
				for (auto y : closing[k])
					if (x.second == y.second)
						rules.emplace_back(i, x.first, k, y.first);
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= n; ++k)
			for (int l = 1; l <= n; ++l)
				rules.emplace_back(-1, i, k, l);
	random_shuffle(rules.begin(), rules.end());
	bool changed = true;
	while (changed) {
		changed = false;
		for (auto rule : rules) {
			if (rule.a == -1) {
				if (dp[rule.b][rule.d] > dp[rule.b][rule.c] + dp[rule.c][rule.d]) {
					dp[rule.b][rule.d] = dp[rule.b][rule.c] + dp[rule.c][rule.d];
					changed = true;
				}
			}
			else {
				if (dp[rule.a][rule.d] > dp[rule.b][rule.c] + 2) {
					dp[rule.a][rule.d] = dp[rule.b][rule.c] + 2;
					changed = true;
				}
			}
		}
	}
	if (dp[s][t] == inf)
		printf("-1\n");
	else
		printf("%lld\n", dp[s][t]);
}