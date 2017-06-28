#include <cstdio>
#include <algorithm>
#include <vector>
#include "oi.h"

using namespace std;

oi::Random RG;

const char* code = "ele";

typedef pair<int,int> PI;
typedef long long LL;

vector<PI> points;

void output(int number, const char * letter)
{
    char filename[32];
    sprintf(filename,"test/%02d.%s.in",number,letter);
    fprintf(stderr,"Generating %s...\n",filename);
    FILE * out = fopen(filename,"w");
    sort(points.begin(),points.end());
    points.erase(unique(points.begin(),points.end()),points.end());
    RG.randomShuffle(points.begin(),points.end());
    fprintf(out,"%d\n",(int)points.size());
    for(PI p : points)
        fprintf(out,"%d %d\n",p.first,p.second);
    fclose(out);
    points.clear();
}


void gen_random(int n, int range)
{
    for(int i=0; i<n; i++)
        points.push_back(PI(RG.rand()%range,RG.rand()%range));
}

void gen_cross(int n, int range)
{
    int k = (n-3)/4;
    range/=2;
    for(int i=0; i<k; i++)
    {
        points.push_back(PI(range,range+i*(LL)range/k));
        points.push_back(PI(range,range-i*(LL)range/k));
        points.push_back(PI(range+i*(LL)range/k,range));
        points.push_back(PI(range-i*(LL)range/k,range));
    }
    points.push_back(PI(range,range));
    points.push_back(PI(range+1,range+1));
    points.push_back(PI(range-1,range-1));
}

void gen_polygon(int n, int range)
{
    range /= 2;
    if (n%2==0)
        n--;
    long double pi = 3.14159265358979323846264338327950288;
    long double alpha = 2*pi/n;
    for(int i=0; i<n; i++)
        points.push_back(PI(range+range*cosl(i*alpha),range+range*sinl(i*alpha)));
}

void gen_special(int n, int range)
{
    range /= 2;
    n-=3;
    long double pi = 3.14159265358979323846264338327950288;
    long double alpha = 2*pi/n;
    for(int i=0; i<n; i++)
        points.push_back(PI(range+(range/2+i*(LL)range/2/n)*cosl(i*alpha),range+(range/2+i*(LL)range/2/n)*sinl(i*alpha)));
    int small = min(range/50,11000);
    points.push_back(PI(range,range));
    points.push_back(PI(range+small,range+small));
    points.push_back(PI(range-small,range-small));
}


void gen_regular(int n, int range)
{
    for(int i=1; i*i<n; i++)
        for(int j=1; j*j<n; j++)
            points.push_back(PI(i,j));
}

void gen_pairs(int n, int range)
{
    for(int i=0; i<n/2; i++)
    {
        int x = RG.rand()%range;
        int y = RG.rand()%range;
        int x2 = x, y2 = y;
        do
        {
            x2 = x + RG.rand()%10 - 5;
            y2 = y + RG.rand()%10 - 5;
        } while (x2<0 || y2<0 || x2>range || y2>range);
        points.push_back(PI(x,y));
        points.push_back(PI(x2,y2));
    }
}

const int TT = 3;

int sizes[TT] = {100, 2000, 100000};
int ranges[TT] = {1000, 40000, 1000000000};

int almost(int x)
{
    return x - RG.rand()%(x/10+1);
}

int main()
{
    for(int tt=1; tt<=TT; tt++)
    {
        RG.setSeed(13023+tt);
        int s = sizes[tt-1];
        int r = ranges[tt-1];
        gen_random(s,r);
        output(tt,"a");
        gen_random(almost(s),r);
        output(tt,"b");
        gen_random(almost(s),min(s,r));
        output(tt,"c");
        gen_cross(s,r);
        output(tt,"d");
        gen_polygon(s,r);
        output(tt,"e");
        gen_regular(s,r);
        output(tt,"f");
        gen_pairs(s,r);
        output(tt,"g");
        gen_random(s,r);
        output(tt,"h");
        gen_special(s,r);
        output(tt,"i");
    }
}
