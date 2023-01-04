#include "bits/stdc++.h"
#define va(x) tr[x].v
#define son(x,k) tr[x].s[k]
#define sz(x) tr[x].siz
#define fa(x) tr[x].p
using namespace std;
const int N = 3e6 + 10;
const int INF = 1e9 + 10;
struct Node {
	int p,v,siz;
	int s[2];
	void init(int _p,int _v) {
		p = _p,v = _v;
		siz = 1;
	}
}tr[N];
struct Segment {
	int l,r,root;
}seg[N << 2];
int idx,w[N];
void push_up(int x)
{
	sz(x) = sz(son(x,0)) + sz(son(x,1)) + 1;
}
int get_k(int root,int v)
{
	int x = root,res = 0;
	while(x) {
		if(va(x) < v) res += sz(son(x,0)) + 1,x = son(x,1);
		else x = son(x,0);
	}
	return res;
}
void rotate(int x)
{
	int y = fa(x),z = fa(y),k = son(y,1) == x;
	son(z,son(z,1) == y) = x,fa(x) = z;
	son(y,k) = son(x,k ^ 1),fa(son(x,k ^ 1)) = y;
	son(x,k ^ 1) = y,fa(y) = x;
	push_up(y),push_up(x);
}
void splay(int &root,int x,int k)
{
	while(fa(x) != k) {
		int y = fa(x),z = fa(y);
		if(z != k) {
			(son(y,1) == x) ^ (son(z,1) == y) ? rotate(x) : rotate(y);
		}
		rotate(x);
	}
	if(!k) root = x;
}
void insert(int &root,int v)
{
	int u = root,p = 0;
	while(u) p = u,u = son(u,v > va(u));
	u = ++ idx;
	if(p) son(p,v > va(p)) = u;
	tr[u].init(p,v);
	splay(root,u,0);
}
int get_pre(int root,int v)
{
	int x = root,res = -INF;
	while(x) {
		if(v > va(x)) res = max(res,va(x)),x = son(x,1);
		else x = son(x,0);
	}
	return res;
}
int get_suc(int root,int v)
{
	int x = root,res = INF;
	while(x) {
		if(v < va(x)) res = min(res,va(x)),x = son(x,0);
		else x = son(x,1);
	}
	return res;
}
void build(int u,int l,int r)
{
	seg[u] = {l,r};
	insert(seg[u].root,-INF);
	insert(seg[u].root,INF);
	for(int i = l;i <= r;i++) insert(seg[u].root,w[i]);
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(u << 1,l,mid);
	build(u << 1 | 1,mid + 1,r);
}
int query(int u,int l,int r,int x)
{
	if(seg[u].l >= l && seg[u].r <= r) return get_k(seg[u].root,x) - 1;
	int mid = (seg[u].l + seg[u].r) >> 1,res = 0;
	if(l <= mid) res += query(u << 1,l,r,x);
	if(r > mid) res += query(u << 1 | 1,l,r,x);
	return res;
}
void update(int &root,int v,int x)
{
	int u = root;
	while(u) {
		if(va(u) == v) break;
		u = son(u,v > va(u));
	}
	splay(root,u,0);
	int L = son(u,0),R = son(u,1);
	while(son(L,1)) L = son(L,1);
	while(son(R,0)) R = son(R,0);
	splay(root,L,0),splay(root,R,L);
	son(R,0) = 0;
	push_up(R),push_up(L);
	insert(root,x);
}
void modify(int u,int pos,int x)
{
	update(seg[u].root,w[pos],x);
	if(seg[u].l == seg[u].r) return;
	int mid = (seg[u].l + seg[u].r) >> 1;
	if(pos <= mid) modify(u << 1,pos,x);
	else modify(u << 1 | 1,pos,x);
}
int query_pre(int u,int l,int r,int x)
{
	if(seg[u].l >= l && seg[u].r <= r) return get_pre(seg[u].root,x);
	int mid = (seg[u].l + seg[u].r) >> 1,res = -INF;
	if(l <= mid) res = max(res,query_pre(u << 1,l,r,x));
	if(r > mid)  res = max(res,query_pre(u << 1 | 1,l,r,x));
	return res;
}
int query_suc(int u,int l,int r,int x)
{
	if(seg[u].l >= l && seg[u].r <= r) return get_suc(seg[u].root,x);
	int mid = (seg[u].l + seg[u].r) >> 1,res = INF;
	if(l <= mid) res = min(res,query_suc(u << 1,l,r,x));
	if(r > mid)  res = min(res,query_suc(u << 1 | 1,l,r,x));
	return res;
}
/*
1 l r x，查询整数 x 在区间 [l,r] 内的排名。
2 l r k，查询区间 [l,r] 内排名为 k 的值。
3 pos x，将 pos 位置的数修改为 x。
4 l r x，查询整数 x 在区间 [l,r] 内的前驱(前驱定义为小于 x，且最大的数)。
5 l r x，查询整数 x 在区间 [l,r] 内的后继(后继定义为大于 x，且最小的数)。
*/
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&w[i]);
	build(1,1,n);
	while(m--) {
		int op,l,r,x,pos;
		scanf("%d",&op);
		if(op == 1) {
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query(1,l,r,x) + 1);
		}
		else if(op == 2) {
			scanf("%d%d%d",&l,&r,&x);
			int a = 0,b = 1e8;
			while(a <= b) {
				int mid = (a + b) >> 1;
				if(query(1,l,r,mid) >= x) b = mid - 1;
				else a = mid + 1;
			}
			printf("%d\n",a - 1);
		}
		else if(op == 3) {
			scanf("%d%d",&pos,&x);
			modify(1,pos,x);
			w[pos] = x;
		}
		else if(op == 4) {
			scanf("%d%d%d",&l,&r,&x);
			int ans = query_pre(1,l,r,x);
			if(ans < 0 || ans > 1e8) puts("-2147483647");
			else printf("%d\n",ans);
		}
		else {
			scanf("%d%d%d",&l,&r,&x);
			int ans = query_suc(1,l,r,x);
			if(ans < 0 || ans > 1e8) puts("2147483647");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
