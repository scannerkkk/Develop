#include "bits/stdc++.h"
using namespace std;
const int M = 20010,N = 5010;
struct node {
    int nt;
    int to;
}e[M];
int dfn[N],low[N],he[N],bridge[M],id[N],d[N];
int dcc,idx,clk;
stack <int> stk;
void add(int a,int b)
{
    e[idx].nt = he[a];
    e[idx].to = b;
    he[a] = idx ++;
}
//此处fa表示从哪条边来 i ^ 1必须边从0开始
void tarjan(int now,int fa)
{
    dfn[now] = low[now] = ++ clk;
    stk.push(now);
    for(int i = he[now];~i;i = e[i].nt) {
        int j = e[i].to;
        if(!dfn[j]) {
            tarjan(j,i);
            low[now] = min(low[now],low[j]);
            if(dfn[now] < low[j])  bridge[i] = bridge[i ^ 1] = 1;
        }
        else if(i != (fa ^ 1)) low[now] = min(low[now],dfn[j]);
    }
    if(dfn[now] == low[now]) {
        ++ dcc;
        int v;
        do {
            v = stk.top();
            stk.pop();
            id[v] = dcc;
        }while(v != now);
    }
}
int main()
{
    int n,m;
    memset(he,-1,sizeof(he));
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    tarjan(1,-1);
    int res = 0;
    //缩点之后 + 1然后除以2，就能得出当前图距离强连通分量最少要多少边就可以变成强连通图
    for(int i = 0;i < idx;i++) if(bridge[i]) d[id[e[i].to]] ++;
    for(int i = 1;i <= dcc;i++) if(d[i] == 1) res ++;
    printf("%d\n",(res + 1) / 2);
    return 0;
}
