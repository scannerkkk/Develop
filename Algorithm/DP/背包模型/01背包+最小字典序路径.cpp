#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int dp[N][N],w[N],v[N];
int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> w[i] >> v[i];
    //求最小字典序，从最后开始往前面转移
    for(int i = n;i >= 1;i--) {
        for(int j = 0;j <= m;j++) {
            dp[i][j] = dp[i + 1][j];
            if(j >= w[i]) dp[i][j] = max(dp[i][j],dp[i + 1][j - w[i]] + v[i]);
        }
    }
    int j = m;
    for(int i = 1;i <= n;i++) {
        //如果当前这个状态可以转移
        if(j >= w[i] && dp[i][j] == dp[i + 1][j - w[i]] + v[i]){
            j -= w[i];
            cout << i << ' ';
        }
    }
    return 0;
}
