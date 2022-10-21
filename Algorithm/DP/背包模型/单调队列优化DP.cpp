#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
//N的极限大小为max(总体积) / min(单个体积)
const int N = 20010;
struct node{
	int v;
	int pos;
}que[N];
int f[N],hd,td;
int main()
{
	int ans = 0;
	int n,m;
	cin >> n >> m;
	for(int i = 1;i <= n;i ++){
		int u,v,s;
		cin >> u >> v >> s;
		//特判不需要体积的物品
		if(u == 0){
			ans += v * s;
			continue;
		}
		//按照体积分组
		s = min(s,m / u);
		for(int j = 0;j < u;j ++){
			hd = td = 0;
			for(int k = 0;k * u + j <= m;k ++){
				int res = k * u + j;
				//队头是旧的直接出队
				while(hd < td && que[hd].pos < k - s) hd ++;
				//把队尾没用的值去除掉
				while(hd < td && que[td - 1].v <= f[res] - k * v) td --;
				que[td].v = f[res] - k * v;
				que[td++].pos = k;
				f[res] = que[hd].v + k * v;
			}
		}
	}
	cout<< ans + f[m] <<endl;
	return 0;
}
