#include <stdio.h>
#include <stdlib.h>

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

int main()
{
	int n, pp;
	scanf("%d%d%d", &m, &pp, &n);
	p = pp * .01;
	q = 1. - p;
	
	for(int i = 0; i < n; i++)
	{
		int h;
		scanf("%d", &h);
		
		if(h > m)
		{
			printf("1 1\n");
			continue;
		}
		
		double r = (h * 1.) / m;
		
		cum = 1.;
		prob = 1.;
		l = 0;
		
		double best = 0.;
		int bbest = 0;
		
		for(int b = 1; b <= m; b++)
		{
			int inc;
			if(MakesSense(b))
			{
				int d = m / b;
				inc = l * d < h;
			}
			else
			{
				inc = l < b * r;
			}
			
			if(inc)
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
			
			if(cum > best)
			{
				best = cum;
				bbest = b;
			}
			
			/*
			if(cum < 1e-6)
			{
				break;
			}
			
			if(cum > 1. - 1e-6)
			{
				best = 1.;
				bbest = m;
				break;
			}
			*/
		}
		
		printf("%d %d\n", m / bbest, bbest);
		//printf("(%.10lf)\n", best);
	}
	
	return 0;
}
