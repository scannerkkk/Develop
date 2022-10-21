//最大值，要用最短路
//因为x1 <= 2 
//    x2 <= 3
//    x3 <= 5
//那么最后的解一定是2，满足上界的最小值的

//最小值，要用最长路
//因为
// x1 >= 2
// x2 >= 3
// x3 >= 5
//那么最后的解一定是5，也就是满足下界的最大值  
#include "bits/stdc++.h"
using namespace std;
const int N = 100010;
struct node{
	int to;
	int nt;
	int wi;
}e[N * 3];
int he[N],cnt[N],vs[N],idx,stk[N * 3];
int n,m,op;
long long dis[N];
void add(int u,int v,int w)
{
	e[++idx].nt = he[u];
	e[idx].wi = w;
	e[idx].to = v;
	he[u] = idx;
}
long long spfa()
{
	long long tot = 0;
	memset(dis,-0x3f,sizeof(dis));
	dis[0] = 0;vs[0] = true;stk[0] = 0;
	int hh = 0,tt = 1;
	while(hh < tt) {
		//用栈优化负环
		int v = stk[--tt];
		vs[v] = false;
		bool f = false;
		for(int i = he[v];~i;i = e[i].nt) {
			int j = e[i].to;
			if(dis[j] < dis[v] + e[i].wi) {
				dis[j] = dis[v] + e[i].wi;
				cnt[j] = cnt[v] + 1;
				//要判到n + 1，因为还要包括源点
				if(cnt[j] >= n + 1) return -1;
				if(!vs[j]) {
					vs[j] = true;
					stk[tt++] = j;
				}
			}
		}
	}
	for(int i = 1;i <= n;i++) tot += dis[i];
	return tot;
}
int main()
{
	scanf("%d%d",&n,&m);
	memset(he,-1,sizeof(he));
	while(m--) {
		int u,v;
		scanf("%d%d%d",&op,&u,&v);
		if(op == 1) add(u,v,0),add(v,u,0);
		else if(op == 2) add(u,v,1);
		else if(op == 3) add(v,u,0);
		else if(op == 4) add(v,u,1);
		else add(u,v,0);
	}
	//建立超级源点，这个1是根据题目要求的
	for(int i = 1;i <= n;i++) add(0,i,1);
	printf("%lld",spfa());
	return 0;
}
