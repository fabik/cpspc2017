#include <bits/stdc++.h>
using namespace std;

#define inf 1023456789
#define linf 1023456789123456789ll
#define pii pair<int,int>
#define pipii pair<int, pii >
#define pll pair<long long,long long>
#define vint vector<int>
#define vvint vector<vint >
#define ll long long
#define pdd pair<double, double>

#define DEBUG
#ifdef DEBUG
#define db(x) cerr << #x << " = " << x << endl
#else
#define db(x)
#endif

int main()
{
	int r, c, n, q;
	ll m;
	scanf("%d %d %d %d %lld", &r, &c, &n, &q, &m);
	vector<int> x1(n), y1(n), x2(n), y2(n);
	for(int i=0; i<n; i++)
	{
		scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
		if(x1[i] > x2[i]) swap(x1[i], x2[i]);
		if(y1[i] > y2[i]) swap(y1[i], y2[i]);
	}
	ll l = 0;
	for(int i=0; i<q; i++)
	{
		int xq1, yq1, xq2, yq2;
		ll v;
		scanf("%d %d %d %d %lld", &xq1, &yq1, &xq2, &yq2, &v);
		xq1 = (xq1 + l*v) % m;
		xq2 = (xq2 + l*v) % m;
		yq1 = (yq1 + l*v) % m;
		yq2 = (yq2 + l*v) % m;
		if(yq1 > yq2) swap(yq1, yq2);
		if(xq1 > xq2) swap(xq1, xq2);
		l = 0;
		for(int j=0; j<n; j++)
		{
			ll x_inter = max(0, min(x2[j], xq2) - max(x1[j], xq1));
			ll y_inter = max(0, min(y2[j], yq2) - max(y1[j], yq1));
			l += x_inter * y_inter;
		}
		printf("%lld\n", l);
		l %= m;
	}
	return 0;
}