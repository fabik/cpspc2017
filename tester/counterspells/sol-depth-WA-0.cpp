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
	int n;
	scanf("%d", &n);
	vint depth(1, 0);
	for(int i=1; i<=n; i++)
	{
		int p;
		scanf("%d", &p);
		depth.push_back(depth[p]+1);
		printf("%d\n", depth.back());
	}
	return 0;
}