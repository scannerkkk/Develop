#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
ll get_inv(ll a,ll p,ll mod)
{
    ll res =  1;
    while(p){
        if(p & 1) res = res * a % mod;
        p >>= 1;
        a = a * a % mod;
    }
    return res;
}
int main()
{
    int n;
    cin >> n;
    while(n --){
        //p必须是质数
        ll a,p;
        cin >> a >> p;
        //费马定理 两个数必须互质才有逆元
        if(a % p == 0) cout<<"impossible"<<endl;
        else cout<<get_inv(a,p - 2,p)<<endl;
    }
    return 0;
}
