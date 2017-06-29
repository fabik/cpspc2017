/*
    Autor: Lukasz Marecik
    
    Rozwiazanie wzorcowe nr 1.
    Pomysl AT + moja optymalizacja.
    Zlozonosc: O(n log n).
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

// Ubogie drzewo sum.
// obsluguje:
//  - aktualizacje konkretnego indeksu
//  - zapytanie o sume na spojnym przedziale

class PoorSumTree {
	int n ;
	int *d ;
 public:
	void set(int i, int add) {
		i += n-1 ;
		d[i] += add ;
		for(i>>=1 ; i>0 ; i>>=1)
			d[i] += add ;
	}
	int get(int from) {
		int ret(0) ;
		int i=from+n-1 ;
		do {
			i >>= __builtin_ctz(i) ;
			ret += d[i] ;
			i++ ;
		} while(i&(i-1)) ;
		return ret ;
	}
	int get(int from, int to) {
	    if(from>to) return 0 ;
		return get(from) - ((to<n) ? get(to+1) : 0) ;
	}
	
	PoorSumTree(int size) {     // reprezentuje przedzial [1,..,size]
		n=1 ;
		while(n<size) n<<=1 ;
		d = new int[2*n]() ;
	}
	~PoorSumTree() {
		delete [] d ;
	}
} ;

////////////////////////////////////////////////////////////////////////////////

const int MAXN=2e5+100 ;

VI G1[MAXN] ;
VI G2[MAXN] ;

///////////////////////////////

// PIERWSZA FAZA obliczen: numerowanie POST-ORDER wierzcholkow w obu drzewach
struct Node {
    int id ;        // numer wierzcholka w postorder
    int a, b ;      // [a,b] to przedzial jaki tworza numery wierzcholkow w tym poddrzewie
} ;
Node info1[MAXN] ;
Node info2[MAXN] ;

int whoHasId[MAXN] ;    // odwrotne zaleznosci z pierwszego drzewa
VI  whoHasA [MAXN] ;
VI  whoHasB [MAXN] ;

int size[MAXN], ans[MAXN] ;

int nextNr=1 ;

void calcTree1Info(int u) {
    info1[u].a = nextNr ;
    FOREACH(it, G1[u])
        calcTree1Info(*it) ;
    info1[u].b = nextNr-1 ;
    info1[u].id = nextNr++ ;
    
    whoHasId[info1[u].id] = u ;
    whoHasA [info1[u].a].PB(u) ;
    whoHasB [info1[u].b].PB(u) ;
}

void calcTree2Info(int u) {
    size[u]=1 ;
    info2[u].a = nextNr ;
    FOREACH(it, G2[u]) {
        calcTree2Info(*it) ;
        size[u] += size[*it] ;
    }
    info2[u].b = nextNr-1 ;
    info2[u].id = nextNr++ ;
    
    ans[u] = size[u]-1 ;
}

///////////////////////////////

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
    nextNr=1 ; calcTree1Info(1) ;
    nextNr=1 ; calcTree2Info(1) ;
    
    PoorSumTree *T = new PoorSumTree(n) ;
    for(int i=1 ; i<=n ; i++) {
        FOREACH(it, whoHasA[i])
            ans[*it] -= T->get(info2[*it].a, info2[*it].b) ;
        T->set(info2[whoHasId[i]].id, 1) ;
    }
    
    delete T ;
    T = new PoorSumTree(n) ;
    for(int i=n ; i>=0 ; i--) {
        FOREACH(it, whoHasB[i])
            ans[*it] -= T->get(info2[*it].a, info2[*it].b) ;
        if(i>0)
            T->set(info2[whoHasId[i]].id, 1) ;
    }
    
    // wypisywanie wyniku
    for(int i=1 ; i<=n ; i++)
        cout << ans[i] << " " ;
    cout << endl ;
}

