#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 1000100,M = 2000200;
int idx,n,cnt,tim;
int dfn[N],he[N],fa[N],vis[N],q[M],cir[M];
ll f[N],ans,mmax,s[M];
struct Edge {
    int nt;
    int to;
    int wi;
}e[M];
void add(int a,int b,int c)
{
    e[++idx].nt = he[a];
    e[idx].to = b;
    e[idx].wi = c;
    he[a] = idx;
}
//找环
void loop(int v)
{
    dfn[v] = ++ tim;
    for(int i = he[v]; ~i;i = e[i].nt) {
        int j = e[i].to;
        if(j == fa[v]) continue;
        if(dfn[j]) {
            if(dfn[j] < dfn[v]) continue;
            cir[++cnt] = j;
            while(j != v) {
                cir[++cnt] = fa[j];
                j = fa[j];
            }
        }
        else fa[j] = v,loop(j);
    }
}
//求环上每个点的子树最大直径
void dfs(int v)
{
    vis[v] = true;
    for(int i = he[v]; ~i;i = e[i].nt) {
        int j = e[i].to,w = e[i].wi;
        if(vis[j]) continue;
        dfs(j);
        mmax = max(mmax,f[v] + f[j] + w);
        f[v] = max(f[v],f[j] + w);
    }
}
//单调队列求最大答案
ll dp()
{
    ll res1 = 0,res2 = 0;
    //处理环上的点的直径
    for(int i = 1;i <= cnt;i++) {
        mmax = 0;
        dfs(cir[i]);
        res1 = max(res1,mmax);
    }
//     处理二元环
    if(cnt == 2) {
        for(int i = he[cir[1]];~i;i = e[i].nt) {
            int j = e[i].to;
            //判重边
            if(j == cir[2]) res2 = max(res2,f[cir[2]] + f[cir[1]] + e[i].wi);
        }
        return max(res1,res2);
    }
    for(int i = 1;i <= cnt;i++) {
        int dis;
        for(int j = he[cir[i]];~j;j = e[j].nt) {
            if(e[j].to == cir[i - 1]) {
                dis = e[j].wi;
                break;
            }
        }
        s[i] = s[i - 1] + dis;
    }
    //断环成链
    for(int i = 1;i < cnt;i++) s[cnt + i] = s[cnt] + s[i];
    int hh,tt;
    hh = tt = 1;
    q[1] = 0;
    for(int i = 1;i < cnt * 2;i++) {
        while(hh <= tt && q[hh] <= i - cnt) hh++;
        res2 = max(res2,f[cir[q[hh] % cnt]] + f[cir[i % cnt]] + s[i] - s[q[hh]]);
        while(hh <= tt && s[q[tt]] - f[cir[q[tt] % cnt]] >= s[i] - f[cir[i % cnt]]) tt--;
        q[++tt] = i;
    }
    return max(res1,res2);
}
ll solve(int x)
{
    cnt = 0,tim = 0;
    loop(x);
    cir[0] = cir[cnt];
    for(int i = 1;i <= cnt;i++) vis[cir[i]] = true;
    return dp();
}
int main()
{
    scanf("%d'",&n);
    memset(he,-1,sizeof(he));
    for(int i = 1;i <= n;i++) {
        int b,c;
        scanf("%d%d",&b,&c);
        add(i,b,c),add(b,i,c);
    }
    for(int i = 1;i <= n;i++) if(!vis[i]) ans += solve(i);
    printf("%lld\n",ans);
    return 0;
}
