//更相减损术gcd(a,b,c) = gcd(a,b - a,c - b);
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 500010;
struct node{
    int l,r;
    ll s,d;
}tr[N << 2];
ll w[N];
ll gcd(ll a,ll b)
{
    return !b ? a : gcd(b,a % b);
}
void push_up(node &u,node &l,node &r)
{
    u.s = l.s + r.s;
    u.d = gcd(l.d,r.d);
}
void push_up(int u)
{
    push_up(tr[u],tr[u << 1],tr[u << 1 | 1]);
}
void build(int u,int l,int r)
{
    if(l == r) tr[u] = {l,l,w[l]-w[l-1],w[l]-w[l-1]};
    else{
        int mid = (l + r) >> 1;
        tr[u] = {l,r};
        build(u << 1,l,mid);
        build(u << 1 | 1,mid + 1,r);
        push_up(u);
    } 
}
node query(int u,int l,int r)
{
    if(l > r) return node{0,0,0,0};
    if(tr[u].l >= l && tr[u].r <= r) return tr[u];
    else{
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r <= mid) return query(u << 1,l,r);
        else if(l > mid) return query(u << 1 | 1,l,r);
        else{
            auto left = query(u << 1,l,r);
            auto right = query(u << 1 | 1,l,r);
            node res;
            push_up(res,left,right); 
            return res;
        }
    }
}
void modify(int u,int x,ll v)
{
    if(tr[u].l == x && tr[u].r == x){
        v = v + tr[u].d;
        tr[u] = {x,x,v,v};
    }
    else{
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(x > mid) modify(u << 1 | 1,x,v);
        else modify(u << 1,x,v);
        push_up(u);
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++) scanf("%lld",&w[i]);
    build(1,1,n);
    while(m --){
        char op[2];
        int l,r;
        scanf("%s%d%d",op,&l,&r);
        if(op[0] == 'Q') {
            auto left = query(1,1,l);
            auto right = query(1,l + 1,r);
            printf("%lld\n",abs(gcd(left.s,right.d)));
        }
        else{
            ll v;
            scanf("%lld",&v);
            modify(1,l,v);
            if(r + 1 <= n) modify(1,r + 1,-v);
        }
    }
    return 0;
}
