#include "bits/stdc++.h"
using namespace std;
const int N = 100010;
struct node{
	int nxt;
	int to;
}edge[2 * N];
int log2n = (int)(log(N) / log(2) + 0.5);
int deep[N],fa[N][20],he[N],cnt;
void add(int u,int v)
{
	edge[++cnt].nxt = he[u];
	edge[cnt].to = v;
	he[u] = cnt;
}
void getdeep(int now,int father)
{
	deep[now] = deep[father] + 1;
	fa[now][0] = father;
	for(int i = 1;(1 << i) <= deep[now];i++) fa[now][i] = fa[fa[now][i - 1]][i - 1];
	for(int i = he[now];i != -1;i = edge[i].nxt){
		if(edge[i].to == father) continue;
		getdeep(edge[i].to,now);
	}
}
int lca(int u,int v)
{
	if(deep[u] < deep[v]) swap(u,v);
	int d = deep[u] - deep[v];
	for(int i = 0;(1 << i) <= d;i++) {
		//说明可以从u往上跳2^i方步
		if((1 << i) & d) u = fa[u][i];
	}
	//如果u跳到了v
	if(u == v) return u;
	//log2n(以2为底)，uv同层不同节点，跳到同一个子树下
	for(int i = log2n;i >= 0;i--){
		if(fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}
int main()
{
	memset(he,-1,sizeof(he));
	int n,root,u,v;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&u,&v);
		if(v==-1) root=u;
		else {
			add(u,v);
			add(v,u);
		}
	}
	getdeep(root,0);
	int m;
	scanf("%d",&m);
	while(m--) {
		scanf("%d%d",&u,&v);
		int res = lca(u,v);
		if(res == u) puts("1");
		else if(res == v) puts("2");
		else puts("0");
	}
	return 0;
}
