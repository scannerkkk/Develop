#include "bits/stdc++.h"
#define son(x,k) tr[x].s[k]
#define sz(x) tr[x].siz
#define fa(x) tr[x].p
#define sam(x) tr[x].sam
#define va(x) tr[x].v
#define ls(x) tr[x].lsum
#define rs(x) tr[x].rsum
#define ms(x) tr[x].msum
#define ts(x) tr[x].sum
#define rv(x) tr[x].rev
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
const int INF = 2e9;
struct Node {
    int p,v,siz;
    int s[2];
    int sam,rev;
    ll lsum,rsum,msum,sum;
    void init(int _p,int _v) {
        p = _p,v = _v,siz = 1;
        s[0] = s[1] = 0;
        sam = rev = 0;
        msum = sum = v;
        lsum = rsum = max(0,v);
    }
}tr[N];
int root,tot,dispose[N],w[N];
char op[20];
void push_up(int u)
{
    sz(u) = sz(son(u,0)) + sz(son(u,1)) + 1;
    ts(u) = ts(son(u,0)) + ts(son(u,1)) + va(u);
    ls(u) = max(ls(u),ts(son(u,0)) + va(u) + ls(son(u,1)));
    rs(u) = max(rs(u),ts(son(u,1)) + va(u) + rs(son(u,0)));
    ms(u) = max(max(ms(son(u,0)),ms(son(u,1))),rs(son(u,0)) + va(u) + ls(son(u,1)));
}
void push_dw(int u)
{
    if(sam(u)) {
        sam(u) = rv(u) = 0;
        if(son(u,0)) sam(son(u,0)) = 1,va(son(u,0)) = va(u),ts(son(u,0)) = 1LL * sz(son(u,0)) * va(u);
        if(son(u,1)) sam(son(u,1)) = 1,va(son(u,1)) = va(u),ts(son(u,1)) = 1LL * sz(son(u,1)) * va(u);
        if(va(u) > 0) {
            if(son(u,0)) ms(son(u,0)) = ls(son(u,0)) = rs(son(u,0)) = ts(son(u,0));
            if(son(u,1)) ms(son(u,1)) = ls(son(u,1)) = rs(son(u,1)) = ts(son(u,1));
        }
        else {
            if(son(u,0)) ms(son(u,0)) = va(son(u,0)),ls(son(u,0)) = rs(son(u,0)) = 0;
            if(son(u,1)) ms(son(u,1)) = va(son(u,1)),ls(son(u,1)) = rs(son(u,1)) = 0;
        }
    }
    else if(rv(u)) {
        rv(u) = 0,rv(son(u,0)) ^= 1,rv(son(u,1)) ^= 1;
        swap(ls(son(u,0)),rs(son(u,0)));
        swap(ls(son(u,1)),rs(son(u,1)));
        swap(son(son(u,0),0),son(son(u,0),1));
        swap(son(son(u,1),0),son(son(u,1),1));
    }
}
int build(int u,int l,int r)
{
    int mid = (l + r) >> 1,t = dispose[tot --];
    tr[t].init(u,w[mid]);
    if(l < mid) son(t,0) = build(t,l,mid - 1);
    if(r > mid) son(t,1) = build(t,mid + 1,r);
    push_up(t);
    return t;
}
void rotate(int x)
{
    int y = fa(x),z = fa(y),k = son(y,1) == x;
    son(z,son(z,1) == y) = x,fa(x) = z;
    son(y,k) = son(x,k ^ 1),fa(son(x,k ^ 1)) = y;
    son(x,k ^ 1) = y,fa(y) = x;
    push_up(y),push_up(x);
}
void splay(int x,int k)
{
    while(fa(x) != k) {
        int y = fa(x),z = fa(y);
        if(z != k) {
            (son(y,0) == x) ^ (son(z,0) == y) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
    if(!k) root = x;
}
int get_k(int k)
{
    int x = root;
    while(true) {
        push_dw(x);
        if(sz(son(x,0)) >= k) x = son(x,0);
        else if(sz(son(x,0)) + 1 == k) return x;
        else k -= sz(son(x,0)) + 1,x = son(x,1);
    }
    return -1;
}
void dfs(int u)
{
    if(son(u,0)) dfs(son(u,0));
    if(son(u,1)) dfs(son(u,1));
    dispose[++ tot] = u;
}
int main()
{
    int n,m;
    for(int i = 1;i < N;i++) dispose[++ tot] = i;
    scanf("%d%d",&n,&m);
    tr[0].msum = w[0] = w[n + 1] = -INF;
    for(int i = 1;i <= n;i++) scanf("%d",&w[i]);
    root = build(0,0,n + 1);
    while(m--) {
        scanf("%s",op);
        if(op[0] == 'I') {
            int pos,cnt;
            scanf("%d%d",&pos,&cnt);
            for(int i = 0;i < cnt;i++) scanf("%d",&w[i]);
            int L = get_k(pos + 1),R = get_k(pos + 2);
            splay(L,0),splay(R,L);
            int V = build(R,0,cnt - 1);
            son(R,0) = V;
            push_up(R),push_up(L);
        }
        else if(op[0] == 'D') {
            int pos,cnt;
            scanf("%d%d",&pos,&cnt);
            int L = get_k(pos),R = get_k(pos + cnt + 1);
            splay(L,0),splay(R,L);
            dfs(son(R,0));
            son(R,0) = 0;
            push_up(R),push_up(L);
        }
        else if(op[0] == 'R') {
            int pos,cnt;
            scanf("%d%d",&pos,&cnt);
            int L = get_k(pos),R = get_k(pos + cnt + 1);
            splay(L,0),splay(R,L);
            rv(son(R,0)) ^= 1;
            swap(ls(son(R,0)),rs(son(R,0)));
            swap(son(son(R,0),0),son(son(R,0),1));
            push_up(R),push_up(L);
        }
        else if(op[0] == 'G') {
            int pos,cnt;
            scanf("%d%d",&pos,&cnt);
            int L = get_k(pos),R = get_k(pos + cnt + 1);
            splay(L,0),splay(R,L);
            printf("%lld\n",ts(son(R,0)));
        }
        else {
            if(op[1] == 'A') printf("%lld\n",ms(root));
            else {
                int pos,cnt,c;
                scanf("%d%d%d",&pos,&cnt,&c);
                int L = get_k(pos),R = get_k(pos + cnt + 1);
                splay(L,0),splay(R,L);
                sam(son(R,0)) = 1,va(son(R,0)) = c,ts(son(R,0)) = sz(son(R,0)) * 1LL * c;
                if(c > 0) ms(son(R,0)) = ls(son(R,0)) = rs(son(R,0)) = ts(son(R,0));
                else ms(son(R,0)) = c,ls(son(R,0)) = rs(son(R,0)) = 0;
                push_up(R),push_up(L);
            }
        }
    }
    return 0;
}
