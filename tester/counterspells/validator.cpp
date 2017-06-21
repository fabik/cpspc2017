#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define linf 1023456789123456789ll
#define pii pair<int,int>
#define pipii pair<int, pii >
#define pll pair<long long,long long>
#define vint vector<int>
#define vvint vector<vint >
#define ll long long
#define pdd pair<double, double>

//#define DEBUG
#ifdef DEBUG
#define db(x) cerr << #x << " = " << x << endl
#else
#define db(x)
#endif

int main()
{
	registerValidation();
	
	int n = inf.readInt(1, 200000, "n");
	inf.readEoln();
	for(int i=0; i<n; i++)
	{
		inf.readInt(0, i, "parent");
		inf.readEoln();
	}
	inf.readEof();	
	return 0;
}