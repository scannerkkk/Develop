#include "bits/stdc++.h"
using namespace std;
const int N = 3010;
int dp[N],a[N],b[N];
//acwing272
int main()
{
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) cin >> b[i];
    for(int i = 1;i <= n;i++) {
        int mx = 0;
        for(int j = 1;j <= n;j++) {
            //找到每个以b[j]结尾的前面最大的长度
            if(b[j] < a[i] && mx < dp[j]) mx = dp[j];
            //如果当前相等，则可以进行一次状态转移：dp[j] = 找到的最大的 + 本身的长度
            if(b[j] == a[i]) dp[j] = mx + 1;
        }
    }
    int res = 0;
    for(int i = 1;i <= n;i++)  res = max(res,dp[i]);
    cout << res << endl;
    return 0;
}
