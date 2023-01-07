#include "bits/stdc++.h"
using namespace std;
int n,m;
int dfn[100010];
int low[100010];
int heads[100010];
struct node{
    int to;
    int nxt;
}edges[200010];
int ans;
int cnt;
int idx;
void init()
{
    for(int i = 1;i <= n;i++)
        heads[i] = -1;
}
void add(int u,int v)
{
    edges[++cnt].to = v;
    edges[cnt].nxt = heads[u];
    heads[u] = cnt;
}
void tarjan(int cur,int fa)
{
    dfn[cur] = low[cur] = ++idx;
    for(int i = heads[cur];i != -1;i = edges[i].nxt){
        int v = edges[i].to;
        if(!dfn[v]){
            tarjan(v,cur);
            low[cur] = min(low[cur],low[v]);
            if(low[v] > dfn[cur])
                cout << cur << "->" << v << endl;
        }
        else if(v != fa)
            low[cur] = min(low[cur],dfn[v]);
    }
}
int main()
{
    cin >> n >> m;
    init();
    int u,v;
    for(int i = 1;i <= m;i++){
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }
    for(int i = 1;i <= n;i++)
        if(!dfn[i])
            tarjan(i,i);
    return 0;
}
