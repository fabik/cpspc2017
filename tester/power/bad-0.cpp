// Bad solution

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

const int maxn = 200200;

const int magic = 20;

struct point
{
    int x, y;
    int number;
};

bool operator<(point p1, point p2)
{
    return p1.x < p2.x;
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

bool check(int n, LL s)
{
    G.clear();
    G.resize(n);
    for(int i=0; i<n; i++)
        for(int j=max(0,i-magic); j<n && j<=i+magic ; j++)
            if (i!=j && dist(P[i],P[j])<s)
                G[i].push_back(j);
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



int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d",&P[i].x, &P[i].y);
        P[i].number = i+1;
    }
    sort(P,P+n);
    LL p = 1;
    LL q = 2e18+1;
    while(p<q)
    {
        int s = (p+q+1)/2;
        if (check(n,s))
            p = s;
        else
            q = s-1;
    }
    check(n,p);
   for(int i=0; i<n; i++)
        sort(G[i].begin(),G[i].end());
    
    vector<int> R[2];
    for(int i=0; i<n; i++)
        R[col[i]].push_back(P[i].number);
    
    printf("%Ld\n",p);
    for(int h=0; h<2; h++)
    {
        printf("%d\n",(int)R[h].size());
        for(int i=0; i<(int)R[h].size(); i++)
            printf((i ? " %d" : "%d"),R[h][i]);
        printf("\n");
    }
    
}
