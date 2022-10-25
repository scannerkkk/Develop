#include "bits/stdc++.h"
using namespace std;
const int N =110,M = 10010;
const int inf = 0x3f3f3f3f;
int in[N],pe[N],id[N],st[N];
struct Edge {
    int s,t,w;
}e[M];
int ZL(int root,int n,int m)
{
    int ans = 0;
    while(true) {
        for(int i = 1;i <= n;i++) in[i] = inf;
        for(int i = 1;i <= m;i++) {
            int s = e[i].s,t = e[i].t,w = e[i].w;
            if(s != t && w < in[t]) {
                in[t] = w;
                pe[t] = s;
            }
        }
        //无最小树形图
        for(int i = 1;i <= n;i++) if(i != root && in[i] == inf) return -1;
        int cnt = 0;
        memset(st,0,sizeof(st));
        memset(id,0,sizeof(id));
        in[root] = 0;
        for(int i = 1;i <= n;i++) {
            ans += in[i];
            int v = i;
            while(st[v] != i && !id[v] && v != root) st[v] = i,v = pe[v];
            //找到环 打上标记
            if(v != root && !id[v]) {
                cnt ++;
                for(int u = pe[v];u != v;u = pe[u]) id[u] = cnt;
                id[v] = cnt;
            } 
        }
        //无环算法结束
        if(cnt == 0) break;
        //处理孤立点
        for(int i = 1;i <= n;i++) if(!id[i]) id[i] = ++ cnt;
        for(int i = 1;i <= m;i++) {
            int v = e[i].t;
            e[i].s = id[e[i].s];
            e[i].t = id[e[i].t];
            //不在同一个环
            if(e[i].s != e[i].t) e[i].w -= in[v];
        }
        //重复处理
        n = cnt;
        root = id[root];
    }
    return ans;
}
int main()
{
    int n,m,r;
    cin >> n >> m >> r;
    for(int i = 1;i <= m;i++) cin >> e[i].s >> e[i].t >> e[i].w;
    cout << ZL(r,n,m) << endl;
    return 0;
}
