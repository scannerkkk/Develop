#include "bits/stdc++.h"
using namespace std;
const int N = 20;
int dp[N][N],w[N][N],way[N];
int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) cin >> w[i][j];
    for(int i = 1;i <= n;i++) 
        for(int j = 1;j <= m;j++)
            for(int k = 0;k <= j;k++)
                dp[i][j] = max(dp[i][j],dp[i - 1][j - k] + w[i][k]);
    cout << dp[n][m] << endl;
    int T = m;
    //求方案的时候要倒推
    for(int i = n;i >= 1;i--)
        for(int j = 0;j <= T;j++)
            if(dp[i][T] == dp[i - 1][T - j] + w[i][j]) {
                way[i] = j;
                T -= j;
                break;
            }
    
    for(int i = 1;i <= n;i++) cout << i << ' ' << way[i] << endl;
    return 0;
}
