#include "bits/stdc++.h"
using namespace std;
typedef pair<int,int> PII;
const int N = 1e4+10;
int res[N << 1],he[N],vis[N],dis[N],fa[N],cnt;
vector<PII> query[N << 1];
struct node{
	int to;
	int wi;
	int nxt;
}edge[N << 1];
//O(n+m)
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void add(int u,int v,int w)
{
	edge[++cnt].to = v;
	edge[cnt].nxt = he[u];
	edge[cnt].wi = w;
	he[u] = cnt;
}
void dfs(int u,int fa)
{
	for(int i = he[u];i != -1;i = edge[i].nxt){
		if(edge[i].to == fa) continue;
		dis[edge[i].to] = dis[u] + edge[i].wi;
		dfs(edge[i].to,u);
	}
}
void tarjan(int u)
{
	vis[u] = 1;
	for(int i = he[u];i != -1;i = edge[i].nxt){
		if(!vis[edge[i].to]){
			tarjan(edge[i].to);
			fa[edge[i].to] = u;
		}
	}

	for(auto it:query[u]){
		int to = it.first,th = it.second;
		if(vis[to] == 2){
			int fy = find(to);
			res[th] = dis[u] + dis[to] - 2 * dis[fy];
		}
	}
	vis[u] = 2;
}
int main()
{
	memset(he,-1,sizeof(he));
	for(int i = 1;i < N;i++) fa[i] = i;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n - 1;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	for(int i = 1;i <= m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x == y) continue;//自环
		query[x].push_back({y,i});
		query[y].push_back({x,i});
	}
	dfs(1,-1);
	tarjan(1);
	for(int i = 1;i <= m;i++) printf("%d\n",res[i]);
	return 0;
}
