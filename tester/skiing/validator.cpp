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

#define MIN_COOR -1000000000
#define MAX_COOR 1000000000

int main()
{
	registerValidation();
	
	int n = inf.readInt(0, 1000000, "n");
	inf.readEoln();
	int S_x, S_y, F_x, F_y;
	S_x = inf.readInt(MIN_COOR, MAX_COOR, "S_x");
	inf.readSpace();
	S_y = inf.readInt(MIN_COOR, MAX_COOR, "S_y");
	inf.readSpace();
	F_x = inf.readInt(MIN_COOR, MAX_COOR, "F_x");
	inf.readSpace();
	F_y = inf.readInt(MIN_COOR, MAX_COOR, "F_y");
	inf.readEoln();
	int cur_y = S_y;
	for(int i=0; i<n; i++)
	{
		int x1, x2, y;
		x1 = inf.readInt(MIN_COOR, MAX_COOR, "x1");
		inf.readSpace();
		x2 = inf.readInt(x1+1, MAX_COOR, "x2");
		inf.readSpace();
		y = inf.readInt(MIN_COOR, cur_y-1, "y");
		inf.readEoln();
		cur_y = y;
	}
	ensuref(F_y < cur_y, "finish must be under last gate");
	inf.readEof();	
	return 0;
}