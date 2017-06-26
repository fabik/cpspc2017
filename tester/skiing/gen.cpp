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

#define plpll pair<ll, pll >

#define MIN_COOR -1000000000
#define MAX_COOR 1000000000

//#define MIN_COOR -100
//#define MAX_COOR 100


ll long_rand()
{
	return rand() + (ll)(rand())*(ll)(RAND_MAX);
}

ll long_rand(ll low, ll high)
{
	return long_rand()%(high - low + 1) + low;
}

void random(int n)
{
	set<int, greater<int> > y;
	while(y.size() < n+2) y.insert(long_rand(MIN_COOR, MAX_COOR));
	printf("%d\n", n);
	printf("%d %d %d %d\n", (int)long_rand(MIN_COOR, MAX_COOR), *y.begin(), (int)long_rand(MIN_COOR, MAX_COOR), *y.rbegin());
	set<int>::iterator it = y.begin();
	it++;
	for(int i=0; i<n; i++)
	{
		int x1, x2;
		do
		{
			x1 = long_rand(MIN_COOR, MAX_COOR);
			x2 = long_rand(MIN_COOR, MAX_COOR);
		} while(x2 <= x1);
		printf("%d %d %d\n", x1, x2, *it);
		it++;
	}
}

void slalom(int n)
{
	set<int, greater<int> > y;
	while(y.size() < n+2) y.insert(long_rand(MIN_COOR, MAX_COOR));
	int S_x = long_rand(MIN_COOR+1, MAX_COOR-1), F_x = long_rand(MIN_COOR+1, MAX_COOR-1);
	printf("%d\n", n);
	printf("%d %d %d %d\n", S_x, *y.begin(), F_x, *y.rbegin());
	
	int small_x = min(S_x, F_x), big_x = max(S_x, F_x);
	bool type = rand()%2;
	set<int>::iterator it = y.begin();
	it++;
	for(int i=0; i<n; i++)
	{
		if(type)
		{
			printf("%d %d %d\n", MIN_COOR, (int)long_rand(MIN_COOR+1, small_x), *it);
		}
		else
		{
			printf("%d %d %d\n", (int)long_rand(big_x, MAX_COOR-1), MAX_COOR, *it);
		}
		type = !type;
		it++;
	}
}

void direct(int n)
{
	set<int, greater<int> > y;
	while(y.size() < n+2) y.insert(long_rand(MIN_COOR, MAX_COOR));
	int SF_x = long_rand(MIN_COOR+2, MAX_COOR-2);
	printf("%d\n", n);
	printf("%d %d %d %d\n", SF_x, *(y.begin()), SF_x, *(y.rbegin()));
	set<int>::iterator it = y.begin();
	it++;
	for(int i=0; i<n; i++)
	{
		int x1 = long_rand(MIN_COOR, SF_x-1);
		int x2 = long_rand(SF_x+1, MAX_COOR);
		printf("%d %d %d\n", x1, x2, *it);
		it++;
	}
}

void circle(int n)
{
	int S_y, step;
	step = rand() % (MAX_COOR - MIN_COOR)/(n+1) + 1;
	S_y = long_rand(MIN_COOR + (n+1)*step, MAX_COOR);
	double r = step * (n+1) / 2.0;
	double mid_y = S_y - r;
	int S_x = 0;
	printf("%d\n", n);
	printf("%d %d %d %d\n", S_x, S_y, S_x, S_y - (n+1)*step);
	int y = S_y;
	for(int i=0; i<n; i++)
	{
		y -= step;
		int x = sqrt(r*r - (y-mid_y)*(y-mid_y));
		printf("%d %d %d\n", -x, x, y);
	}
}

void circle_hull(int n)
{
	int S_y, step;
	step = rand() % (MAX_COOR - MIN_COOR)/(n+1) + 1;
	S_y = long_rand(MIN_COOR + (n+1)*step, MAX_COOR);
	double r = step * (n+1) / 2.0;
	double mid_y = S_y - r;
	int S_x = MIN_COOR;
	printf("%d\n", n);
	printf("%d %d %d %d\n", S_x, S_y, S_x, S_y - (n+1)*step);
	int y = S_y;
	for(int i=0; i<n; i++)
	{
		y -= step;
		int x = MIN_COOR + sqrt(r*r - (y-mid_y)*(y-mid_y));
		printf("%d %d %d\n", x, MAX_COOR, y);
	}
}

