#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;


typedef pair<int,int> PI;
typedef long long LL;

const int maxn = 200200;


struct point
{
    int x, y;
    PI cell;
    int number;
};

bool operator<(point p1, point p2)
{
    return p1.cell<p2.cell;
}

LL dist(point p1, point p2)
{
    LL x = p1.x - p2.x;
    LL y = p1.y - p2.y;
    return x*x + y*y;
}

point P[maxn];

vector<vector<int>> G;
vector<int> col;


point pfc(PI c)
{
    point p;
    p.cell = c;
    return p;
}

bool dfs(int x)
{
    bool ok = true;
    for(int y : G[x])
    {
        if (col[y]==col[x])
            return false;
        if (col[y]==-1)
        {
            col[y] = !col[x];
            ok &= dfs(y);
            if (!ok)
                return false;
        }
    }
    return ok;
}

bool bipartite()
{
    int n = G.size();
    col.clear();
    col.resize(n,-1);
    bool ok = true;
    for(int i=0; i<n; i++)
        if (col[i]==-1)
        {
            col[i] = 0;
            ok &= dfs(i);
        }
    return ok;
}

bool check(int n, LL s)
{
    long double r = sqrtl(s);
    for(int i=0; i<n; i++)
    {
        P[i].cell.first = floorl(P[i].x/r);
        P[i].cell.second = floorl(P[i].y/r);
    }
    sort(P,P+n);
    int c = 1;
    for(int i=0; i<n; i++)
    {
        if (i==0 || P[i].cell!=P[i-1].cell)
            c = 1;
        else
            c++;
        if (c>6)
            return false;
    }
    G.clear();
    G.resize(n);
    for(int i=0; i<n; i++)
    {
        for(int cx = P[i].cell.first-1; cx <= P[i].cell.first+1; cx++)
            for(int cy = P[i].cell.second-1; cy <= P[i].cell.second+1; cy++)
            {
                int start = lower_bound(P,P+n,pfc(PI(cx,cy))) - P;
                for(int j = start; j<n && P[j].cell == PI(cx,cy); j++)
                    if (dist(P[i],P[j])<s && i!=j)
                        G[P[i].number].push_back(P[j].number);
            }
    }
    return bipartite();
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d",&P[i].x, &P[i].y);
        P[i].number = i;
    }
    LL p = 1;
    LL q = 2e18+1;
    while(p<q)
    {
        LL s = (p+q+1)/2;
        if (check(n,s))
            p = s;
        else
            q = s-1;
    }
    assert(check(n,p));
    for(int i=0; i<n; i++)
        sort(G[i].begin(),G[i].end());
    vector<int> R[2];
    for(int i=0; i<n; i++)
        R[col[i]].push_back(i);
    
    printf("%Ld\n",p);
    for(int h=0; h<2; h++)
    {
        printf("%d\n",(int)R[h].size());
        for(int i=0; i<(int)R[h].size(); i++)
            printf((i ? " %d" : "%d"),R[h][i]+1);
        printf("\n");
    }
}
