#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 210,M = 40010;
struct Edge {
    int nt,to;
    ll wi;
}e[M];
ll w[N][N];
int idx,he[N],dep[N],vis[N],cur[N];
int n,m,s,t;
void add(int a,int b,ll c)
{
    e[idx] = {he[a],b,c};
    he[a] = idx ++;
}
int bfs()
{
    queue <int> que;
    memset(dep,0,sizeof(dep));
    dep[s] = 1;que.push(s);
    cur[s] = he[s];
    while(que.size()) {
        int v = que.front();
        que.pop();
        for(int i = he[v];~i;i = e[i].nt) {
            int j = e[i].to;
            if(e[i].wi && !dep[j]) {
                dep[j] = dep[v] + 1;
                cur[j] = he[j];
                que.push(j);
                if(j == t) return 1;
            }
        }
    }
    return dep[t];
}
ll dfs(int u,ll in)
{
    if(u == t) return in;
    ll out = 0;
    for(int i = cur[u];~i;i = e[i].nt) {
        int j = e[i].to;
        cur[u] = i;
        if(dep[j] == dep[u] + 1 && e[i].wi) {
            ll d = dfs(j,min(in,e[i].wi));
            if(!d) continue;
            e[i].wi -= d;e[i ^ 1].wi += d;
            in -= d;out += d;
            if(in <= 0) break;
        }
    }
    return out;
}
void Dinic()
{
    ll ans = 0;
    cin >> n >> m >> s >> t;
    memset(he,-1,sizeof(he));
    for(int i = 1;i <= m;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        w[a][b] += c;
    }
    for(int i = 1;i <= n;i++) 
        for(int j = i + 1;j <= n;j++) {
            add(i,j,w[i][j]);
            add(j,i,w[j][i]);
        }   
    while(bfs()) ans += dfs(s,1e18);
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    Dinic();
    return 0;
}
