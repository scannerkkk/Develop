#include "bits/stdc++.h"
#define PII pair<int,int>
using namespace std;
//多源bfs回先把某些特殊的节点先放入队列
const int N = 1010;
char mp[N][N];
int dis[N][N],vis[N][N],n,m;
int mx[] = {0,1,-1,0};
int my[] = {1,0,0,-1};
void bfs()
{
	queue <PII> que;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < m;j++)
			if(mp[i][j] == '1')
				dis[i][j] = 0,que.push({i,j}),vis[i][j] = 1;
	while(!que.empty()) {
		PII v = que.front();
		que.pop();
		for(int i = 0;i < 4;i++){
			int dx = v.first + mx[i];
			int dy = v.second + my[i];
			if(dx < 0 || dx >= n || dy < 0 || dy >= m) continue;
			if(vis[dx][dy]) continue;
			dis[dx][dy] = dis[v.first][v.second] + 1;
			vis[dx][dy] = true;
			que.push({dx,dy});
		}
	}
}
int main()
{
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d",&n,&m);
	for(int i = 0;i < n;i++) scanf("%s",mp + i);
	bfs();
	for(int i = 0;i < n;i++)
		for(int j = 0;j < m;j++)
			printf("%d%c",dis[i][j],(j==m-1)?'\n':' ');
	return 0;
}
