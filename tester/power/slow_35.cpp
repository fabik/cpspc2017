// Slow solution, but fits in memory, 35/100

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;

const int maxn = 200200;

struct point
{
    int x, y;
};

LL dist(point p1, point p2)
{
    LL x = p1.x - p2.x;
    LL y = p1.y - p2.y;
    return x*x + y*y;
}

point P[maxn];

vector<int> col;


bool dfs(int x, int n, LL s)
{
    bool ok = true;
    for(int y=0; y<n; y++)
    {
        if ((x==y) || (dist(P[x],P[y])>=s))
            continue;
        if (col[y]==col[x])
            return false;
        if (col[y]==-1)
        {
            col[y] = !col[x];
            ok &= dfs(y,n,s);
            if (!ok)
                return false;
        }
    }
    return ok;
}

bool check(int n, LL s)
{
    col.clear();
    col.resize(n,-1);
    bool ok = true;
    for(int i=0; i<n; i++)
        if (col[i]==-1)
        {
            col[i] = 0;
            ok &= dfs(i,n,s);
        }
    return ok;
}



int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d %d",&P[i].x, &P[i].y);
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
    assert(check(n,p));    
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
