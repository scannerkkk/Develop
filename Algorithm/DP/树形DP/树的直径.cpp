#include "bits/stdc++.h"
using namespace std;
struct node{
    int nxt;
    int to;
    int wi;
}e[20010];
int idx,he[10010],ans = -1e9;
void add(int u,int v,int w)
{
    e[++idx].nxt = he[u];
    e[idx].to = v;
    e[idx].wi = w;
    he[u] = idx;
}
int dfs(int cur,int fa)
{
    int d1 = 0,d2 = 0,dis = 0;
    for(int i = he[cur];~i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        int d = dfs(e[i].to,cur) + e[i].wi;
        if(d >= d1) d2 = d1,d1 = d;
        else if(d > d2) d2 = d;
        dis = max(d,dis);
    }
    ans = max(d1 + d2,ans);
    return dis;
}
void init(int n)
{
    for(int i = 1;i <= n;i++) he[i] = -1;
}
int main()
{
    int n,u,v,w;
    cin >> n;
    init(n);
    for(int i = 1;i < n;i++) {
        cin >> u >> v >> w;
        add(u,v,w);add(v,u,w);
    }
    dfs(1,-1);
    cout << ans << endl;
    return 0;
}
