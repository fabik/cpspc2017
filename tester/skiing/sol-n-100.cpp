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

struct vektor
{
	ll x, y;
	vektor(ll xx, ll yy) : x(xx), y(yy)
	{
	}
	
	void print()
	{
		printf("%lld %lld\n", x, y);
	}
};

ll prod(vektor a, vektor b, vektor c) //b-a times c-a
{
	ll ux = b.x-a.x, uy = b.y-a.y;
	ll vx = c.x-a.x, vy = c.y-a.y;
	return ux*vy - vx*uy;
}

int main()
{
	int n;
	scanf("%d", &n);
	int sx, sy, fx, fy;
	scanf("%d %d %d %d", &sx, &sy, &fx, &fy);
	vektor s(sx, sy), f(fx, fy);
	vector<vektor> left, right;
	for(int i=0; i<n; i++)
	{
		int x1, x2, y;
		scanf("%d %d %d", &x1, &x2, &y);
		left.push_back(vektor(x2, y));
		right.push_back(vektor(x1, y));
	}
	left.push_back(f);
	right.push_back(f);
	vector<vektor> lenvelope, renvelope;
	lenvelope.push_back(s);
	renvelope.push_back(s);
	int leb = 0, reb = 0;
	vektor cur = s;
	vector<vektor> res;
	for(int i=0; i<left.size(); i++)
	{
		while(lenvelope.size() >= 2+leb)
		{
			if(prod(lenvelope[lenvelope.size()-2], lenvelope.back(), left[i]) <= 0)
			{
				lenvelope.pop_back();
			}
			else break;
		}
		lenvelope.push_back(left[i]);
		while(renvelope.size() >= 2+reb)
		{
			if(prod(renvelope[renvelope.size()-2], renvelope.back(), right[i]) >= 0)
			{
				renvelope.pop_back();
			}
			else break;
		}
		renvelope.push_back(right[i]);
		
		
		while(prod(cur, renvelope[reb+1], lenvelope[leb+1]) < 0)
		{
			res.push_back(cur);
			if(lenvelope[leb+1].y < renvelope[reb+1].y)
			{
				cur = renvelope[reb+1];
				reb++;
				lenvelope[leb] = cur;
			}
			else
			{
				cur = lenvelope[leb+1];
				leb++;
				renvelope[reb] = cur;
			}
		}
	}
	res.push_back(cur);
	res.push_back(f);
	printf("%d\n", res.size());
	for(int i=0; i<res.size(); i++)
	{
		res[i].print();
	}
	return 0;
}