/* ingen for NWD
   Autor: Piotr Smulewicz
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>

#include "oi.h"

using namespace std;
const int MAXC = 10 * 1000 * 1000;
const long long MAXZAK =1000LL*1000LL*1000LL*1000LL;
typedef long long LL;
const int N[] =       { 7 , 15, 2000, 2000  , 500*1000, 500*1000};
const long long Z[] = { 30, 30, 2000, MAXZAK, MAXZAK  , MAXZAK  };

int number = 1;
char letter = 'a';
int uni;
oi::Random generator(1);
vector<int> l, r;
void nastepna_grupa()
{
    number++;
    letter = 'a';
}

vector<long long> data;
void save(int n, int e)
{
    if (uni) {
        sort(data.begin(),data.end());
        std::vector<long long>::iterator it;
        it = std::unique(data.begin(), data.end());

        data.resize(std::distance(data.begin(), it));
    }
    stringstream name;
    name << "test/0" << number << "." << letter << ".in";
    letter++;
    cout << "Generate file " << name.str() << endl;
    ofstream file(name.str().c_str());
    file << data.size() << endl;
    for (int i = 0; i < n; i++) {
        file << data[i] << ((i + 1 != int(data.size())) ? " " : "\n");
    }
}

// random number from interval [l, r]
long long from_interval(long long l, long long r)
{
    //if( l>r )
    //    swap(l,r);
    assert(l <= r);
    long long d = r - l + 1;
    return l + generator.randULL() % d;
}

void random_test(int n, int e, long long min, long long max)
{
    data.clear();

    for (int i = 0; i < n; i++) {
        data.push_back(from_interval(min, max));
    }
    save(n, e);
}

void random_a(long long n, long long k)
{
    data.clear();
    for (int i = 0; i < n; i++) {
        if (i < n / 2)
            data.push_back(k * (i + 1));
        else if (i != n - 1)
            data.push_back((n / 2) * k + 1);
        else
            data.push_back((n / 2) * k * 2);
    }
    save(n, 1);
}

void random_uniq(int n, long long min, long long max)
{
    data.clear();

    for (int i = 0; i < n; i++) {
        data.push_back(from_interval(min, max));
    }

    save(n, 1);
}

void long_work(int n){
    data.clear();
    long long sum=0;
    for(int i=0;i<n;i++){
        if(i<19){
            sum+=(1<<(20-i));
            data.emplace_back(sum);
            
        }else{
            if(i==19)
                sum+=2;
            sum++;
            data.emplace_back(sum);
        }
        
        
        
    }
    save(n, 1);
}
int main()
{

        for (int subtask = 0; subtask < 6; subtask++) {
            uni=(subtask==4);
            for(int i=0;i<3;i++){
            random_test(N[subtask], N[subtask] / 2, 1, Z[subtask]);
            random_test(N[subtask], 2, 1, Z[subtask]);
            random_test(N[subtask], N[subtask] - 3, 1, Z[subtask]);

            random_test(N[subtask], N[subtask] / 2, Z[subtask] - 20, Z[subtask]);
            random_a(N[subtask], Z[subtask] / N[subtask]);
            }
            if(subtask>=3)
                long_work(N[subtask]);
            nastepna_grupa();
           
        }

    return 0;
}
