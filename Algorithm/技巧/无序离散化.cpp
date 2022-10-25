#include "bits/stdc++.h"
using namespace std;
struct node{
	int x;
	int y;
	int e;
}edge[2000010];
int f[2000010],cnt;
unordered_map<int,int> mp;
//利用map离散化
int get(int u)
{
	if(!mp.count(u)) mp[u] = ++cnt;
	return mp[u];
}
int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}
int main()
{
	int t;
	cin >> t;
	while(t--){
		int n,x,y,e;
		mp.clear();
		cnt = 0;
		cin >> n;
		for(int i = 1;i <= n;i++){
			cin >> x >> y >> e;
			edge[i] = {get(x),get(y),e};
		}

		//注意这里cnt是离散化的大小，不一定等于初始化的n的大小
		for(int i = 1;i <= cnt;i++) f[i] = i;

		for(int i = 1;i <= n;i++){
			if(edge[i].e == 1) {
				f[find(edge[i].x)] = find(edge[i].y);
			}
		}

		bool ok = true;
		for(int i = 1;i <= n;i++){
			if(edge[i].e == 0){
				if(find(edge[i].x) == find(edge[i].y)){
					ok = false;
					break;
				}
			}
		}

		if(ok) puts("YES");
		else puts("NO");
	}
	return 0;
}
