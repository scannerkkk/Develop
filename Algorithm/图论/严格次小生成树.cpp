#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 2e5 + 10,M = 4e5 + 10;
struct Edge {
    int fr,to,wi;
    bool used;
    bool operator < (const Edge &other) const {
        return other.wi > wi;
    }
}e[M];
struct MST {
    int nt,to,wi;
}t[M];
int cnt,n,m,idx,log2n = log2(N);
int f[N],he[N],dep[N],fa[N][30],mx[N][30],mxx[N][30];
ll s = 0,ans = 1e18;
void add(int a,int b,int c)
{
    t[++ idx] = {he[a],b,c};
    he[a] = idx;
}
int find(int x)
{
    return x == f[x] ? x : f[x] = find(f[x]);
}
void kruscal()
{
    for(int i = 1;i <= n;i++) f[i] = i;
    memset(he,-1,sizeof(he));
    sort(e + 1,e + 1 + m);
    for(int i = 1;i <= m;i++) {
        int fa = find(e[i].fr),fb = find(e[i].to),fc = e[i].wi;
        if(fa != fb) {
            e[i].used = true;
            f[fa] = fb;
            s += fc;
            add(e[i].fr,e[i].to,fc);add(e[i].to,e[i].fr,fc);
        }
    }
}
void dfs(int u,int fat)
{
    dep[u] = dep[fat] + 1;
    for(int i = 1;(1 << i) <= dep[u];i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        if(mx[u][i - 1] == mx[fa[u][i - 1]][i - 1]) {
            mx[u][i] = mx[u][i - 1];
            mxx[u][i] = max(mxx[fa[u][i - 1]][i - 1],mxx[u][i - 1]);
        }
        else if(mx[u][i - 1] > mx[fa[u][i - 1]][i - 1]) {
            mx[u][i] = mx[u][i - 1];
            mxx[u][i] = max(mx[fa[u][i - 1]][i - 1],mxx[fa[u][i - 1]][i - 1]);
        }
        else {
            mx[u][i] = mx[fa[u][i - 1]][i - 1];
            mxx[u][i] = max(mx[u][i - 1],mxx[fa[u][i - 1]][i - 1]);
        }
    }
    for(int i = he[u]; ~i;i = t[i].nt) {
        int j = t[i].to;
        if(j == fat) continue;
        fa[j][0] = u;mx[j][0] = t[i].wi;
        dfs(j,u);
    }
}
int lca(int x,int y)
{
    if(dep[x] < dep[y]) swap(x,y);
    int dis = dep[x] - dep[y];
    for(int i = 0;(1 << i) <= dis;i++) if((1 << i) & dis) x = fa[x][i]; 
    if(x == y) return x;
    for(int i = log2n;i >= 0;i--) {
        if(fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
ll SSMST(int x,int y,int c)
{
    int p = lca(x,y),nx = 0,nxx = 0;
    for(int i = log2n;i >= 0;i--) {
        if(dep[fa[x][i]] >= dep[p]) {
            if(nx == mx[x][i]) nxx = max(nxx,mxx[x][i]);
            if(nx >  mx[x][i]) nxx = max(nxx,mx[x][i]);
            if(nx <  mx[x][i]) nx = mx[x][i],nxx = max(nxx,mxx[x][i]);
            x = fa[x][i];
        }
        if(dep[fa[y][i]] >= dep[p]) {
            if(nx == mx[y][i]) nxx = max(nxx,mxx[y][i]);
            if(nx >  mx[y][i]) nxx = max(nxx,mx[y][i]);
            if(nx <  mx[y][i]) nx = mx[y][i],nxx = max(nxx,mxx[y][i]);
            y = fa[y][i];
        }
    }
    if(c != nx) return s - nx + c;
    else if(nxx) return s - nxx + c;
    else return (ll)1e18;
}
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= m;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        e[i] = {a,b,c,false};
    }
    kruscal();
    dfs(1,0);
    for(int i = 1;i <= m;i++) {
        if(e[i].used || e[i].fr == e[i].to) continue;
        ans = min(ans,SSMST(e[i].fr,e[i].to,e[i].wi));
    }
    cout << ans << endl;
    return 0;
}
