#include "bits/stdc++.h"
using namespace std;
const int N = 5010;
int primes[N],vis[N],sum[N],cnt;
//先分解质因数，再高精度乘
void get_prime(int n)
{
    for(int i = 2;i <= n;i++){
        if(!vis[i]) primes[++cnt] = i;
        for(int j = 1;primes[j] <= n / i;j++){
            vis[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}
int get(int a,int p)
{
    int res = 0;
    while(a){
        res += a / p;
        a /= p;
    }
    return res;
}
vector<int> mul(vector<int> &a,int p)
{
    vector<int> res;
    int t = 0;
    for(int i = 0,len = a.size();i < len;i ++){
        t += a[i] * p;
        res.push_back(t % 10);
        t = t / 10;
    }
    while(t){
        res.push_back(t % 10);
        t /= 10;
    }
    return res;
}
int main()
{
    int a,b;
    cin >> a >> b;
    get_prime(a);
    for(int i = 1;i <= cnt;i++){
        int p = primes[i];
        sum[i] = get(a,p) - get(b,p) - get(a - b,p);
    }
    
    vector<int> res;
    res.push_back(1);
    for(int i = 1; i<= cnt;i++){
        for(int j = 1;j <= sum[i];j++){
            res = mul(res,primes[i]);
        }
    }
    
    for(int i = res.size() - 1;i >= 0;i --) cout<<res[i];
    return 0;
}
