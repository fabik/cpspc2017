#include <bits/stdc++.h>
using namespace std ;
using namespace __gnu_cxx ;
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

#include "oi.h"
oi::Random RG ;

const string TASK = "kor" ;

const int TESTS = 4 ;
const VI N[TESTS] = { {100, 1000, 2000},            // male testy dla bruta
                      {100000, 190000, 200000} } ;  // duze testy dla wzorcowki
const int PATH_RATIO_SIZE = 3 ;
const double pathRatio1[PATH_RATIO_SIZE] = { 0.4, 0.6, 0.8 } ;
const double pathRatio2[PATH_RATIO_SIZE] = { 0.3, 0.5, 0.7 } ;

const int ALMOST_EQUAL_PATH_TYPES = 2 ;

////////////////////////////////////////////////////////////////////////////////

// Tworzy losowe drzewo:
// - Na poczatku buduje losowa sciezke rozmiaru 'path'
// - Potem losowo dokleja pozostale wierzcholki
// Jezeli 'path' jest ~rozmiaru drzewa to:
// - drzewo jest glebokie         = niepodatne na bruta kors1
// - odpowiedz jest w miare duza  = niepodatne na bruta kors2
void genTreeWithLongPath(int n, int path, VI &line) {
    // dla wygody wierzcholki numerujemy 0..n-1
    VI nodes(n), parent(n) ;
    REP(i, n)
        nodes[i] = i ;
    RG.randomShuffle(nodes.begin()+1, nodes.end()) ;
    
    for(int i=1 ; i<n && i<path ; i++)      // dluga sciezka w glab
        parent[nodes[i]] = nodes[i-1] ;
        
    for(int i=path ; i<n ; i++)             // reszta losowo
        parent[nodes[i]] = nodes[RG.rand()%i] ;
    
    line.clear() ;
    for(int i=1 ; i<n ; i++)
        line.PB(parent[i]+1) ;
}

// Tworzy dwa "podobne" losowe drzewa o pierwiastkowej wysokosci
// oraz szerokosci.
// Metoda: doklejanie pierwiastkowych sciezek.
// W drugim drzewie doklejam permutacje tejze sciezki.
void genTreesWithSqrtHeightAndWidth(int n, VI &line1, VI &line2) {
    // dla wygody wierzcholki numerujemy 0..n-1
    VI nodes(n), parent(n) ;
    REP(i, n)
        nodes[i] = i ;
    RG.randomShuffle(nodes.begin()+1, nodes.end()) ;
    
    VI parent2(n) ;
    
    const int SQRT = sqrt(n) ;
    
    for(int start=0, i=1 ; i<n ; i+=SQRT, start++) {
        parent[nodes[i]] = nodes[start] ;
        for(int j=i+1 ; j<i+SQRT && j<n ; j++)
            parent[nodes[j]] = nodes[j-1] ;
        
        RG.randomShuffle(nodes.begin()+i, nodes.begin()+min(i+SQRT, n)) ;
        
        parent2[nodes[i]] = nodes[start] ;
        for(int j=i+1 ; j<i+SQRT && j<n ; j++)
            parent2[nodes[j]] = nodes[j-1] ;
    }
    
    line1.clear() ;
    line2.clear() ;
    for(int i=1 ; i<n ; i++) {
        line1.PB(parent[i] +1) ;
        line2.PB(parent2[i]+1) ;
    }
}

void genAlmostEqualPaths(int n, VI &line1, VI &line2, int type) {
    // dla wygody wierzcholki numerujemy 0..n-1
    VI nodes(n), parent(n) ;
    REP(i, n)
        nodes[i] = i ;
    RG.randomShuffle(nodes.begin()+1, nodes.end()) ;
    
    for(int i=1 ; i<n ; i++)
        parent[nodes[i]] = nodes[i-1] ;
    
    VI parent2(n) ;
    
    if(type==0) {
        const int PART=5 ;
        for(int i=1 ; i<n ; i+=PART)
            swap(nodes[min(i+RG.rand()%PART,n-1)], nodes[min(i+RG.rand()%PART,n-1)]) ;
    }
    else if(type==1) {
        VI part[2] ;
        for(int i=1 ; i<n ; i++)
            part[i&1].PB(nodes[i]) ;
        
        nodes.resize(1) ;
        REP(i, 2)
            FOREACH(it, part[i])
                nodes.PB(*it) ;
    }
    else assert(false) ;
    
    for(int i=1 ; i<n ; i++)
        parent2[nodes[i]] = nodes[i-1] ;
    
    line1.clear() ;
    line2.clear() ;
    for(int i=1 ; i<n ; i++) {
        line1.PB(parent[i] +1) ;
        line2.PB(parent2[i]+1) ;
    }
}

////////////////////////////////////////////////////////////////////////////////

struct {
    int n ;
    VI line[2] ;
} test ;

void genRandomTestWithLongPath(int n, int pathSize1, int pathSize2) {
    test.n = n ;
    genTreeWithLongPath(n, pathSize1, test.line[0]) ;
    genTreeWithLongPath(n, pathSize1, test.line[1]) ;
}

void genRandomTestWithSqrtHeightAndWidth(int n) {
    test.n = n ;
    genTreesWithSqrtHeightAndWidth(n, test.line[0], test.line[1]) ;
}

void genRandomTestWithEqualPaths(int n) {
    test.n = n ;
    genTreeWithLongPath(n, n, test.line[0]) ;
    test.line[1] = test.line[0] ;
}

void genRandomTestWithAlmostEqualPaths(int n, int type) {
    test.n = n ;
    genAlmostEqualPaths(n, test.line[0], test.line[1], type) ;
}

////////////////////////////////////////////////////////////////////////////////

void ouput(const string &fileName) {
    ofstream out(fileName) ;
    out << test.n << endl ;
    REP(j, 2)
        for(int i=0 ; i<(int)test.line[j].size() ; i++) {
            out << test.line[j][i] ;
            if(i+1!=(int)test.line[j].size()) out << " " ;
            else out << endl ;
       }
    out.close() ;
}

int main()
{
    for(int t=1 ; t<=TESTS ; t++) {
        RG.setSeed(74638746+t) ;
        
        char nextLetter='a' ;
        FOREACH(n, N[t-1]) {
            for(int g=0 ; g<PATH_RATIO_SIZE ; g++) {
                genRandomTestWithLongPath(*n, (*n)*pathRatio1[g], (*n)*pathRatio2[g]) ;
                ouput("test/0" + to_string(t) + "." + (nextLetter++) + ".in") ;
            }
        
            genRandomTestWithSqrtHeightAndWidth(*n) ;
            ouput("test/0" + to_string(t) + "." + (nextLetter++) + ".in") ;
            
            genRandomTestWithEqualPaths(*n) ;
            ouput("test/0" + to_string(t) + "." + (nextLetter++) + ".in") ;
            
            REP(g, ALMOST_EQUAL_PATH_TYPES) {
                genRandomTestWithAlmostEqualPaths(*n, g) ;
                ouput("test/0" + to_string(t) + "." + (nextLetter++) + ".in") ;
            }
        }
    }
}
