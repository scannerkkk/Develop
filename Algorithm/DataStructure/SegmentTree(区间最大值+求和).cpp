#include "bits/stdc++.h"
using namespace std;
const int N = 500010;
struct node{
    int l,r;
    int sum,lmx,rmx,tmx;
}tr[N << 2];
int w[N];
void push_up(node &u,node &l,node &r)
{
    u.sum = l.sum + r.sum;
    u.lmx = max(l.lmx,l.sum + r.lmx);
    u.rmx = max(r.rmx,r.sum + l.rmx);
    //横跨的情况
    u.tmx = max(max(l.tmx,r.tmx),l.rmx + r.lmx);
}
void push_up(int u)
{
    push_up(tr[u],tr[u << 1],tr[u << 1 | 1]);
}
void build(int u,int l,int r)
{
    
    if(l == r) tr[u] = {l,r,w[l],w[l],w[l],w[l]};
    else{
        tr[u] = {l,r};
        build(u << 1,l,(l + r) >> 1);
        build(u << 1 | 1,(l + r) >> 1 + 1,r);
        push_up(u);
    }
}
void modify(int u,int x,int v)
{
    if(tr[u].l == tr[u].r) tr[u] = {x,x,v,v,v,v};
    else{
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1,x,v);
        else modify(u << 1 | 1,x,v);
        push_up(u);
    }
}
node query(int u,int l,int r)
{
    if(tr[u].l >= l && tr[u].r <= r) return tr[u];
    else{
        int mid = tr[u].l + tr[u].r >> 1;
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
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++) scanf("%d",&w[i]);    
    build(1,1,n);
    while(m --){
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        if(op == 2) modify(1,l,r);
        else{
            if(l > r) swap(l,r);
            printf("%d\n",query(1,l,r).tmx);
        }
    }
    return 0;
}
