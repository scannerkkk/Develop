#include "bits/stdc++.h"
using namespace std;
const int N = 2e3 + 10;
int dp[N];
vector <int> g[N];
int sg(int u)
{
    if(dp[u] != -1) return dp[u];
    set <int> st;
    for(auto x:g[u]) st.insert(sg(x));
    int mex = 0;
    while(st.count(mex)) mex++;
    return dp[u] = mex;
}
int main()
{
    int n,m,k;
    cin >> n >> m >> k;
    memset(dp,-1,sizeof(dp));
    for(int i = 1;i <= m;i++) {
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    int ans = 0;
    for(int i = 1;i <= k;i++) {
        int u;
        cin >> u;
        ans ^= sg(u);
    }
    if(ans) cout << "win" << endl;
    else cout << "lose" << endl;
    return 0;
}
