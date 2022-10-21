#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int dis[N],he[N],cnt,ver[N];
bool vis[N];
int n,m;
struct node{
	int w;
	int f;
	int t;
	int nxt;
}e[N];
void add(int u,int v,int w)
{
	e[++cnt].f = u;
	e[cnt].t = v;
	e[cnt].w = w;
	e[cnt].nxt = he[u];
	he[u] = cnt;
}
void init()
{
	fill(vis,vis + N,0);
	fill(he,he + N,-1);
	fill(dis,dis + N,1e9 + 10);
}
void spfa()
{
	queue <int> que;
	for(int i = 1;i <= n;i++){
	    vis[i] = true; 
	    que.push(i);
	}
	//判断负环用栈的话性能更优
	while(!que.empty()){
		int v = que.front();
		que.pop();
		//如果这个点已经在队列
		vis[v] = false;
		for(int i = he[v];i != -1;i = e[i].nxt){
			if(dis[e[i].t] > dis[e[i].f] + e[i].w){
				dis[e[i].t] = dis[e[i].f] + e[i].w;
				if(!vis[e[i].t]) {
					vis[e[i].t] = true;
					ver[e[i].t] = ver[e[i].f] + 1;
					if(ver[e[i].t] >= n){
					    //存在负环
					    cout<<"Yes"<<endl;
					    return ;
					}
					que.push(e[i].t);	
				}
			}
		}
	}
	cout<<"No"<<endl;
}
int main()
{
	cin >> n >> m;
	init();
	for(int i = 1;i <= m;i++){
		int u,v,w;
		cin >> u >> v >> w;
		add(u,v,w);
	}
	spfa();
	return 0;
}
