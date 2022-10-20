#include "bits/stdc++.h"
using namespace std;
const int N = 200010;
struct node{
    int l,r;
    int mx;
}tre[N << 2];
void push_up(int u)
{
    tre[u].mx = max(tre[u << 1].mx,tre[u << 1 | 1].mx);
}
void build(int u,int l,int r)
{
    tre[u] = {l,r};
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(u << 1,l,mid);
    build(u << 1 | 1,mid + 1,r);
}
int query(int u,int l,int r)
{
    //如果这棵子树的区间完全被包含了，直接返回即可
    if(tre[u].l >= l && tre[u].r <= r) return tre[u].mx;
    int mid = (tre[u].l + tre[u].r) >> 1,v = 0;
    if(l <= mid) v = query(u << 1,l,r);
    if(r > mid) v = max(v,query(u << 1 | 1,l,r));
    return v;
}
void modify(int u,int x,int v)
{
    if(tre[u].l == x && tre[u].r == x) tre[u].mx = v;
    else{
        int mid = (tre[u].l + tre[u].r) >> 1;
        if(x <= mid) modify(u << 1,x,v);
        else modify(u << 1 | 1,x,v);
        push_up(u);
    }
}
int main()
{
    int n = 0,last = 0,p,m;
    scanf("%d%d",&m,&p);
    build(1,1,m);
    while(m--){
        char op[2];
        int x;
        scanf("%s%d",op,&x);
        if(op[0] == 'Q') {
            last = query(1,n - x + 1,n);
            printf("%d\n",last);
        }
        else modify(1,++n,(1LL* x + last) % p);
    }
    return 0;
}
