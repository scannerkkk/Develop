#include "bits/stdc++.h"
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define PII pair<int,int>
#define fi first
#define se second
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
using namespace std;
const int N = 5e5 + 10,P = 13331,mod = 1e9 + 7,limit = 65536;
struct SegTree{
    int l,r,len;
    ll mx,lz,hash,base;
}seg[N << 2];
ll f[N];
void push_up(int u)
{
    seg[u].mx = max(seg[u << 1].mx,seg[u << 1 | 1].mx);
    seg[u].hash = seg[u << 1].hash + seg[u << 1 | 1].hash;
}
void push_down(int u)
{
    if(seg[u].lz) {
        seg[u << 1].lz += seg[u].lz;
        seg[u << 1].mx += seg[u].lz;
        seg[u << 1].hash = (seg[u << 1].hash + seg[u << 1].base * seg[u].lz) % mod;
        seg[u << 1 | 1].lz += seg[u].lz;
        seg[u << 1 | 1].mx += seg[u].lz;
        seg[u << 1 | 1].hash = (seg[u << 1 | 1].hash + seg[u << 1 | 1].base * seg[u].lz) % mod;
        seg[u].lz = 0;
    }
}
void build(int u,int l,int r)
{
    if(l == r) {
        seg[u] = {l,r,1,0,0,0,f[l]};
        scanf("%lld",&seg[u].mx);
        seg[u].hash = seg[u].mx * seg[u].base % mod;
    }
    else {
        seg[u] = {l,r,r - l + 1,0,0,0};
        int mid = l + r >> 1;
        build(u << 1,l,mid);
        build(u << 1 | 1,mid + 1,r);
        seg[u].base = (seg[u << 1].base + seg[u << 1 | 1].base) % mod;
        push_up(u);
    }
}
void update_seg(int u,int l,int r)
{
    if(seg[u].l >= l && seg[u].r <= r) {
        seg[u].mx ++;
        seg[u].lz ++;
        seg[u].hash = (seg[u].hash + seg[u].base) % mod;
        return ;
    }
    else {
        push_down(u);
        int mid = (seg[u].l + seg[u].r) >> 1;
        if(l <= mid) update_seg(u << 1,l,r);
        if(r >  mid) update_seg(u << 1 | 1,l,r);
        push_up(u);
    }
}
void update_mod(int u)
{
    if(seg[u].mx < limit) return ;
    if(seg[u].l == seg[u].r) seg[u].mx = 0,seg[u].hash = 0;
    else {
        push_down(u);
        update_mod(u << 1);
        update_mod(u << 1 | 1);
        push_up(u);
    }
}
ll query_hash(int u,int l,int r)
{
    if(seg[u].l >= l && seg[u].r <= r) return seg[u].hash;
    push_down(u);
    ll res = 0;
    int mid = seg[u].l + seg[u].r >> 1;
    if(l <= mid) res = (res + query_hash(u << 1,l,r)) % mod;
    if(r > mid) res = (res + query_hash(u << 1 | 1,l,r)) % mod; 
    return res;
}
bool check(int l,int r,int len)
{
    if(l > r) swap(l,r);
    ll hash1 = query_hash(1,l,l + len - 1) * f[r - l] % mod;
    ll hash2 = query_hash(1,r,r + len - 1);
    return hash1 == hash2;
}
void solve()
{
    int n,m,op,l,r,len;
    scanf("%d%d",&n,&m);
    build(1,1,n);
    while(m --) {
        scanf("%d",&op);
        if(op == 1) {
            scanf("%d%d",&l,&r);
            update_seg(1,l,r);
            update_mod(1);
        }
        else {
            scanf("%d%d%d",&l,&r,&len);
            printf("%s",check(l,r,len) ? "yes\n" : "no\n");
        }
    }
}
int main()
{
    f[0] = 1;
    for(int i = 1;i < N;i++) f[i] = f[i - 1] * P % mod;
    int T = 1;
    while(T --) solve();
    return 0;
}
