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

struct node
{
	int from, to;
	ll value;
	ll lazy;
	node *left, *right;
	bool am_leaf;
	
	node(int f, int t, ll v, node *l = NULL, node *r = NULL, ll laz = 0) : from(f), to(t), value(v), left(l), right(r), lazy(laz)
	{
		am_leaf = left == NULL;
	}
	
	ll get(int a, int b)
	{
		if(b <= from || a >= to) return 0;
		if(a <= from && b >= to) return value;
		ll length = min(b, to) - max(a, from);
		if(am_leaf) return value/(to-from) * length;
		return left->get(a, b) + right->get(a,b) + lazy * length;
	}
	
	node *add(int a, int b, ll val)
	{
		if(b <= from || a >= to) return this;
		if(a <= from && b >= to)
		{
			return new node(from, to, value+val*(to-from), left, right, lazy+val);
		}
		node *l = left->add(a, b, val);
		node *r = right->add(a, b, val);
		return new node(from, to, l->value+r->value+lazy*(to-from) , l, r, lazy);
	}
};

node *segtree(vector<int>& coors, int a, int b) //[]
{
	if(b - a == 1)
	{
		return new node(coors[a], coors[b], 0);
	}
	int mid = (a+b)/2;
	node *left = segtree(coors, a, mid);
	node *right = segtree(coors, mid, b);
	return new node(coors[a], coors[b], 0, left, right);
}

map<int, node*> current, cumulative;

ll sum_before(int x, int y1, int y2)
{
	node *cur_seg = current.lower_bound(x)->second;
	node *cum_seg = cumulative.lower_bound(x)->second;
	return cum_seg->get(y1, y2) + cur_seg->get(y1, y2)*x;
}

int main()
{
	int r, c, n, q;
	ll mod;
	scanf("%d %d %d %d %lld", &r, &c, &n, &q, &mod);
	vector<int> x1(n), y1(n), x2(n), y2(n);
	vector<pair<int, pii > > event;
	set<int> ys;
	int maxx = 0;
	for(int i=0; i<n; i++)
	{
		scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
		if(x1[i] > x2[i])swap(x1[i], x2[i]);
		if(y1[i] > y2[i])swap(y1[i], y2[i]);
		ys.insert(y1[i]);
		ys.insert(y2[i]);
		current[x1[i]] = NULL;
		current[x2[i]] = NULL;
		cumulative[x1[i]] = NULL;
		cumulative[x2[i]] = NULL;
		maxx = max(maxx, x2[i]);
		event.push_back(pipii(x1[i], pii(i, 1)));
		event.push_back(pipii(x2[i], pii(i, -1)));
	}
	vector<int> ysvec;
	for(set<int>::iterator it = ys.begin(); it != ys.end(); it++)
	{
		ysvec.push_back(*it);
	}
	node *ccur = segtree(ysvec, 0, ysvec.size()-1), *ccum = segtree(ysvec, 0, ysvec.size()-1);
	sort(event.begin(), event.end());
	for(int i=0; i<event.size(); i++)
	{
		int x = event[i].first, id = event[i].second.first, type = event[i].second.second;
		if(current[x] == NULL)
		{
			current[x] = ccur;
			cumulative[x] = ccum;
		}
		ccur = ccur->add(y1[id], y2[id], type);
		if(type == 1)
		{
			ccum = ccum->add(y1[id], y2[id], -x);
		}
		else
		{
			ccum = ccum->add(y1[id], y2[id], x);
		}
	}
	
	//queries incoming, brace yourselves
	ll l = 0;
	for(int i=0; i<q; i++)
	{
		int x1, y1, x2, y2;
		ll v;
		scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &v);
		x1 = (x1+(l%mod)*v)%mod;
		x2 = (x2+(l%mod)*v)%mod;
		y1 = (y1+(l%mod)*v)%mod;
		y2 = (y2+(l%mod)*v)%mod;
		if(x1 > x2)swap(x1, x2);
		if(y1 > y2)swap(y1, y2);
		x2 = min(x2, maxx);
		x1 = min(x1, maxx);
		l = sum_before(x2, y1, y2) - sum_before(x1, y1, y2);
		printf("%lld\n", l);
	}
	return 0;
}