#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;

const int N = 11;
ll f[N][N];
ll gauss(int n,ll f[N][N]) 
{
    ll res = 1;
    for(int i = 1;i <= n;i++) {
        for(int j = i + 1;j <= n;j++) {
            //类似扩欧求逆元
            while(f[j][i]) {
                ll inv = f[j][i] / f[i][i];
                for(int k = i;k <= n;k++) f[j][k] = (f[j][k] - inv * f[i][k] % mod + mod) % mod;
                swap(f[i],f[j]);
                res = -res;
            }
            swap(f[i],f[j]);
            res = -res;
        }
    }
    for(int i = 1;i <= n;i++) res = res * f[i][i] % mod;
    return (res + mod) % mod;
}
int main()
{

    return 0;
}
