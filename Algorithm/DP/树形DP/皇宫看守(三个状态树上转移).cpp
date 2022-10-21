#include "bits/stdc++.h"
using namespace std;
const int N = 1510;
struct node{
    int nt;
    int to;
}e[N << 2];
int he[N],w[N],idx,dp[N][N];
bool vs[N];
//acwing1077皇宫看守
void add(int a,int b)
{
    e[++idx].to = b;
    e[idx].nt = he[a];
    he[a] = idx;
}
void dfs(int u)
{
    //在自己这里摆放侍卫
    dp[u][2] = w[u];
    for(int i = he[u]; ~i;i = e[i].nt) {
        int j = e[i].to;
        dfs(j);
        //dp[u][0]表示被父节点看到了，那么当前节点就不需要摆放侍卫，子节点是否摆放无所谓
        dp[u][0] += min(dp[j][1],dp[j][2]);
        //dp[u][2]表示自己这个点放一个侍卫，那么子节点可以被父节点看到，也可以自己摆放，也可以被子节点的子节点看到
        dp[u][2] += min({dp[j][0],dp[j][1],dp[j][2]});
    }
    //dp[u][1] 表示u点被子节点看到
    dp[u][1] = 1e9 + 10;
    for(int i = he[u]; ~i;i = e[i].nt) {
        int j = e[i].to;
        //被子节点看到时，我们要拿所有子节点的摆放值减去当前子节点被看到的最小值，然后加上当前子节点自己摆放侍卫的值
        dp[u][1] = min(dp[u][1],dp[j][2] + dp[u][0] - min(dp[j][1],dp[j][2]));
    }
}
int main()
{
    int n,root = 1;
    cin >> n;
    memset(he,-1,sizeof(he));
    for(int i = 1;i <= n;i++) {
        int id,cnt,wi,x;
        cin >> id >> wi >> cnt;
        w[id] = wi;
        for(int j = 1;j <= cnt;j++){
            cin >> x;
            add(id,x);
            vs[x] = true;
        }
    }
    while(vs[root]) root++;
    dfs(root);
    cout << min(dp[root][1],dp[root][2]) << endl;
    return 0;
}
