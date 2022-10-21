#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10,M = 1e6 + 10;
int tr[N][26],cnt[N],fail[N],idx,ans;
char s[M];
bool vis[N];
void insert()
{
	int root = 0;
	for(int i = 0;s[i];i++) {
		int t = s[i] - 'a';
		if(!tr[root][t]) tr[root][t] = ++idx;
		root = tr[root][t];
	}
	cnt[root]++;
}
void build()
{
	queue<int> que;
	int root = 0,p;
	for(int i = 0;i < 26;i++) if(tr[root][i]) que.push(tr[root][i]);
	while(que.size()) {
		root = que.front();
		que.pop();
		for(int i = 0;i < 26;i++) {
			p = tr[root][i];
			//去上一层的匹配失败需要跳转的那个位置
			if(!p) tr[root][i] = tr[fail[root]][i];
			else {
				//去上一层的i这个位置
				fail[p] = tr[fail[root]][i];
				que.push(p);
			}
		}
	} 
}
void match()
{
	for(int i = 0,j = 0;s[i];i++) {
		int nxt = s[i] - 'a';
		j = tr[j][nxt];
		int p = j;
		while(p) {
			if(vis[p]) break;
			vis[p] = true;
			ans += cnt[p];
			cnt[p] = 0;
			p = fail[p];
		}
	}
}
void init()
{
	idx = ans = 0;
	memset(tr,0,sizeof(tr));
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
	memset(fail,0,sizeof(fail));
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T --) {
		int n;
		init();
		scanf("%d",&n);
		for(int i = 1;i <= n;i++) {
			scanf("%s",s);
			insert();
		}
		build();
		scanf("%s",s);
		match();
		printf("%d\n",ans);
	}
	return 0;
}
