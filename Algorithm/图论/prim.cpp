#include "bits/stdc++.h"
using namespace std;
const int N = 510;
int E[N][N],dis[N],vis[N];
int n,m;

void prim()
{
    int res = 0;
    //初始化每个字节都是0x3f，（注意每个数是0x3f3f3f）
    memset(dis,0x3f,sizeof(dis));
    dis[1] = 0;
    for(int i = 0;i < n;i++){
        int t = -1;
        for(int j = 1;j <= n;j++){
            if(!vis[j] && (t == -1 || dis[t] > dis[j]))
                t = j;
        }
        if(dis[t] == 0x3f3f3f3f){
            cout<<"impossible"<<endl;
            return ;
        }
        res += dis[t];
        vis[t] = true;
        for(int j = 1;j <= n;j++)  dis[j] = min(dis[j],E[t][j]);
    }
    cout<<res<<endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    memset(E,0x3f,sizeof(E));
    while(m--){
        int u,v,w;
        cin >> u >> v >> w;
        E[u][v] = E[v][u] = min(E[u][v],w);
    }
    prim();
    return 0;
}