void random_hull(int n)
{
	set<int, greater<int> > y;
	while(y.size() < n+2) y.insert(long_rand(MIN_COOR, MAX_COOR));
	printf("%d\n", n);
	printf("%d %d %d %d\n", (int)long_rand(MIN_COOR, MAX_COOR), *y.begin(), (int)long_rand(MIN_COOR, MAX_COOR), *y.rbegin());
	set<int>::iterator it = y.begin();
	it++;
	for(int i=0; i<n; i++)
	{
		int x1, x2;
		do
		{
			x1 = MIN_COOR;
			x2 = long_rand(MIN_COOR+1, MAX_COOR);
		} while(x2 <= x1);
		printf("%d %d %d\n", x1, x2, *it);
		it++;
	}
}

void precision_exact()
{
	int count = long_rand(2, 10);
	ll dx = long_rand(0, (MAX_COOR - MIN_COOR) / count);
	ll dy = long_rand(0, (MAX_COOR - MIN_COOR) / count);
	dy *= -1;
	int S_y  = long_rand(MIN_COOR - count*dy, MAX_COOR);
	int F_y = S_y + count*dy;
	if(rand()%2)dx *= -1;
	int S_x = long_rand(max((ll)MIN_COOR, MIN_COOR-(ll)(count)*dx), min((ll)MAX_COOR, MAX_COOR-(ll)(count)*dx));
	int F_x = S_x + count*dx;
	printf("1\n");
	printf("%d %d %d %d\n", S_x, S_y, F_x, F_y);
	int where = long_rand(1, count-1);
	int y = S_y + where * dy;
	int x1 = S_x + where * dx;
	int x2;
	do
	{
		x2 = long_rand(MIN_COOR, MAX_COOR);
	} while(x1 == x2);
	if(x1 > x2)swap(x1, x2);
	printf("%d %d %d\n", x1, x2, y);
}

plpll egcd(ll x, ll y)
{
	if(y == 0)
	{
		return plpll(x, pll(1, 0));
	}
	plpll tmp = egcd(y, x%y);
	ll xs = tmp.second.second;
	ll ys = (tmp.first - x*xs)/y;
	return plpll(tmp.first, pll(xs, ys));
}

void precision_almost()
{
	ll dx, dy;
	do
	{
		dx = long_rand(2, MAX_COOR - MIN_COOR);
		dy = long_rand(2, MAX_COOR - MIN_COOR);
	} while(egcd(dx, dy).first != 1);
	plpll tmp = egcd(dx, dy);
	int dx2 = abs(tmp.second.second);
	int dy2 = abs(tmp.second.first);
	if(rand()%2)
	{
		dx *= -1;
		dx2 *= -1;
	}
	int S_x = long_rand(max((ll)MIN_COOR, MIN_COOR - dx), min((ll)MAX_COOR, MAX_COOR - dx));
	int S_y = long_rand(MIN_COOR + dy, (ll)MAX_COOR);
	printf("1\n");
	printf("%d %d %d %d\n", S_x, S_y, (int)(S_x + dx), (int)(S_y - dy));
	int x1 = S_x + dx2;
	int y = S_y - dy2;
	int x2;
	do
	{
		x2 = long_rand(MIN_COOR, MAX_COOR);
	} while(x2 == x1);
	if(x1 > x2)swap(x1, x2);
	printf("%d %d %d\n", x1, x2, y);
}

void precision_miss()
{
}



int main()
{
	
	int type, n, seed;
	scanf("%d %d %d", &type, &n, &seed);
	srand(seed);
	switch(type)
	{
		case 0:
		{
			random(n);
			break;
		}
		case 1:
		{
			slalom(n);
			break;
		}
		case 2:
		{
			direct(n);
			break;
		}
		case 3:
		{
			circle(n);
			break;
		}
		case 4:
		{
			circle_hull(n);
			break;
		}
		case 5:
		{
			random_hull(n);
			break;
		}
		case 6:
		{
			precision_exact();
			break;
		}
		case 7:
		{
			precision_almost();
			break;
		}
	}
	return 0;
}