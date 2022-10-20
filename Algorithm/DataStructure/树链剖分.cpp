#include "bits/stdc++.h"
using namespace std;
const int N = 100010,M = 200020;
struct Edge {
    int to;
    int nt;
}e[M];
struct SegTree {
    int l,r;
    int s,lazy;
}seg[N << 2];
int idx,mod,a[N],tim;
int dfn[N],fat[N],son[N],siz[N],he[N],wei[N],top[N],dep[N];
void add(int a,int b)
{
    e[++idx].nt = he[a];
    e[idx].to = b;
    he[a] = idx;
}
//边权转点权 把边的权值给到下一个节点，查区间的时候用[son[l],r]
//如果l == r就不能继续算下去了，因为会出错
void init()
{
    idx = tim = 0;
    memset(dfn,0,sizeof(dfn));
    memset(siz,0,sizeof(siz));
    memset(he,-1,sizeof(he));
    memset(dep,0,sizeof(dep));
}
void push_up(int u)
{
    seg[u].s = (seg[u << 1].s + seg[u << 1 | 1].s) % mod; 
}
void push_down(int u)
{
    seg[u << 1].s = (seg[u << 1].s + (seg[u].lazy * (seg[u << 1].r - seg[u << 1].l + 1))) % mod;
    seg[u << 1].lazy = (seg[u].lazy + seg[u << 1].lazy) % mod;
    seg[u << 1 | 1].s = (seg[u << 1 | 1].s + (seg[u].lazy * (seg[u << 1 | 1].r - seg[u << 1 | 1].l + 1))) % mod;
    seg[u << 1 | 1].lazy = (seg[u].lazy + seg[u << 1 | 1].lazy) % mod;
    seg[u].lazy = 0;
}
void build(int u,int l,int r)
{
    if(l == r) seg[u] = {l,r,wei[l],0};
    else {
        seg[u] = {l,r,0,0};
        int mid = (l + r) >> 1;
        build(u << 1,l,mid);
        build(u << 1 | 1,mid + 1,r);
        push_up(u);
    }
}
void modify(int u,int l,int r,int v)
{
    if(seg[u].l >= l && seg[u].r <= r) {
        seg[u].s = (seg[u].s + v * (seg[u].r - seg[u].l + 1)) % mod;
        seg[u].lazy = (seg[u].lazy + v) % mod;
    }
    else {
        push_down(u);
        int mid = (seg[u].l + seg[u].r) >> 1;
        if(l <= mid) modify(u << 1,l,r,v);
        if(r > mid) modify(u << 1 | 1,l,r,v);
        push_up(u);
    }
}
int query(int u,int l,int r)
{
    if(seg[u].l >= l && seg[u].r <= r) return seg[u].s;
    else {
        int s = 0,mid;
        push_down(u);
        mid = (seg[u].l + seg[u].r) >> 1;
        if(l <= mid) s = (s + query(u << 1,l,r)) % mod;
        if(r > mid) s = (s + query(u << 1 | 1,l,r)) % mod;
        return s;
    }
}
//预处理重儿子
void dfs1(int cur,int fa)
{
    dep[cur] = dep[fa] + 1;
    siz[cur] = 1;
    fat[cur] = fa;
    for(int i = he[cur]; ~i;i = e[i].nt) {
        int j = e[i].to;
        if(j == fa) continue;
        dfs1(j,cur);
        siz[cur] += siz[j];
        if(siz[j] > siz[son[cur]]) son[cur] = j;
    }
}
//剖分重链
void dfs2(int cur,int fa)
{
    dfn[cur] = ++ tim;
    top[cur] = fa;
    wei[tim] = a[cur];
    if(!son[cur]) return ;
    dfs2(son[cur],fa);
    for(int i = he[cur]; ~i;i = e[i].nt) {
        int j = e[i].to;
        if(j == fat[cur] || j == son[cur]) continue;
        dfs2(j,j);
    }
}
//子树加z
void moson(int x,int z)
{
    modify(1,dfn[x],dfn[x] + siz[x] - 1,z);
}
//查询子树
int quson(int x)
{
    return query(1,dfn[x],dfn[x] + siz[x] - 1);
}
//不同重链上的添加操作
void mochain(int x,int y,int z)
{
    z %= mod;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        modify(1,dfn[top[x]],dfn[x],z);
        x = fat[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    modify(1,dfn[x],dfn[y],z);
}
//不同重链上的查询操作
int quchain(int x,int y)
{
    int s = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        s = (s + query(1,dfn[top[x]],dfn[x])) % mod;
        x = fat[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    s = (s + query(1,dfn[x],dfn[y])) % mod;
    return s;
}
int main()
{
    int n,m,r;
    scanf("%d%d%d%d",&n,&m,&r,&mod);
    init();
    for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
    while(n > 1) {
        int u,v;
        n --;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    
    dfs1(r,r);
    dfs2(r,r);
    build(1,1,tim);
    
    while(m --) {
        int op,x,y,z;
        scanf("%d",&op);
        if(op == 1) {
            scanf("%d%d%d",&x,&y,&z);
            mochain(x,y,z);
        }
        else if(op == 2) {
            scanf("%d%d",&x,&y);
            printf("%d\n",quchain(x,y));
        }
        else if(op == 3) {
            scanf("%d%d",&x,&z);
            moson(x,z);
        }
        else if(op == 4) {
            scanf("%d",&x);
            printf("%d\n",quson(x));
        }
    }
    return 0;
}
