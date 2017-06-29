/*
    Autor: Lukasz Marecik
    
    Najprostsze rozwiazanie brutalne,
    dzialajace w czasie O(\sum_v subTreeSize(v)) = O(n^2).
*/

#include <bits/stdc++.h>
using namespace std ;
typedef long long LL ;
typedef pair<int,int> PII ;
typedef vector<int> VI ;
const int INF = 1e9+100 ;
const LL INFLL = (LL)INF*INF ;
#define REP(i,n) for(int i=0;i<(n);++i)
#define ALL(c) c.begin(),c.end()
#define FOREACH(i,c) for(auto i=(c).begin();i!=(c).end();++i)
#define CLEAR(t) memset(t,0,sizeof(t))
#define PB push_back
#define MP make_pair
#define FI first
#define SE second

////////////////////////////////////////////////////////////////////////////////

const int MAXN=2e5+100 ;

VI G1[MAXN] ;
VI G2[MAXN] ;

int color[MAXN]; 

// w pierwszym przebiegu zaznaczamy potomkow
void mark1(int u, int c) {
    color[u] = c ;
    FOREACH(it, G1[u])
        mark1(*it, c) ;
}

// w drugim przebiegu liczymy ile potomkow zostalo zaznaczonych
int mark2(int u, int c) {
    int ret = (color[u]==c) ;
    FOREACH(it, G2[u])
        ret += mark2(*it, c) ;
    return ret ;
}

int main()
{
    ios_base::sync_with_stdio(0) ;
    int n, a, b ;
    
    // wczytywanie danych
    cin >> n ;
    for(int i=2 ; i<=n ; i++) {
        cin >> a ;
        G1[a].PB(i) ;
    }
    for(int i=2 ; i<=n ; i++) {
        cin >> b ;
        G2[b].PB(i) ;
    }
    
    // obliczenia
    for(int i=1 ; i<=n ; i++) {
        mark1(i, i) ;
        cout << mark2(i, i)-1 << " " ;
    }
    cout << endl ;
}

