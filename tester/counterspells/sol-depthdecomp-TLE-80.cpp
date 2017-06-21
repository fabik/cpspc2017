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

struct dd_path;

struct node
{
	node *parent, *heavy;
	vector<node*> sons;
	bool heavy_alive;
	bool black; //only applies to blocking/head nodes
	int maxdepth, depth;
	int black_light;
	dd_path* path;
	
	node()
	{
		parent = NULL;
		heavy = NULL;
		black = true;
		depth = 0;
		maxdepth = depth;
		black_light = 0;
		heavy_alive = false;
		path = NULL;
	}
	
	node(node* par)
	{
		parent = par;
		heavy = NULL;
		black = true;
		depth = parent->depth+1;
		maxdepth = depth;
		black_light = 0;
		heavy_alive = false;
		path = NULL;
		parent->sons.push_back(this);
	}
};

struct dd_path
{
	node* head;
	map<int, node*> blocking;
	
	bool get_color(node* n)
	{
		int d = n->depth;
		node *block = head;
		map<int, node*>::iterator it = blocking.lower_bound(-d);
		if(it != blocking.end())block = it->second;
		return (block->black) ^  ((n->depth - block->depth)%2);
	}
	
	int counter(node* whom)
	{
		bool color = get_color(whom);
		if(color)
		{
			return chain(whom);
		}
		return 0;
	}
	
	int counter_light(node* whom)
	{
		whom->black_light++;
		if(whom->black_light == 1 && whom->heavy_alive)
		{
			whom->heavy->black = get_color(whom->heavy);
			blocking[-whom->heavy->depth] = whom->heavy;
		}
		return counter(whom);
	}
	
	int counter_heavy(node* whom)
	{
		whom->heavy_alive = true;
		if(whom->black_light > 0)
		{
			blocking[-whom->heavy->depth] = whom->heavy;
		}
		return counter(whom);
	}
	
	int uncounter(node* whom)
	{
		bool black_heavy = 0;
		if(whom->heavy_alive) black_heavy = get_color(whom->heavy);
		whom->black_light--;
		if(whom->black_light == 0 && whom->heavy_alive)
		{
			blocking.erase(-whom->heavy->depth);
		}
		if(!black_heavy && (whom->black_light == 0))
		{
			return chain(whom);
		}
		return 0;
	}
	
	int chain(node* whom)
	{
		map<int, node*>::iterator it = blocking.lower_bound(-whom->depth);
		if(it != blocking.end())
		{
			it->second->black = !it->second->black;
			return whom->depth - it->second->depth + 1;
		}
		head->black = !head->black;
		int res = whom->depth - head->depth + 1;
		if(head->parent != NULL)
		{
			if(head->black)
			{
				res += head->parent->path->counter_light(head->parent);
			}
			else
			{
				res += head->parent->path->uncounter(head->parent);
			}
		}
		return res;
	}
	
	dd_path(node* h)
	{
		head = h;
	}
};

void dfs(node* cur)
{
	cur->maxdepth = cur->depth;
	for(int i=0; i<cur->sons.size(); i++)
	{
		dfs(cur->sons[i]);
		cur->maxdepth = max(cur->maxdepth, cur->sons[i]->maxdepth);
	}
}

void dd(node* n, dd_path* p, vector<dd_path*>& paths)
{
	if(p == NULL)
	{
		p = new dd_path(n);
		paths.push_back(p);
	}
	n->path = p;
	pair<int, node*> best(-1, NULL);
	for(int i=0; i<n->sons.size(); i++)
	{
		best = max(best, pair<int, node*>(n->sons[i]->maxdepth, n->sons[i]));
	}
	if(best.second != NULL) n->heavy = best.second;
	for(int i=0; i<n->sons.size(); i++)
	{
		if(n->sons[i] == best.second) dd(n->sons[i], p, paths);
		else dd(n->sons[i], NULL, paths);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	vector<dd_path*> paths;
	vector<node*> nodes;
	nodes.push_back(new node);
	vint par(n+1, -1);
	for(int i=1; i<=n; i++)
	{
		scanf("%d", &par[i]);
		nodes.push_back(new node(nodes[par[i]]));
	}
	dfs(nodes[0]);
	dd(nodes[0], NULL, paths);
	for(int i=1; i <= n; i++)
	{
		int res = 0;
		if(nodes[i]->path != nodes[i]->parent->path)
		{
			res = nodes[i]->parent->path->counter_light(nodes[i]->parent);
		}
		else
		{
			res = nodes[i]->path->counter_heavy(nodes[i]->parent);
		}
		printf("%d\n", res);
	}
	for(int i=0; i<=n; i++) delete nodes[i];
	for(int i=0; i<paths.size(); i++) delete paths[i];
	return 0;
}