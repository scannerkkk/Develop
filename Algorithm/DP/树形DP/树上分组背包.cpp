#include "bits/stdc++.h"
using namespace std;
const int N = 110;
struct node{
    int nt;
    int to;
    int wi;
}e[N << 1];
int dp[N][N],he[N],cnt;
int m,n;
void add(int a,int b,int c)
{
    e[++cnt].nt = he[a];
    e[cnt].to = b;
    e[cnt].wi = c;
    he[a] = cnt;
}
//acwing1074
//类似于有依赖的背包，首先枚举子树（物品组），然后枚举操作数（体积），最后枚举选择（决策）
void dfs(int u,int fa)
{
    for(int i = he[u];~i;i = e[i].nt){
        int son = e[i].to;
        if(son == fa) continue;
        dfs(son,u);
        for(int j = m;j >= 1;j--){
            for(int k = 0;k < j;k++) {
                dp[u][j] = max(dp[u][j],dp[u][j - k - 1] + e[i].wi + dp[son][k]);
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    memset(he,-1,sizeof(he));
    for(int i = 1;i < n;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        add(b,a,c);
    }
    dfs(1,-1);
    cout << dp[1][m] << endl;
    return 0;
}
