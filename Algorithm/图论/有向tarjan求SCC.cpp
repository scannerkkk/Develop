#include "bits/stdc++.h"
using namespace std;
struct node{
    int v;
    int nxt;
}edges[2010];
int vis[2110],dfn[2110],low[2110];//dfn表示第几个被dfs到，vis表示该点是否在栈中，表示已经搜过了，low表示最早能够回溯到的位置
int heads[2110];
int cnt,idx;
int n,m,ans;
stack <int> scc;
void init()
{
    for(int i = 1;i <= n;i++)
        heads[i] = -1;
}
void tarjan(int x)
{
    low[x] = dfn[x] = ++idx;
    vis[x] = 1;
    scc.push(x);
    for(int i = heads[x]; i != -1;i = edges[i].nxt){
        //如果这个点没有搜过，那就搜下去
        if(!dfn[edges[i].v]){
            tarjan(edges[i].v);
            //更新最早能够回溯到的位置
            low[x] = min(low[x],low[edges[i].v]);
        }
        //如果这个边已经被访问过啦，就是说防止从儿子边访问父亲边
        else if(vis[edges[i].v])
            //注意这里dfn[edges[i].v]，因为这样子写就不会把其他的节点牵扯进来，dfn是没有改变的，但是low[edges[i].v]可能会被其他强联通连进去，因此求割点时不能比较low[x] 和 low[edges[i].v]
            low[x] = min(low[x],dfn[edges[i].v]);
    }
    //强联通分量
    if(dfn[x] == low[x]){
        int v;
        do {
            v = scc.top();
            scc.pop();
            cout << v << ' ';//打印SCC
            vis[v] = false;//为什么要标记为false呢，因为我可能还会从其他地方访问这个点。
            idx--;
        }while(v != x);
        cout << '\n';
    }
}
void add(int x,int y)
{
    edges[++cnt].nxt = heads[x];
    edges[cnt].v = y;
    heads[x] = cnt;
}
int main()
{
    //输入顶点个数和边条数
    cin >> n >> m;
    //初始化heads数组
    init();
    //链式前向星存储图（就是邻接表）
    for(int i = 1;i <= m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
    }
    for(int i = 1;i <= n;i++)
        //可能存在孤立点也是强联通分量，也就是图可能不连通所以每个点都要遍历一遍
        if(!dfn[i])
            tarjan(i);
    return 0;
}
