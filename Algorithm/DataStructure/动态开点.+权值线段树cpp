#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 1e7 + 10;
struct node {
    int lc,rc;
    int cnt;
}seg[N];
int idx,root;
void push_up(int u)
{
    int lc = seg[u].lc,rc = seg[u].rc;
    seg[u].cnt = seg[lc].cnt + seg[rc].cnt;
}
void insert(int &cur,int l,int r,int p)
{
    if(!cur) cur = ++ idx;
    if(l == r) {
        seg[cur].cnt ++;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(seg[cur].lc,l,mid,p);
    else insert(seg[cur].rc,mid + 1,r,p);
    push_up(cur);
}
ll query(int cur,int l,int r,int L,int R)
{
    if(!cur) return 0;
    if(l >= L && r <= R) return seg[cur].cnt;
    ll res = 0,mid = (l + r) >> 1;
    if(L <= mid) res += query(seg[cur].lc,l,mid,L,R);
    if(R > mid)  res += query(seg[cur].rc,mid + 1,r,L,R);
    return res;
}
int main()
{
    int n;
    scanf("%d",&n);
    ll ans = 0;
    for(int i = 1;i <= n;i++) {
        int x;
        scanf("%d",&x);
        insert(root,1,1e9 + 1,x);
        ans += query(1,1,1e9 + 1,x + 1,1e9 + 1);
    }
    cout << ans << endl;
    return 0;
}
