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
	vint parent(1, -1);
	vector<bool> active(1, true);
	vint active_children(1, 0);
	for(int i=1; i<=n; i++)
	{
		int p;
		scanf("%d", &p);
		parent.push_back(p);
		active.push_back(true);
		active_children.push_back(0);
		int count = 0;
		active_children[p]++;
		for(int cur = parent[i]; cur != -1; cur = parent[cur])
		{
			if(active[cur] && active_children[cur] > 0)
			{
				active[cur] = false;
				count++;
				if(parent[cur] != -1) active_children[parent[cur]]--;
				continue;
			}
			if(!active[cur] && active_children[cur] == 0)
			{
				active[cur] = true;
				count++;
				if(parent[cur] != -1) active_children[parent[cur]]++;
				continue;
			}
			break;
		}
		printf("%d\n", count);
	}
	return 0;
}