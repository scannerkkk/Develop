#include "bits/stdc++.h"
using namespace std;
const int M = 2e4 + 10,N = 300;
struct UFS {
    int f[N];
    void clr() {for(int i = 1;i < N;i++) f[i] = i;}
    int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}
    bool merge(int x,int y) {
        int fx = find(x),fy = find(y);
        if(fx == fy) return false;
        f[fx] = fy;
        return true;
    }
}ufs;
struct Edge {
    int fr,to,wi;
    bool operator < (const Edge &other) const{
        return wi < other.wi;
    }
}e[M];
int vis[N],cnt;
int n,m,ans = 0;
int Kruscal(int idx)
{
    int res = 0,rem = 0;
    ufs.clr();
    for(int i = 1;i <= m;i++) {
        if(i == idx) continue;
        if(ufs.merge(e[i].fr,e[i].to)) {
            res += e[i].wi;
            rem ++;
        }
    }
    if(rem != n - 1) return ans + 1;
    else return res;
}
void solve()
{
    int res = 0;
    cnt = ans = 0;
    cin >> n >> m;
    ufs.clr();
    for(int i = 1;i <= m;i++) cin >> e[i].fr >> e[i].to >> e[i].wi;
    sort(e + 1,e + 1 + m);
    for(int i = 1;i <= m;i++) {
        if(ufs.merge(e[i].fr,e[i].to)) {
            ans += e[i].wi;
            vis[++cnt] = i;
        }
    }
    if(cnt != n - 1) {
        cout << "Not Unique!" << endl;
        return ;
    }
    for(int i = 1;i <= cnt;i++) {
        if(Kruscal(vis[i]) == ans) {
            cout << "Not Unique!" << endl;
            return ;
        }
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin >> T;
    while(T --) {
        solve();
    }
    return 0;
}
