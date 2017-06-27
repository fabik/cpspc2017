#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const LL infty = 3000*1000LL*1000*1000LL*1000*1000LL;

typedef pair<int,int> PI;

LL sq(int x)
{
    return x*(LL)x;
}

LL closest(vector<PI> &v, int p, int q)
{
//    fprintf(stderr,"%d %d\n",p,q);
    if (q==p)
        return infty;
    int s = (p+q)/2;
    LL d1 = closest(v,p,s);
    LL d2 = closest(v,s+1,q);
    LL d = min(d1,d2);
    vector<PI> w;
    for(int i=p; i<=q; i++)
        if (sq(v[i].first - v[s].first)<=d)
            w.push_back(PI(v[i].second,v[i].first));
    sort(w.begin(),w.end());
    for(int i=0; i<(int)w.size(); i++)
        for(int j=i+1; (j<(int)w.size()) && (j<=i+6); j++)
            d = min(d,sq(w[i].first-w[j].first)+sq(w[i].second-w[j].second));
    return d;
}

int main(int argc, char ** argv)
{
    int n;
    FILE* in = fopen(argv[1],"r");
    FILE* out = fopen(argv[3],"r");
    FILE *hint = fopen(argv[2],"r");
    fscanf(in,"%d",&n);
    vector<PI> A(n);
    for(int i=0; i<n; i++)
        fscanf(in,"%d %d",&A[i].first,&A[i].second);
//    sort(A.begin(),A.end());
    LL d,dh;
    fscanf(out,"%Ld",&d);
    vector<PI> B[2];
    fscanf(hint,"%Ld",&dh);
    if (dh!=d)
    {
        printf("0\n",d,dh);
        return 0;
    }    
    LL D = infty;
    for(int h=0; h<2; h++)
    {
        int s;
        fscanf(out,"%d",&s);
        for(int i=0; i<s; i++)
        {
            int k;
            fscanf(out,"%d",&k);
            B[h].push_back(A[k-1]);
        }
        sort(B[h].begin(),B[h].end());
        D = min(D,closest(B[h],0,s-1));
    }
    if (D<d)
    {
        printf("0\n",D,d);
        return 0;
    }
    printf("1\n");
}
