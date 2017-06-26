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
#define pdd pair<long double, long double>

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

long double my_distance(vektor a, vektor b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

ll prod(vektor a, vektor b, vektor c) //b-a times c-a
{
	ll ux = b.x-a.x, uy = b.y-a.y;
	ll vx = c.x-a.x, vy = c.y-a.y;
	return ux*vy - vx*uy;
}

void add(vector<vektor>&where, vektor what)
{
	while(where.size() >= 2)
	{
		if(prod(where[where.size()-2], where.back(), what) == 0) where.pop_back();
		else break;
	}
	where.push_back(what);
}

int main()
{
	int n;
	scanf("%d", &n);
	int sx, sy, fx, fy;
	scanf("%d %d %d %d", &sx, &sy, &fx, &fy);
	vektor s(sx, sy), f(fx, fy);
	vector<vektor> left, right;
	vector<long double> ldist, rdist;
	vector<pii> lfrom, rfrom;
	left.push_back(s);
	right.push_back(s);
	ldist.push_back(linf*4.0);
	rdist.push_back(linf*4.0);
	lfrom.push_back(pii(-1,-1));
	rfrom.push_back(pii(-1,-1));
	for(int i=0; i<n; i++)
	{
		int x1, x2, y;
		scanf("%d %d %d", &x1, &x2, &y);
		left.push_back(vektor(x2, y));
		right.push_back(vektor(x1, y));
		ldist.push_back(linf*4.0);
		rdist.push_back(linf*4.0);
		lfrom.push_back(pii(-1,-1));
		rfrom.push_back(pii(-1,-1));
	}
	left.push_back(f);
	right.push_back(f);
	ldist.push_back(0);
	rdist.push_back(0);
	lfrom.push_back(pii(-1,-1));
	rfrom.push_back(pii(-1,-1));
	
	for(int i=left.size()-2; i>=0; i--)
	{
		vektor lbor = left[i+1], rbor = right[i+1];
		for(int j=i+1; j<left.size(); j++)
		{
			if(prod(left[i], left[j], lbor) >= 0)
			{
				lbor = left[j];
				if(prod(left[i], rbor, lbor) < 0)break;
				if(ldist[i] >= (ldist[j] + my_distance(left[i], left[j])))
				{
					ldist[i] = ldist[j] + my_distance(left[i], left[j]);
					lfrom[i] = pii(0, j);
				}
			}
			if(prod(left[i], right[j], rbor) <= 0)
			{
				rbor = right[j];
				if(prod(left[i], rbor, lbor) < 0)break;
				if(ldist[i] >= rdist[j] + my_distance(left[i], right[j]))
				{
					ldist[i] = rdist[j] + my_distance(left[i], right[j]);
					lfrom[i] = pii(1, j);
				}
			}
		}
		lbor = left[i+1], rbor = right[i+1];
		for(int j=i+1; j<right.size(); j++)
		{
			if(prod(right[i], left[j], lbor) >= 0)
			{
				lbor = left[j];
				if(prod(right[i], rbor, lbor) < 0)break;
				if(rdist[i] >= ldist[j] + my_distance(right[i], left[j]))
				{
					rdist[i] = ldist[j] + my_distance(right[i], left[j]);
					rfrom[i] = pii(0, j);
				}
			}
			if(prod(right[i], right[j], rbor) <= 0)
			{
				rbor = right[j];
				if(prod(right[i], rbor, lbor) < 0)break;
				if(rdist[i] >= rdist[j] + my_distance(right[i], right[j]))
				{
					rdist[i] = rdist[j] + my_distance(right[i], right[j]);
					rfrom[i] = pii(1, j);
				}
			}
		}
	}
	int cs = 0, ci = 0;
	vector<vektor> res;
	while(cs != -1)
	{
		if(cs == 0)
		{
			add(res, left[ci]);
			pii tmp = lfrom[ci];
			cs = tmp.first;
			ci = tmp.second;
		}
		else
		{
			add(res, right[ci]);
			pii tmp = rfrom[ci];
			cs = tmp.first;
			ci = tmp.second;
		}
	}
	
	printf("%d\n", res.size());
	for(int i=0; i<res.size(); i++)
	{
		res[i].print();
	}
	return 0;
}