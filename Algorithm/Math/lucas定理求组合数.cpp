#include "bits/stdc++.h"
#define ll long long
using namespace std;
const int mod = 1e6 + 3;
const int N = 1e6 + 10;
ll fac[N],inv[N];
// 时间复杂度：Lucas定理(O(p + logP))
// C(a,b)(lucas)≡(a/p,b/p)(lucas) * C(a % p,b % p)
//求逆元
ll ksm(ll a,ll p)
{
    ll res = 1;
    while(p) {
        if(p & 1) res = 1LL * res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}
//处理组合数
ll combin(ll a,ll b)
{
    if(a < b) return 0;
    return fac[a] * inv[b] % mod * inv[a - b] % mod;
}
//O(p)处理阶乘以及阶乘逆元
void init()
{
    inv[0] = fac[0] = 1;
    for(int i = 1;i < mod;i++) fac[i] = fac[i - 1] * i % mod;
    inv[mod - 1] = ksm(fac[mod - 1],mod - 2);
    for(int i = mod - 2;i >= 1;i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int Lucas(int a,int b)
{
    if(a < mod && b < mod) return combin(a,b);
    else return 1LL * combin(a % mod,b % mod) * Lucas(a / mod,b / mod) % mod;
}
int main()
{
    int T;
    scanf("%d",&T);
    init();
    while(T --) {
        int n,l,r,ans;
        scanf("%d%d%d",&n,&l,&r);
        printf("%d\n",(Lucas(n + r - l + 1,r - l + 1) - 1 + mod) % mod);
    }
    return 0;
}
