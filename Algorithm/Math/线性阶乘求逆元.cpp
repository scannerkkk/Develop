#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 2010,mod = 1e5 + 3;
ll fac[N],inv[N],y;
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
int main()
{
    int a,b,c,d,k;
    cin >> a >> b >> c >> d >> k;
    fac[0] = inv[0] = 1;
    for(int i = 1;i <= 2000;i++) fac[i] = i * fac[i - 1] % mod;
    exgcd(fac[2000],mod,inv[2000],y);
    inv[2000] = (inv[2000] % mod + mod) % mod;
    for(int i = 1999;i >= 1;i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    ll ans = 0;
    for(int i = 0;i <= k;i++) ans = (ans + C(b,i) * P(a,i) % mod * C(d,k - i) % mod * P(a + c - i,k - i) % mod) % mod;
    cout << ans << endl;
    return 0;
}
