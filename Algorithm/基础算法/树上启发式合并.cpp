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
const int N = 1e5 + 10;
int v[N],son[N],sz[N],cnt[N];
ll ans[N],tmp,mx;
vector <int> G[N];
int n,u1,u2;
void update(int now,int fa,int sign,int fat)
{
    int t = v[now];
    cnt[t] += sign;
    if(cnt[t] > mx) mx = cnt[t],tmp = t;
    else if(cnt[t] == mx) tmp += t;
    for(auto x:G[now]) {
        if(x == fa || x == fat) continue;
        update(x,now,sign,fat);
    }
}
void dfs_son(int now,int fa)
{
    sz[now] = 1;
    for(auto x:G[now]) {
        if(x == fa) continue;
        dfs_son(x,now);
        sz[now] += sz[x];
        if(sz[x] > sz[son[now]]) son[now] = x;
    }
}
void dfs_ans(int now,int fa,bool fat)
{
    for(auto x:G[now]) {
        if(x == fa || x == son[now]) continue;
        dfs_ans(x,now,0);
    }
    if(son[now]) dfs_ans(son[now],now,1);
    update(now,fa,1,son[now]);
    ans[now] = tmp;
    if(!fat) update(now,fa,-1,0),tmp = mx = 0;
}
void solve()
{
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> v[i];
    for(int i = 1;i < n;i++) {
        cin >> u1 >> u2;
        G[u1].push_back(u2);
        G[u2].push_back(u1);
    }
    dfs_son(1,0);
    dfs_ans(1,0,1);
    for(int i = 1;i <= n;i++) cout << ans[i] << " \n"[i == n];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T --) solve();
    return 0;
}
