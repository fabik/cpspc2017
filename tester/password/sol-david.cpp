#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <algorithm> 
  
typedef unsigned long long int uhuge; 
  
#define N 1 
#define A ((uhuge(1) << 48) - 1) 
#define MAXN 500000 
#define B (1 << 16) 
  
int n; 
int h; 
int hh; 
char S[MAXN + 1]; 
uhuge Mod[N]; 
uhuge Num[N][MAXN * 25]; 
uhuge Help[MAXN * 25]; 
int iHelp[B + 1]; 
  
void Sort(uhuge* a, int n) 
{ 
    uhuge* AH = a; 
    uhuge* BH = Help; 
    uhuge* QH; 
  
    for(int k = 0; k < 48; k += 16) 
    { 
        for(int i = 0; i < B; i++) 
        { 
            iHelp[i] = 0; 
        } 
  
        for(int i = 0; i < n; i++) 
        { 
            iHelp[((AH[i] >> k) & (B - 1)) + 1]++; 
        } 
  
        for(int i = 0; i < B; i++) 
        { 
            iHelp[i + 1] += iHelp[i]; 
        } 
  
        for(int i = 0; i < n; i++) 
        { 
            BH[iHelp[(AH[i] >> k) & (B - 1)]++] = AH[i]; 
        } 
  
        QH = AH; 
        AH = BH; 
        BH = QH; 
    } 
} 
  
uhuge GCD(uhuge a, uhuge b) 
{ 
    uhuge q; 
    if(a < b) 
    { 
        q = a; 
        a = b; 
        b = q; 
    } 
      
    while(b) 
    { 
        q = a % b; 
        a = b; 
        b = q; 
    } 
      
    return a; 
} 
  
int main() 
{ 
    scanf("%d", &n); 
    h = n / 2; 
    hh = h * 50; 
    scanf("%s", S); 
  
    assert(2 <= n); 
    assert(n <= MAXN); 
  
    for(int i = 0; i < n; i++) 
    { 
        assert((S[i] >= 'a') && (S[i] <= 'z')); 
    } 
  
    assert(!(S[n])); 
      
    Mod[0] = A; 
    for(int i = 1; i < N; i++) 
    { 
        Mod[i] = Mod[i - 1]; 
          
        AGAIN: 
        Mod[i]--; 
        for(int j = 0; j < i; j++) 
        { 
            if(GCD(Mod[j], Mod[i]) != 1) 
            { 
                goto AGAIN; 
            } 
        } 
    } 
      
    for(int i = 0; i < N; i++) 
    { 
        uhuge* p = Num[i]; 
        uhuge curpow = 1; 
        for(int j = 0; j < h; j++) 
        { 
            uhuge cur = curpow; 
            for(int k = 0; k < 25; k++) 
            { 
                *(p++) = cur; 
                cur += curpow; 
                cur %= Mod[i]; 
            } 
              
            cur = Mod[i] - curpow; 
            cur %= Mod[i]; 
            for(int k = 0; k < 25; k++) 
            { 
                *(p++) = cur; 
                cur += Mod[i] - curpow; 
                cur %= Mod[i]; 
            } 
  
            curpow *= 26; 
            curpow %= Mod[i]; 
        } 
          
        //std::sort(Num[i], Num[i] + hh); 
        Sort(Num[i], hh); 
  
        /*for(int j = 1; j < hh; j++) 
        { 
            if(Num[i][j] >= (uhuge(1) << 60)) 
            { 
                //printf("?\n"); 
            } 
            if(Num[i][j - 1] > Num[i][j]) 
            { 
                //printf("!\n"); 
            } 
            printf("%lld\n", Num[i][j]); 
            getchar(); 
        }*/
    } 
      
    uhuge a[N]; 
    uhuge b[N]; 
    uhuge curpow[N]; 
  
    for(int i = 0; i < N; i++) 
    { 
        a[i] = 0; 
        b[i] = 0; 
        curpow[i] = 1; 
    } 
      
    int rsl = -1; 
    for(int i = 0; i < h; i++) 
    { 
        for(int j = 0; j < N; j++) 
        { 
            a[j] *= 26; 
            a[j] += S[i] - 'a'; 
            a[j] %= Mod[j]; 
  
            uhuge cur = curpow[j]; 
            cur *= S[(n - 1) - i] - 'a'; 
            cur %= Mod[j]; 
            b[j] += cur; 
            b[j] %= Mod[j]; 
  
            curpow[j] *= 26; 
            curpow[j] %= Mod[j]; 
        } 
  
        for(int j = 0; j < N; j++) 
        { 
            uhuge cur = ((a[j] - b[j]) + Mod[j]) % Mod[j]; 
            uhuge* AH = (0) ? Num[j] : Help; 
            if(!(std::binary_search(AH, AH + hh, cur))) 
            { 
                goto NO; 
            } 
        } 
  
        rsl = (n - 1) - i; 
        NO:; 
    } 
      
    printf("%d\n", rsl); 
    return 0; 
} 