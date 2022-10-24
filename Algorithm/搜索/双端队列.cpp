#include "bits/stdc++.h"
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
//双端队列bfs适用于只有01权值的图
int n,m;
int dis[510][510];
char mp[510][510],cs[6] = "\\/\\/";
bool vs[510][510];
int mx[] = {-1,-1,1,1};
int my[] = {-1,1,1,-1};
int ix[] = {-1,-1,0,0};
int iy[] = {-1,0,0,-1};
int bfs()
{
	deque<PII> que;
	que.push_front({0,0});
	memset(vs,0,sizeof(vs));
	memset(dis,0x3f,sizeof(dis));
	dis[0][0] = 0;
	while(que.size()){
		PII v = que.front();
		que.pop_front();
		if(v.fi == n && v.se == m) return dis[n][m];
		if(vs[v.fi][v.se]) continue;
		vs[v.fi][v.se] = true;
		for(int i = 0;i < 4;i ++){
			int dx = v.fi + mx[i];
			int dy = v.se + my[i];
			if(dx < 0 || dx > n || dy < 0 || dy > m) continue;
			int ga = v.fi + ix[i];
			int gb = v.se + iy[i];
			int wi = (mp[ga][gb] != cs[i]);
			//不等于要转向
			int d = dis[v.fi][v.se] + wi;
			if(d < dis[dx][dy]) {
				dis[dx][dy] = d;
				if(wi) que.push_back({dx,dy});
				else que.push_front({dx,dy});
			}
		}
	}
	return 0;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i = 0;i < n;i++) scanf("%s",mp + i);
		if(n + m & 1) puts("NO SOLUTION");
		else printf("%d\n",bfs());
	}
	return 0;
}
