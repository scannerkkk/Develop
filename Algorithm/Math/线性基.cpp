#include "bits/stdc++.h"
using namespace std;
using ll = long long;
ll d[70],p[70],cnt;
const int mod = 10086;
bool zero = false;
void init()
{
    cnt = 0;
    zero = false;
    memset(d,0,sizeof(d));
    memset(p,0,sizeof(p));
}
ll qpow(ll a,int p)
{
    ll res = 1;
    while(p) {
        if(p & 1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}
void insert(ll x)
{
    for(int i = 63;i >= 0;i--) {
        if(x >> i) {
            if(!p[i]) {
                p[i] = x;
                return ;
            }
            x ^= p[i];
        }
    }
    zero = true;
}
void rebuild()
{
    for(int i = 0;i <= 63;i++) 
        for(int j = i - 1;j >= 0;j--)
            if(p[i] & (1LL << j)) p[i] ^= p[j];
    for(int i = 0;i <= 63;i++) if(p[i]) d[cnt++] = p[i];
}
ll ask_kmax(ll k)
{
    k -= zero;
    if(!k) return 0;
    if(k >= (1LL << cnt)) return -1;
    ll res = 0;
    for(int i = 63;i >= 0;i--) if(k & (1LL << i)) res ^= d[i];
    return res;
}
ll ask_kmin(ll k)
{
    k -= zero;
    if(!k) return 0;
    if(k >= (1LL << cnt)) return -1;
    ll res = 0;
    for(int i = 0;i <= 63;i++) if(k & (1LL << i)) res = res ^ d[i];
    return res;
}
ll ask_max()
{
    ll res = 0;
    for(int i = 63;i >= 0;i--) res = max(res,res ^ d[i]);
    return res;
}
ll ask_min()
{
    if(zero) return 0;
    for(int i = 0;i <= 63;i++) if(d[i]) return d[i];
    return 0;
}
ll ask_firstX(int n,ll x)
{
    ll res = 0;
    for(int i = 0;i <= 63;i++) if(p[i]) d[cnt++] = i;
    for(int i = 0;i < cnt;i++) if(x & (1LL << d[i])) (res += (1LL << i)) %= mod;
    res = ((res * qpow(1LL * 2,n - cnt) + 1) % mod) % mod;
    return res;
}
bool exist(ll x)
{
    for(int i = 63;i >= 0;i--) {
        if(x & (1 << i)) x ^= p[i];
        if(!x) return true;
    }
    return false;
}
void solve()
{
    init();
    ll n,x;
    cin >> n;
    for(int i = 1;i <= n;i++) {
        scanf("%lld",&x);
        insert(x);
    }
    scanf("%lld",&x);
    //除了询问某个数第一次出现的位置，其余操作全都要先rebuild
    // rebuild();
    printf("%lld\n",ask_firstX(n,x));
}
int main()
{
    solve();
    return 0;
}
