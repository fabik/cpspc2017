#include <stdio.h>
#include <stdlib.h>

#define MAXM 1000001

double Prob[MAXM];
double Cum[MAXM];

double Best[MAXM];
int bBest[MAXM];

int Sure[MAXM];
int Least;

int m, pp;
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
			
			break;
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
			break;
		}
		else
		{
			Check(Cum[k], k, b);
		}
	}
}

void Compute()
{
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
	
	int bcur = 0;
	int beg = 0;
	
	for(int h = 1; h <= m; h++)
	{
		int b = bBest[h];
		if(b != bcur)
		{
			if(bcur)
			{
				//printf("%d..%d: %d-%d\n", beg, h - 1, m / bcur, bcur);
				Sure[h - 1] = 1;
				Sure[h] = 1;
				
				for(int i = h - 2; (i > 0) && (rand() % 2); i--)
				{
					Sure[i] = 1;
				}
				
				for(int i = h + 1; (i <= m) && (rand() % 2); i++)
				{
					Sure[i] = 1;
				}
			}
			
			bcur = b;
			beg = h;
		}
		
		if((!(Least)) && (b != m))
		{
			Least = h;
		}
	}
	
	//printf("%d..%d: %d-%d\n", beg, m, m / bcur, bcur);
	//printf("nChecks: %d\n", nChecks);
}

int RandRange(int min, int max)
{
	return (rand() % ((max - min) + 1)) + min;
}

int main(int argc, char** argv)
{
	if(argc < 5)
	{
		printf("Usage: %s m p n type ...\n", argv[0]);
		return 0;
	}
	
	int n, type;
	sscanf(argv[1], "%d", &m);
	sscanf(argv[2], "%d", &pp);
	sscanf(argv[3], "%d", &n);
	sscanf(argv[4], "%d", &type);
	
	srand(m + pp + n);
	
	printf("%d %d\n", m, pp);
	printf("%d\n", n);
	
	switch(type)
	{
		case 1:
		for(int i = 0; i < n; i++)
		{
			int h;
			sscanf(argv[5 + i], "%d", &h);
			printf("%d%c", h, (i == n - 1) ? '\n' : ' ');
		}
		break;
		
		case 2:
		case 3:
		for(int i = 0; i < n; i++)
		{
			int h = i + 1;
			printf("%d%c", h, (i == n - 1) ? '\n' : ' ');
		}
		break;
		
		case 4:
		for(int i = 0; i < n; i++)
		{
			int h = (rand() % 1000000) + 1;
			printf("%d%c", h, (i == n - 1) ? '\n' : ' ');
		}
		break;
		
		case 5:
		Compute();
		
		int h = (rand() % 10) + 1;
		printf("%d ", h);
		n--;
		
		for(int h = 1; h <= m; h++)
		{
			if(Sure[h])
			{
				printf("%d ", h);
				n--;
			}
		}
		
		for(int i = 0; i < n; i++)
		{
			int h = RandRange(Least, m);
			printf("%d%c", h, (i == n - 1) ? '\n' : ' ');
		}
		
		break;
	}
	
	return 0;
}
