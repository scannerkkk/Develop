#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
//lazy表示和的懒标记,mul表示乘的懒标记
struct node{
	int l,r;
	ll sum,mul,lazy;
}tr[N << 2];
int w[N],p;
void push_up(int u)
{
	tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}
void calc(int u,int m,int k)
{
	tr[u].sum = ((tr[u].sum * m) + ((ll)(tr[u].r - tr[u].l + 1) * k)) % p;
	tr[u].mul = tr[u].mul * m % p;
	tr[u].lazy = (tr[u].lazy * m + k) % p;
}
void push_down(int u)
{
 	calc(u << 1,tr[u].mul,tr[u].lazy);
 	calc(u << 1 | 1,tr[u].mul,tr[u].lazy);
 	tr[u].lazy = 0;
 	tr[u].mul = 1;
}
void build(int u,int l,int r)
{
	if(l == r) tr[u] = {l,r,w[l],1,0};
	else {
		tr[u] = {l,r,0,1,0};
		int mid = (l + r) >> 1;
		build(u << 1,l,mid);
		build(u << 1 | 1,mid + 1,r);
		push_up(u);
	}
}
void modify(int u,int l,int r,int m,int k)
{
	//m表示乘，k表示加
	if(tr[u].l >= l && tr[u].r <= r) calc(u,m,k);
	else {
		push_down(u);
		int mid = (tr[u].l + tr[u].r) >> 1;
		if(l <= mid) modify(u << 1,l,r,m,k);
		if(r > mid) modify(u << 1 | 1,l,r,m,k);
		push_up(u);
	}
}
int query(int u,int l,int r)
{
	if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
	else {
		push_down(u);
		int mid = (tr[u].l + tr[u].r) >> 1;
		int sum = 0;
		if(l <= mid) sum = query(u << 1,l,r) % p;
		if(r > mid) sum = (sum + query(u << 1 | 1,l,r)) % p;
		return sum;
	}
}
int main()
{
	int n;
	scanf("%d%d",&n,&p);
	for(int i = 1;i <= n;i++) scanf("%d",&w[i]);
	build(1,1,n);
	int m;
	scanf("%d",&m); 
	while(m --){
		int op,l,r,v;
		scanf("%d",&op);
		if(op == 1){
			//乘
			scanf("%d%d%d",&l,&r,&v);
			modify(1,l,r,v,0);
		}else if(op == 2){
			scanf("%d%d%d",&l,&r,&v);
			modify(1,l,r,1,v);
		}
		else {
			scanf("%d%d",&l,&r);
			printf("%d\n",query(1,l,r));
		}
	}
	return 0;
}
