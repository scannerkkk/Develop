#include <bits/stdc++.h>
#define PII pair<int,int>
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define vi vector<int>
#define debug(x) cerr << "!!!" << x << endl;
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
#define fi first
#define se second
using namespace std;
char *p1,*p2,buf[100000];
const int N = 1e5 + 10;
vector<PII> e[N];
ll maxx = -1e10,dp[N];
ll A[N],B[N],C[N],D[N];
int dfn[N],fa[N],wc[N],cir[N],vis[N],si[N];
int n,tim,cnt;
void get_loop(int v)
{
	dfn[v] = ++ tim;
	for(auto to:e[v]) {
		int j = to.fi,w = to.se;
		if(j == fa[v]) continue;
		if(!dfn[j]) {
			fa[j] = v;
			wc[j] = w;
			get_loop(j);
		}
		else if(dfn[j] > dfn[v]){
			//注意这一步，扣环是边权转点的时候要特殊在起始点这条边赋值
			if(!wc[v]) wc[v] = w;
			for(;j != v;j = fa[j]) {
				cir[++cnt] = j;
				vis[j] = true;
				si[cnt] = wc[j];
			}
			cir[++cnt] = j;
			si[cnt] = wc[j];
			vis[j] = true;
		}
	}
}
void dfs(int v,int fat)
{
	for(auto to : e[v]) {
		int j = to.fi,w = to.se;
		if(vis[j] || j == fat) continue;
		dfs(j,v);
		maxx = max(maxx,dp[j] + dp[v] + w);
		dp[v] = max(dp[v],dp[j] + w);
	}
}
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++) {
		int a,b,c;
		cin >> a >> b >> c;
		e[a].push_back({b,c});
		e[b].push_back({a,c});
	}
	//扣环
	get_loop(1);
	for(int i = 1;i <= cnt;i++) dfs(cir[i],0);
	ll mx = 0,s = 0;
	//预处理前缀
	//断环	
	//A[i] 表示前面数组中最大深度加上链长
	//B[i] 表示前面数组中两棵子树最大深度 + 这两棵子树的中间长度
	//mx：一个技巧用于拼接这两棵子树的中间长度，相党羽某一棵子树的最大长度加上前缀链长度
	for(int i = 1;i <= cnt;i++) {
		s += si[i - 1];
		A[i] = max(A[i - 1],dp[cir[i]] + s);
		B[i] = max(B[i - 1],mx + dp[cir[i]] + s);
		mx = max(mx,dp[cir[i]] - s);
	}
	ll cps = si[cnt];
	//断环
	mx = s = si[cnt] = 0;
	for(int i = cnt;i >= 1;i--) {
		s += si[i];
		C[i] = max(C[i + 1],dp[cir[i]] + s);
		D[i] = max(D[i + 1],mx + dp[cir[i]] + s);
		mx = max(mx,dp[cir[i]] - s);
	}
	ll res = 1e18,tmp = 0;
	//拼接答案
	for(int i = 1;i < cnt;i++) {
		tmp = max({B[i],D[i + 1],A[i] + C[i + 1] + cps});
		res = min(res,tmp);
	}
	maxx = max(maxx,res);
	cout << fixed << setprecision(1) << maxx * 1.0 / 2 << endl;
	return 0;
}
