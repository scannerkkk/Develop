#include "bits/stdc++.h"
using ll = long long;
using namespace std;
const int mod = 1e9 + 7,N = 305;

ll mat[N][N];

ll gauss(int n,ll f[N][N])
{
	ll res = 1;
	for(int i = 2;i <= n;i++) {
		for(int j = i + 1;j <= n;j++) {
			while(f[i][i]) {
				ll v = f[j][i] / f[i][i];
				for(int k = i;k <= n;k++) f[j][k] = (f[j][k] - f[i][k] * v % mod + mod) % mod;
				swap(f[i],f[j]);
				res = -res;	
			}
			swap(f[i],f[j]);
			res = -res;
		}
		res = res * f[i][i] % mod;
	}
	return (res + mod) % mod;
}
int main()
{
	int n,m,t;
	int u,v,w;
	scanf("%d%d%d",&n,&m,&t);
	for(int i = 1;i <= m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		if(!t) {
			mat[u][u] = (mat[u][u] + w) % mod;
			mat[v][v] = (mat[v][v] + w) % mod;
			mat[u][v] = (mat[u][v] - w) % mod;
			mat[v][u] = (mat[v][u] - w) % mod;
		}
		else {
			//有向图u--->v 等价于v的度数矩阵加，v---->u的邻接矩阵减
			mat[v][v] = (mat[v][v] + w) % mod;
			mat[v][u] = (mat[v][u] - w) % mod;
		}
	}
	printf("%lld",gauss(n,mat));
	return 0;
}
