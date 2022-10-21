///分组背包
#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int dp[N],w[N][N],v[N][N],s[N];
int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        cin >> s[i];
        for(int j = 1;j <= s[i];j++) cin >> w[i][j] >> v[i][j];
    }
    
    for(int i = 1;i <= n;i++)
        for(int j = m;j >= 0;j--)
            for(int k = 1;k <= s[i];k ++)
                if(w[i][k] <= j) dp[j] = max(dp[j],dp[j - w[i][k]] + v[i][k]);
    cout<<dp[m]<<endl;
    return 0;
}
