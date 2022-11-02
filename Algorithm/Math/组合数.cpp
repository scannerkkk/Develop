#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 2010000,mod = 1e9 + 7;
ll fac[N],inv[N];
ll C(int a,int b)
{
    if(a < b) return 0;
    return fac[a] * inv[b] % mod * inv[a - b] % mod;
}
ll P(int a,int b)
{
    if(a < b) return 0;
    return fac[a] * inv[a - b] % mod;;
}
void exgcd(int a,int b,ll &x,ll &y)
{
    if(!b) {
        x = 1,y = 0;
        return ;
    }
    exgcd(b,a % b,y,x);
    y -= a / b * x;
}
void init(int n)
{   
    ll x,y;
    fac[0] = inv[0] = 1;
    for(int i = 1;i <= n;i++) fac[i] = i * fac[i - 1] % mod;
    exgcd(fac[n],mod,inv[n],y);
    inv[n] = (inv[n] % mod + mod) % mod;
    for(int i = n - 1;i >= 1;i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int main()
{
    init()
    return 0;
}
