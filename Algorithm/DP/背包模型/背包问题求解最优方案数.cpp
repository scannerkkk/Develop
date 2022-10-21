//背包问题求最优解方案数
#include "bits/stdc++.h"
using namespace std;
const int N = 1010,mod = 1e9 + 7;
int w[N],v[N];
int f[N],g[N];
int main()
{
    int n,m;
    cin >> n >> m;
    g[0] = 1;
    for(int i = 1;i <= n;i++) cin >> v[i] >> w[i];
    for(int i = 1;i <= n;i++) for(int j = m;j >= v[i];j--) {
        int tmp = max(f[j],f[j - v[i]] + w[i]);
        int val = 0;
        if(tmp == f[j]) val = (val + g[j]) % mod;
        if(tmp == f[j - v[i]] + w[i]) val = (val + g[j - v[i]]) % mod;
        g[j] = val,f[j] = tmp;
    }
    int res = 0;
    for(int i = 0;i <= m;i++) {
        if(f[i] == f[m]) res = (res + g[i]) % mod;
    }
    cout << res << endl;
    return 0;
}
