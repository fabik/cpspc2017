#include <iostream>
#include <vector>
#include <algorithm>
long long n, x;
int k;
const long long MAXEL=1000LL*1000LL*1000LL*1000LL;
std::vector<long long> li, result;
std::vector<std::pair<long long, int> > kro;
long long nwd(long long a, long long b)
{
    while (a != 0) {
        b %= a;
        std::swap(a, b);
    }
    return b;
}
int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin >> n;
    result.resize(n+2);
    for (int i = 0; i < n; i++) {
        std::cin >> x;
        li.emplace_back(x);
    }
    sort(li.begin(), li.end());
    int ile = 0;
    long long last = li.front();
    for (auto l : li) {
        if (l == last) {
            ile++;
        } else {
            kro.emplace_back(last, ile);
            ile = 1;
            last = l;
        }
    }
    kro.emplace_back(last, ile);
    long long nw = 0;
    long long sum = 0;
    for (auto x : kro)
        sum += x.first;
    for (std::size_t i = 0; i < kro.size(); i++) {
        long long tmp = nwd(nw, kro[i].first);
        //std::cout<<i<<" tmp nw "<<tmp<<" "<<nw<<std::endl;
        if (tmp != nw) {
            long long max = -MAXEL; 
            for (std::size_t j = i; j < kro.size(); j++) 
                max = std::max(max, nwd(nw,kro[j].first ) - kro[j].first);
                long long sum2 = sum + max;
                //std::cout<<"m n "<<max<<" "<<nw<<" "<<sum<<std::endl;
                result[kro.size()-i] = std::max(result[kro.size()-i] ,sum2);
                
                result[kro.size()-i+1] = std::max(result[kro.size()-i+1] ,sum2-max+nw);
            
                //std::cout<<"$result["<<kro.size()-i<<"]= "<<result[kro.size()-i]<<std::endl;
                //std::cout<<"$result["<<kro.size()-i+1<<"]= "<<result[kro.size()-i+1]<<std::endl;
                int ite = 0;
                int poz = kro.size() - 1;
                std::vector<long long> str;
                while (true) {
                    while (poz >= int(i) && kro[poz].second == 1)
                        poz--;
                    if (poz < int(i))
                        break;
                    kro[poz].second--;
                    str.emplace_back(poz);
                    ite++;
                    sum2 += kro[poz].first;
                    result[kro.size()-i+ite] = std::max(result[kro.size()-i+ite],sum2);
                    result[kro.size()-i+ite+1] = std::max(result[kro.size()-i+ite+1],sum2-max+nw);
                    //std::cout<<"result["<<kro.size()-i+ite<<"]= "<<result[kro.size()-i+ite]<<std::endl;
                    //std::cout<<"result["<<kro.size()-i+ite+1<<"]= "<<result[kro.size()-i+ite+1]<<std::endl;
                  
                    
                }
                for(auto x:str)
                    kro[x].second++;
            
            nw=tmp;
        }
        sum-=kro[i].first;//*kro[i].second;

    }
    sum=0;
    for (auto x : li)
        sum += x;
    nw=0;
    for (std::size_t i = 0; i < li.size(); i++) {
        
        long long tmp = nwd(nw, li[i]);
        
        if(tmp!=nw){
            long long max=-MAXEL;
            for(std::size_t j=i;j<li.size();j++){
                max=std::max(max,nwd(li[i],nw))-li[i];
            }
            result[li.size()-i]=std::max(result[li.size()-i],sum+max);
        }else{
            result[li.size()-i]=std::max(result[li.size()-i],sum-li[i]+nw);
        }
        
        sum-=li[i];
        nw=tmp;
        
    }

   
    for (int i=1;i<=n;i++) {
        std::cout << result[i] << "\n";
    }

    
}
