#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct node{
	int l,r;
	ll sum,lazy;
}tr[N << 2];
int w[N];
void push_up(int u)
{
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void push_down(int u)
{
	tr[u << 1].sum += (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].lazy;
	tr[u << 1].lazy += tr[u].lazy;
	tr[u << 1 | 1].sum += (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].lazy;
	tr[u << 1 | 1].lazy += tr[u].lazy;
	tr[u].lazy = 0;
}
void build(int u,int l,int r)
{
	if(l == r) tr[u] = {l,r,w[l],0};
	else{
		tr[u] = {l,r};
		int mid = (l + r) >> 1;
		build(u << 1,l,mid);
		build(u << 1 | 1,mid + 1,r);
		push_up(u);
	}
}
void modify(int u,int l,int r,int v)
{
	if(tr[u].l >= l && tr[u].r <= r){
		tr[u].sum += (tr[u].r - tr[u].l + 1) * v;
		tr[u].lazy += v;
	}else{
		push_down(u);
		int mid = (tr[u].l + tr[u].r) >> 1;
		if(l <= mid) modify(u << 1,l,r,v);
		if(r > mid) modify(u << 1 | 1,l,r,v);
		push_up(u);
	}
}
ll query(int u,int l,int r)
{
	if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
	else{
		push_down(u);
		int mid = (tr[u].l + tr[u].r) >> 1;
		ll sum = 0;
		//与左边有交集
		if(l <= mid) sum = query(u << 1,l,r);
		//与右边有交集
		if(r > mid) sum += query(u << 1 | 1,l,r);  
		return sum;
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&w[i]);
	build(1,1,n);
	while(m --){
		char op[2];
		int l,r;
		scanf("%s%d%d",op,&l,&r);
		if(op[0] == 'Q') printf("%lld\n",query(1,l,r));
		else {
			int v;
			scanf("%d",&v);
			modify(1,l,r,v);
		}
	}
	return 0;
}
