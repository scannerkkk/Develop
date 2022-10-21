#include "bits/stdc++.h"
using namespace std;
const int N = 2010;
int dp[N],v[25000],w[25000],cnt;
int main()
{
    //多重背包二进制优化
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        int v1,w1,s,t = 1;
        cin >> w1 >> v1 >> s;
        while(s >= t){
            v[++cnt] = t * v1;
            w[cnt] = t * w1;
            s -= t;
            t *= 2;
        }
        if(s) v[++cnt] = s * v1, w[cnt] = s * w1;
    }
    for(int i = 1;i <= cnt;i++) for(int j = m;j >= w[i];j--) dp[j] = max(dp[j],dp[j - w[i]] + v[i]);
    cout<<dp[m]<<endl;
    return 0;
}
