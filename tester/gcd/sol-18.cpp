# include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
	if (a == 0)
		return b;
	else
		return gcd(b % a, a);
}
const int MN = 20;
long long gcd_arr[1 << MN];
long long a[MN];
const long long inf = 1e18 + 44;
long long dp[1 << MN][MN + 1];
int main() {
	int n;
	scanf("%d", &n);
	assert(n <= MN);
	for (int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	gcd_arr[0] = 0;
	for (int mask = 1; mask < (1 << n); ++mask) {
		int i = __builtin_ctz(mask);
		assert((1 << i) == (mask & -mask));
		gcd_arr[mask] = gcd(a[i], gcd_arr[mask &~ (1 << i)]);
	}
	for (int mask = 0; mask < (1 << n); ++mask)
		for (int i = 0; i <= n; ++i)
			dp[mask][i] = -inf;
	dp[0][0] = 0;
	for (int mask = 1; mask < (1 << n); ++mask)
		for (int i = 1; i <= n; ++i) {
			assert(dp[mask][i] == -inf);
			for (int subset = mask; subset > 0; subset = (subset - 1) & mask) {
				assert(subset > 0);
				dp[mask][i] = max(dp[mask][i], dp[mask &~ subset][i - 1] + gcd_arr[subset]);
			}
		}
	for (int mask = 1; mask < (1 << n); ++mask)
		assert(dp[mask][1] == gcd_arr[mask]);
	for (int i = 1; i <= n; ++i)
		printf("%lld\n", dp[(1 << n) - 1][i]);
}