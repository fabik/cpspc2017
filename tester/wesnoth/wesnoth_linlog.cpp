#include <stdio.h>
#include <stdlib.h>

#define MAXM 1000001

double Prob[MAXM];
double Cum[MAXM];

double Best[MAXM];
int bBest[MAXM];

int m;
double p, q;
double cum = 1., newcum;
double prob = 1., newprob;
int l = 0;

int MakesSense(int b)
{
	if(b * 1LL * b <= m)
	{
		return 1;
	}
	
	int d = m / b;
	return b == m / d;
}

int nChecks;
void Check(double cum, int l, int b)
{
	int d = m / b;
	int h = l * d;
	
	//printf("Checking >= %d of %d (%d HP) with %.10lf\n", l, b, h, cum);
	
	if(Best[h] < cum)
	{
		Best[h] = cum;
		bBest[h] = b;
	}
	else
	{
		//printf("Refused!\n");
	}
}

void Expand(int b)
{
	Check(cum, l, b);
	Cum[l] = cum;
	Prob[l] = prob;
	
	for(int k = l - 1; k >= 1; k--)
	{
		nChecks++;
		
		Prob[k] = (Prob[k + 1] * q * (k + 1)) / (p * (b - k));
		Cum[k] = Cum[k + 1] + Prob[k];
		
		if(Cum[k] > 1. - 1e-6)
		{
			if(b == m)
			{
				Check(1., k, b);
			}
			
			//break;
		}
		else
		{
			Check(Cum[k], k, b);
		}
	}
	
	for(int k = l + 1; k <= b; k++)
	{
		nChecks++;
		
		Prob[k] = (Prob[k - 1] * p * (b - (k - 1))) / (q * k);
		Cum[k] = Cum[k - 1] - Prob[k - 1];
		
		if(Cum[k] < p)
		{
			//break;
		}
		else
		{
			Check(Cum[k], k, b);
		}
	}
}

int main()
{
	int pp;
	scanf("%d%d", &m, &pp);
	p = pp * .01;
	q = 1. - p;
	
	for(int b = 1; b <= m; b++)
	{
		if(l < b * p)
		{
			l++;
			newcum = (p * cum) + (q * (cum - prob));
			newprob = (prob * p * b) / l;
		}
		else
		{
			double probl = (prob * q * l) / (p * (b - l));
			newcum = (p * (cum + probl)) + (q * cum);
			newprob = (prob * q * b) / (b - l);
		}
		
		cum = newcum;
		prob = newprob;
		
		if(MakesSense(b))
		{
			Expand(b);
		}
	}
	
	double best = 0.;
	int bbest = 0;
	
	for(int h = m; h > 0; h--)
	{
		if(Best[h] > best)
		{
			best = Best[h];
			bbest = bBest[h];
		}
		else
		{
			Best[h] = best;
			bBest[h] = bbest;
		}
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
