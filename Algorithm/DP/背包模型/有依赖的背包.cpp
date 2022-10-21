///有依赖的背包  （树形dp）
#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int dp[N][N],v[110],u[110];
//dp[x][v]表达选择以x为子树的物品，在容量不超过v时所获得的最大价值
vector<int> e[N];
int n,m,root,p;
void dfs(int fa)
{
    for(int i = u[fa];i <= m;i++) dp[fa][i] = v[fa];
    //点x必须选，所以初始化dp[x][w[x] ~ m]= v[x]
    for(auto x: e[fa]){
        dfs(x);

        //把体积分组背包一下
        //i的范围为w[x]~m, 小于w[fa]无法选择以fa为子树的物品
        for(int i = m;i >= u[fa];i--)
        //分给子树x的空间不能大于i-w[fa],不然都无法选根物品fa
            for(int j = 0;j <= i - u[fa];j++)
                dp[fa][i] = max(dp[fa][i],dp[fa][i - j] + dp[x][j]);
    }
}
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        cin >> u[i] >> v[i] >> p;
        if(p == -1) root = i;
        else e[p].push_back(i);
    }
    dfs(root);
    cout<<dp[root][m]<<endl;
    return 0;
}
