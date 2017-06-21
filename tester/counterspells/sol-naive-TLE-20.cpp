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
	vvint son(1);
	vint parent(1, -1);
	vector<bool> active(1, true);
	for(int i=1; i<=n; i++)
	{
		int p;
		scanf("%d", &p);
		parent.push_back(p);
		son.push_back(vint(0));
		active.push_back(true);
		son[p].push_back(i);
		int count = 0;
		for(int cur = parent[i]; cur != -1; cur = parent[cur])
		{
			bool old = active[cur];
			active[cur] = true;
			for(int j=0; j<son[cur].size(); j++)
			{
				if(active[son[cur][j]])
				{
					active[cur] = false;
					break;
				}
			}
			if(active[cur] != old)count++;
			else break;
		}
		printf("%d\n", count);
	}
	return 0;
}