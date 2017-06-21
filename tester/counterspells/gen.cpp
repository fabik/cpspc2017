//Generate inputs for task counterspells.
//Reads parameters from stdin (NOT as arguments).
//Parameters are: TYPE SEED N [type-specific], where
//TYPE defines tree type and is one of:
// 0 -- each new node is added under a random parent. Has fourth
//      parameter MAX_DEPTH specifying maximum allowed tree depth
// 1 -- a deep tree (basically a path with occasional stray branches).
//      Has fourth parameter STRAY_CHANCE specifying probability of
//      branching.
// 2 -- a balaneced binary tree
// 3 -- a star
// 4 -- a tree of depth 2, each son of root has at most one child
// 5 -- a bad case for maximum-depth path decomposition based solution
// 6 -- a bad case for solutions updating all blocking nodes. Has a fourth
//      parameter STRAY_CHANCE
//SEED is seed for the RNG.
//N is N defined in problem statement.

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

#define MANY 16777216

bool with_chance(double p)
{
	return (rand() % MANY) < p*MANY;
}

void random_parent(int n, int max_depth)
{
	vector<int> depth(n+1, 0);
	for(int i=1; i<=n; i++)
	{
		int parent;
		do
		{
			parent = rand()%i;
		} while(depth[parent] >= max_depth);
		printf("%d\n", parent);
		depth[i] = depth[parent]+1;
	}
}

void deep(int n, double stray_chance)
{
	int head = 0, stray_head = -1;
	for(int i=1; i<=n; i++)
	{
		if(with_chance(stray_chance))
		{
			if(stray_head == -1)
			{
				printf("%d\n", rand()%i);
				stray_head = i;
			}
			else
			{
				printf("%d\n", stray_head);
				stray_head = -1;
			}
		}
		else
		{
			printf("%d\n", head);
			head = i;
		}
	}
}

void balanced(int n)
{
	for(int i=1; i<=n; i++) printf("%d\n", (i-1)/2);
}

void star(int n)
{
	for(int i=1; i<=n; i++) printf("0\n");
}

void two_layers(int n)
{
	vector<int> uncountered;
	for(int i=1; i<=n; i++)
	{
		if(uncountered.size() > 1 || (uncountered.size() == 1 && with_chance(0.5)))
		{
			int id = rand()%uncountered.size();
			swap(uncountered[id], uncountered.back());
			printf("%d\n", uncountered.back());
			uncountered.pop_back();
		}
		else
		{
			printf("0\n");
			uncountered.push_back(i);
		}
	}
}

void staircase_tree(int n)
{
	int main_head = 0;
	vint heads(1, 0);
	for(int i=1; i<=n; i++)
	{
		for(int pass=0; pass<2; pass++)
		{
			for(int j=0; i<=n && j<heads.size(); j++)
			{
				printf("%d\n", heads[j]);
				heads[j] = i;
				i++;
			}
		}
		if(i <= n)
		{
			printf("%d\n", main_head);
			main_head = i;
			heads.push_back(i);
		}
	}
}

void hairy_bamboo(int n, double stray_chance)
{
	int major_head = 0, minor_head = 0, steps = 0;
	int stray_head = -1;
	vector<int> stray_points; 
	for(int i=1; i<=n; i++)
	{
		if(with_chance(stray_chance) && stray_points.size() > 0)
		{
			if(stray_head == -1)
			{
				printf("%d\n", stray_points[rand()%stray_points.size()]);
				stray_head = i;
			}
			else
			{
				printf("%d\n", stray_head);
				stray_head = -1;
			}
		}
		else
		{
			if(steps % 3 == 2)
			{
				printf("%d\n", major_head);
				major_head = i;
				stray_points.push_back(minor_head);
				minor_head = i;
			}
			else
			{
				printf("%d\n", minor_head);
				minor_head = i;
			}
			steps++;
		}
	}
}

int main()
{
	int type, seed, n;
	scanf("%d %d %d", &type, &seed, &n);
	srand(seed);
	printf("%d\n", n);
	switch(type)
	{
		case 0:
		{
			int max_depth;
			scanf("%d", &max_depth);
			random_parent(n, max_depth);
			break;
		}
		case 1:
		{
			double stray_chance;
			scanf("%lf", &stray_chance);
			deep(n, stray_chance);
			break;
		}
		case 2:
		{
			balanced(n);
			break;
		}
		case 3:
		{
			star(n);
			break;
		}
		case 4:
		{
			two_layers(n);
			break;
		}
		case 5:
		{
			staircase_tree(n);
			break;
		}
		case 6:
		{
			double stray_chance;
			scanf("%lf", &stray_chance);
			hairy_bamboo(n, stray_chance);
			break;
		}
	}
	return 0;
}