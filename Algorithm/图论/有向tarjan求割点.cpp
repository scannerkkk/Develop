#include "bits/stdc++.h"
using namespace std;
const int N = 2e4;
bool cut[N + 10];
int dfn[N + 10],low[N + 10];
int idx;
int n,m;
int heads[N + 10];
struct node{
    int to;
    int nxt;
}edges[200010];
int cnt;
void add(int u,int v)
{
    edges[++cnt].to = v;
    edges[cnt].nxt = heads[u];
    heads[u] = cnt;
}
void init()
{
    for(int i = 1;i <= N + 10;i++)
        heads[i] = -1;
}
void tarjan(int cur,int fa,int root)
{
    int v;
    int child = 0;
    dfn[cur] = low[cur] = ++idx;
    for(int i = heads[cur];i != -1;i = edges[i].nxt){
        v = edges[i].to;
        if(!dfn[v]){
            child++;
            tarjan(v,cur,root);
            low[cur] = min(low[cur],low[v]);
            if(cur == root && child >= 2)
                cut[cur] = true;
            if(cur != root && low[v] >= dfn[cur])
                cut[cur] = true;
        }
        //防止从儿子访问父亲
        else if(v != fa)
            low[cur] = min(low[cur],dfn[v]);
    }
}
int main()
{
    cin >> n >> m;
    init();
    for(int i = 1;i <= m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }
    for(int i = 1;i <= n;i++)
        if(!dfn[i])
            tarjan(i,i,i);
    int ans = 0;
    for(int i = 1;i <= n;i++)
        ans += cut[i];
    cout << ans << endl;
    for(int i = 1;i <= n;i++)
        if(cut[i])
            cout << i << ' ';
    return 0;
}
