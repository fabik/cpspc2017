// Slow solution - O(n^2) with no logs, 35/100

#include <cstdio>
#include <algorithm>
#include <vector>
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

typedef pair<int,int> PI;

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

bool check(int n, vector<PI> &v, int s)
{
    col.clear();
    col.resize(n,-1);
    G.clear();
    G.resize(n);
    for(int i=0; i<s; i++)
    {
        G[v[i].first].push_back(v[i].second);
        G[v[i].second].push_back(v[i].first);
    }
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
        scanf("%d %d",&P[i].x, &P[i].y);
    vector<PI> v;
    for(int i=0; i<n; i++)
    {   vector<bool> used(n,false);
        for(int k=0; k<min(n-1,6); k++)
        {
            int b = -1;
            for(int j=0; j<n; j++)
                if (j!=i && !used[j] && (b==-1 || dist(P[i],P[j])<dist(P[i],P[b])))
                    b = j;
            used[b] = true;
            v.push_back(PI(i,b));
        }
    }
    fprintf(stderr,"%d\n",(int)v.size());
    sort(v.begin(),v.end(), [] (PI a, PI b) {return dist(P[a.first],P[a.second])<dist(P[b.first],P[b.second]); });
    LL p = 0;
    LL q = v.size()-1;
    while(p<q)
    {
        int s = (p+q+1)/2;
        if (check(n,v,s))
            p = s;
        else
            q = s-1;
    }
    check(n,v,p);
    vector<int> R[2];
    for(int i=0; i<n; i++)
        R[col[i]].push_back(i);
    
    printf("%Ld\n",dist(P[v[p].first],P[v[p].second]));
    for(int h=0; h<2; h++)
    {
        printf("%d\n",(int)R[h].size());
        for(int i=0; i<(int)R[h].size(); i++)
            printf((i ? " %d" : "%d"),R[h][i]+1);
        printf("\n");
    }
    
}
