#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10,M = 2e6 + 10;
const int inf = 0x3f3f3f3f;
struct Edge {
    int s,t,w;
    int id,rw;
}e[M];
struct Cancel {
    int pre;
    int id;
}cancel[M];
int use[M],st[N],id[N],pe[N],peId[N],in[N];
int ZL(int root,int n,int m)
{
    int res = 0,tot = m;
    while(1) {
        for(int i = 1;i <= n;i++) in[i] = inf;
        for(int i = 1;i <= m;i++) {
            if(e[i].s != e[i].t && in[e[i].t] > e[i].w) {
                in[e[i].t] = e[i].w;
                pe[e[i].t] = e[i].s;
                //记录由哪条边转移过来
                peId[e[i].t] = e[i].id;
            }
        } 
        for(int i = 1;i <= n;i++) if(i != root && in[i] == inf) return -1;
        int cnt = 0;
        memset(st,0,sizeof(st));
        memset(id,0,sizeof(id));
        in[root] = 0;
        for(int i = 1;i <= n;i++) {
            res += in[i];
            int v = i;
            //将图中用到的边保存
            if(i != root) use[peId[i]] ++;
            for(;v != root && !id[v] && st[v] != i;v = pe[v]) st[v] = i;
            if(v != root && !id[v]) {
                cnt ++;
                id[v] = cnt;
                for(int u = pe[v];u != v;u = pe[u]) id[u] = cnt;
            }
        }
        if(cnt == 0) break;
        for(int i = 1;i <= n;i++) if(!id[i]) id[i] = ++ cnt;
        for(int i = 1;i <= m;i++) {
            int v = e[i].t;
            e[i].s = id[e[i].s];
            e[i].t = id[e[i].t];
            if(e[i].s != e[i].t) {
                ++ tot;
                e[i].w -= in[v];
                //保存这条边的信息
                cancel[tot].id = e[i].id;
                cancel[tot].pre = peId[v];
                e[i].id = tot;
            }
        }
        root = id[root],n = cnt;
    }
    for(int i = tot;i > m;i--) {
        if(use[i]) {
            use[cancel[i].pre] --;
            use[cancel[i].id] ++;
        }
    }
    return res;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    int u,v,w;
    for(int i = 1;i <= m;i++) {
        scanf("%d%d%d",&e[i].s,&e[i].t,&e[i].w);
        e[i].id = i;e[i].rw = e[i].w;
    }
    int ans = ZL(1,n,m);
    printf("%d\n",ans);
    if(ans != 0 && ans != -1) {
        for(int i = 1;i <= m;i++) 
            if(use[i] && e[i].rw) 
                printf("%d ",i);
    }
    return 0;
}
