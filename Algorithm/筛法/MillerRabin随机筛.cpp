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
    ll y = x - 1,z;
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
int main()
{

    return 0;
}
