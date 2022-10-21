//二维背包
#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int dp[N][N],u[N],v[N],w[N];
int main()
{
    int n,m,k;
    cin >> n >> k >> m;
    for(int i = 1;i <= n;i++) cin >> u[i] >> w[i] >> v[i];
    for(int i = 1;i <= n;i++) 
        for(int j = m;j >= w[i];j--) 
            for(int z = k;z >= u[i];z--) 
               dp[j][z] = max(dp[j][z],dp[j - w[i]][z - u[i]] + v[i]);
    cout<<dp[m][k]<<endl;
    return 0;
}
