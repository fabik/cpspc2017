#include <stdio.h>
#include <stdlib.h>

#define MAXM 1000001

double Prob[MAXM];
double Cum[MAXM];

int m;
double p, q;
double cum = 1., newcum;
double prob = 1., newprob;
int l = 0;

double Compute(int ll, int bb)
{
	cum = 1.;
	prob = 1.;
	l = 0;
	
	for(int b = 1; b <= bb; b++)
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
	}
	
	Cum[l] = cum;
	Prob[l] = prob;
	
	for(int k = l - 1; k >= ll; k--)
	{
		Prob[k] = (Prob[k + 1] * q * (k + 1)) / (p * (bb - k));
		Cum[k] = Cum[k + 1] + Prob[k];
		
		if(Cum[k] > 1. - 1e-6)
		{
			//printf("R1\n");
			return 1.;
		}
	}
	
	for(int k = l + 1; k <= ll; k++)
	{
		Prob[k] = (Prob[k - 1] * p * (bb - (k - 1))) / (q * k);
		Cum[k] = Cum[k - 1] - Prob[k - 1];
		
		if(Cum[k] < p - 1e-6)
		{
			//printf("R0\n");
			return 0.;
		}
	}
	
	//printf("RA\n");
	return Cum[ll];
}

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		fprintf(stderr, "Usage: %s file.in file.ok file.out\n", argv[0]);
		return 1;
	}
	
	FILE* fin = fopen(argv[1], "rt");
	FILE* fok = fopen(argv[2], "rt");
	FILE* fout = fopen(argv[3], "rt");
	
	if(!(fin)) 
	{
		fprintf(stderr, "Cannot open file \"%s\"!\n", argv[1]);
		return 1;
	}
	
	if(!(fok))
	{
		fprintf(stderr, "Cannot open file \"%s\"!\n", argv[2]);
		return 1;
	}
	
	if(!(fout))
	{
		fprintf(stderr, "Cannot open file \"%s\"!\n", argv[3]);
		return 1;
	}
	
	
	int pp;
	fscanf(fin, "%d%d", &m, &pp);
	p = pp * .01;
	q = 1. - p;
	
	int n;
	fscanf(fin, "%d", &n);
	
	for(int i = 0; i < n; i++)
	{
		int h;
		fscanf(fin, "%d", &h);
		
		int lOk, bOk;
		double pOk;
		fscanf(fok, "%d%d%lf", &lOk, &bOk, &pOk);
		
#define WRONG \
	fprintf(stdout, "0\n"); \
	return 0
		
		int dOut, bOut;
		if(fscanf(fout, "%d%d", &dOut, &bOut) != 2)
		{
			//printf("Too few numbers\n");
			WRONG;
		}
		
		if((dOut < 1) || (bOut < 1) || (dOut * 1LL * bOut > m))
		{
			//printf("Out of bounds\n");
			WRONG;
		}
		
		if(pOk == 0.)
		{
			continue;
		}
		
		int lOut = (h + (dOut - 1)) / dOut;
		if((bOut == bOk) && (lOut == lOk))
		{
			continue;
		}
		
		double pOut = Compute(lOut, bOut);
		if(pOut < pOk - 1e-6)
		{
			//printf("Low probability %.10lf < %.10lf\n", pOut, pOk);
			WRONG;
		}
		else
		{
			//printf("Computed probability %.10lf vs. %.10lf (OK)\n", pOut, pOk);
		}
	}
	
	fprintf(stdout, "1\n");
	return 0;
}
