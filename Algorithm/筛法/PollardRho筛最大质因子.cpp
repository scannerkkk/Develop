#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ull = unsigned long long;
ll ksc(ll x,ll y,ll p) 
{
    ll z = ((long double) x / p * y);
    ll t = (ull) x * y - (ull)z * p;
    return (t + p) % p;
}
ll ksm(ll a,ll k,ll p) 
{
    ll res = 1;
    while(k) {
        if(k & 1) res = ksc(res,a,p);
        a = ksc(a,a,p);
        k >>= 1;
    }
    return res;
}
//Miller Rabin随机筛
inline bool MR(ll x,ll p) 
{
    //费马小定理判断同余方程是否成立
    if(ksm(x,p - 1,p) != 1)  return 0;
    ll y = p - 1,z;
    while(!(y & 1)) {
        y >>= 1;z = ksm(x,y,p);
        if(z != 1 && z != p - 1) return 0;
        if(z == p - 1) return 1;
    }
    return 1;
}
inline bool prime(ll x)
{
    if(x == 2 || x == 3 || x == 5 || x == 7 || x == 11 
    || x == 13 || x == 17 || x == 19 || x == 23 || x == 41) 
        return 1;
    return MR(2,x) && MR(3,x) && MR(5,x) && MR(7,x) && MR(11,x)
        && MR(13,x) && MR(17,x) && MR(19,x) && MR(23,x) && MR(41,x);
}
//求p的非平凡因子
//生成函数f(x) = x * x + c
inline ll rho(ll p)
{
    ll x,y,z,c,g,i,j;
    while(1) {
        y = x = rand() % p;
        z = 1,c = rand() % p;
        i = 0,j = 1;
        while(++ i) {
            x = (ksc(x,x,p) + c) % p;
            z = ksc(z,abs(y - x),p);
            if(x == y || !z) break;
            if(!(i % 127) || i == j) {
                g = __gcd(z,p);
                if(g > 1) return g;
                if(i == j) y = x,j <<= 1;
            }
        }
    }
}
ll ans = 1;
//递归分解质因子
inline void prho(ll p)
{
    if(p <= ans) return ;
    if(prime(p)) {
        ans = p;
        return ;
    }
    ll fac = rho(p);
    while(p % fac == 0) p /= fac;
    prho(p),prho(fac);
}
int main()
{
    srand(time(0));
    int T;
    scanf("%d",&T);
    while(T --) {
        ll x;
        scanf("%lld",&x);
        ans = 1;
        prho(x);
        if(ans == x) puts("Prime");
        else printf("%lld\n",ans);
    }
    return 0;
}
