#include "bits/stdc++.h"
#define fastIO ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
using namespace std;
using ll = long long;
const int N = 1e5 + 10,M = 2e5 + 20;
struct Edge {
    int to;
    int nt;
    int wi;
}e[M];
//lazy1是定值w，lazy2是都加上w
struct Seg {
    int l,r;
    ll mx,lazy1,lazy2;
}seg[M << 1];
int dfn[N],son[N],top[N],siz[N],he[N],a[N],fa[N],wei[N],dep[N];
int idx,tim;
void add(int a,int b,int c)
{
    e[++idx] = {b,he[a],c};
    he[a] = idx;
}
void push_up(int u)
{
    seg[u].mx = max(seg[u << 1].mx,seg[u << 1 | 1].mx);
}
void push_down(int u)
{
    if(~seg[u].lazy1) {
        seg[u << 1].mx = seg[u << 1 | 1].mx = seg[u].lazy1;
        seg[u << 1].lazy1 = seg[u << 1 | 1].lazy1 = seg[u].lazy1;
        seg[u << 1].lazy2 = seg[u << 1 | 1].lazy2 = 0;
        seg[u].lazy1 = -1;
    }
    if(seg[u].lazy2) {
        seg[u << 1].mx += seg[u].lazy2;
        seg[u << 1 | 1].mx += seg[u].lazy2;
        seg[u << 1].lazy2 += seg[u].lazy2;
        seg[u << 1 | 1].lazy2 += seg[u].lazy2;
        seg[u].lazy2 = 0;
    }
}
void dfs1(int cur,int fat)
{
    siz[cur] = 1;
    dep[cur] = dep[fat] + 1;
    fa[cur] = fat;
    for(int i = he[cur];~i;i = e[i].nt) {
        int j = e[i].to,w = e[i].wi;
        if(j == fat) continue;
        dfs1(j,cur);
        siz[cur] += siz[j];
        a[j] = w;
        if(siz[son[cur]] < siz[j]) son[cur] = j;
    }
}
void dfs2(int cur,int fat)
{
    dfn[cur] = ++ tim;
    wei[tim] = a[cur];
    top[cur] = fat;
    if(son[cur]) dfs2(son[cur],fat);
    for(int i = he[cur]; ~i;i = e[i].nt) {
        int j = e[i].to;
        if(j == fa[cur] || j == son[cur]) continue;
        dfs2(j,j);
    }
}
void build(int u,int l,int r)
{
    if(l == r) seg[u] = {l,r,wei[l],-1,0};
    else {
        seg[u] = {l,r,0,-1,0};
        int mid = (l + r) >> 1;
        build(u << 1,l,mid); 
        build(u << 1 | 1,mid + 1,r);
        push_up(u);
    }
}
ll query(int u,int l,int r)
{
    if(seg[u].l >= l && seg[u].r <= r) return seg[u].mx;
    else {
        ll mx = 0;
        push_down(u);
        int mid = (seg[u].l + seg[u].r) >> 1;
        if(l <= mid) mx = max(mx,query(u << 1,l,r));
        if(r > mid) mx = max(mx,query(u << 1 | 1,l,r));
        return mx;
    }
}
void modify1(int u,int l,int r,int v)
{
    if(seg[u].l >= l && seg[u].r <= r) {
        seg[u].mx = v;
        seg[u].lazy1 = v;
        seg[u].lazy2 = 0;
    }
    else {
        push_down(u);
        int mid = (seg[u].l + seg[u].r) >> 1;
        if(l <= mid) modify1(u << 1,l,r,v);
        if(r > mid) modify1(u << 1 | 1,l,r,v);
        push_up(u);
    }
}
void modify2(int u,int l,int r,int v)
{
    if(seg[u].l >= l && seg[u].r <= r) {
        seg[u].lazy2 += v;
        seg[u].mx += v;
    }
    else {
        push_down(u);
        int mid = (seg[u].l + seg[u].r) >> 1;
        if(l <= mid) modify2(u << 1,l,r,v);
        if(r > mid) modify2(u << 1 | 1,l,r,v);
        push_up(u);
    }
}
void mochain1(int x,int y,int v)
{
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        modify1(1,dfn[top[x]],dfn[x],v);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    modify1(1,dfn[x] + 1,dfn[y],v);
}
void mochain2(int x,int y,int v)
{
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        modify2(1,dfn[top[x]],dfn[x],v);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    modify2(1,dfn[x] + 1,dfn[y],v);
}
ll quchain(int x,int y)
{
    ll mx = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        mx = max(mx,query(1,dfn[top[x]],dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    mx = max(mx,query(1,dfn[x] + 1,dfn[y]));
    return mx;
}
int main()
{
    fastIO;
    int n;
    cin >> n;
    memset(he,-1,sizeof(he));
    for(int i = 1;i < n;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);add(b,a,c);
    }
    dfs1(1,1);
    dfs2(1,1);
    build(1,1,n);
    string op;
    while(cin >> op) {
        int l,r,v;
        if(op[0] == 'S') break;
        if(op[0] == 'M') {
            cin >> l >> r;
            cout << quchain(l,r) << endl;
        }
        if(op[1] == 'o') {
            cin >> l >> r >> v;
            mochain1(l,r,v);
        }
        if(op[0] == 'A') {
            cin >> l >> r >> v;
            mochain2(l,r,v);
        }
        if(op[1] == 'h') {
            cin >> l >> v;
            l = (dep[e[l * 2].to] > dep[e[l * 2 - 1].to]) ? e[l * 2].to : e[l * 2 - 1].to;
            modify1(1,dfn[l],dfn[l],v);
        }
    }
    return 0;
}
