#include <stdio.h>
#include <stdlib.h>

#define MAXM 1001

double Prob[MAXM][MAXM]; //Prob[i][j] is the probability of exactly i hits out of j blows
double Cum[MAXM][MAXM]; //Cum[i][j] is the probability of at least i hits out of j blows

double Best[MAXM];
int bBest[MAXM];

int main()
{
	int m;
	int pp;
	scanf("%d%d", &m, &pp);
	double p = pp * .01;
	double q = 1. - p;
	
	Prob[0][0] = 1.;
	Cum[0][0] = 1.;
	
	for(int j = 1; j <= m; j++)
	{
		Prob[0][j] = Prob[0][j - 1] * q;
		Prob[j][j] = Prob[j - 1][j - 1] * p;
		
		for(int i = 1; i < j; i++)
		{
			Prob[i][j] = (Prob[i - 1][j - 1] * p) + (Prob[i][j - 1] * q);
		}
		
		Cum[j][j] = Prob[j][j];
		for(int i = j - 1; i >= 0; i--)
		{
			Cum[i][j] = Cum[i + 1][j] + Prob[i][j];
		}
	}
	
	for(int h = 1; h <= m; h++)
	{
		double best = 0.;
		int bbest = 0;
		
		for(int d = 1; d * d <= m; d++)
		{
			int b = m / d;
			int k = (h + (d - 1)) / d;
			double cur = Cum[k][b];
			
			if(cur > best)
			{
				best = cur;
				bbest = b;
			}
		}
		
		for(int b = 1; b * b <= m; b++)
		{
			int d = m / b;
			int k = (h + (d - 1)) / d;
			double cur = Cum[k][b];
			
			if(cur > best)
			{
				best = cur;
				bbest = b;
			}
		}
		
		if(best > 1 - 1e-6)
		{
			bbest = m;
		}
		
		Best[h] = best;
		bBest[h] = bbest;
	}
	
	int n;
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++)
	{
		int h;
		scanf("%d", &h);
		
		if(h > m)
		{
			printf("1 1\n");
		}
		else
		{
			int b = bBest[h];
			printf("%d %d\n", m / b, b);
		}
	}
	
	return 0;
}

