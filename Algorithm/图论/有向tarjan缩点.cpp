#include "bits/stdc++.h"
using namespace std;
int dfn[1100],low[1100];
int heads[1010];
//边集数组
struct node{
    int from;
    int to;
    int nxt;
}edges[10010];
//记录当前正在访问的点，也就是存储强联通分量
stack <int> que;
//标记哪几个顶点是一个强联通分量的
int color[1100];
//标记顶点是否在访问中
bool vis[1100];
//统计重新建的图的点的入度和出度
int out[1100],in[1100];
//染色，也就是标记强联通分量
int num;
int n,m;
int cnt;
int idx;
//初始化heads数组
void init()
{
    for(int i = 1;i <= n;i++)
        heads[i] = -1;
}
//邻接表存信息
void add(int u,int v)
{
    edges[++cnt].from = u;
    edges[cnt].to = v;
    edges[cnt].nxt = heads[u];
    heads[u] = cnt;
}
//tarjan算法
void tarjan(int cur)
{
    low[cur] = dfn[cur] = ++idx;
    que.push(cur);
    vis[cur] = true;
    for(int i = heads[cur];i != -1;i = edges[i].nxt){
        int v = edges[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[cur] = min(low[cur],low[v]);
        }
        else if(vis[v])
            low[cur] = min(low[cur],dfn[v]);
    }
    //统计强联通分量
    if(dfn[cur] == low[cur]){
        num++;
        int vertex;
        do{
            vertex = que.top();
            que.pop();
            color[vertex] = num;
            vis[vertex] = false;
            idx--;
        }while(vertex != cur);
    }
}
int main()
{
    cin >> n >> m;
    init();
    for(int i = 1;i <= m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
    }
    for(int i = 1;i <= n;i++)
        if(!dfn[i])
            tarjan(i);
    //打印染色情况
    for(int i = 1;i <= n;i++)
        cout << color[i] << endl;
    //重新建图
    for(int i = 1;i <= m;i++){
        int sx,sy;
        sx = color[edges[i].from];
        sy = color[edges[i].to];
        if(sx != sy){
            in[sy]++;
            out[sx]++;
        }
    }
    return 0;
}
