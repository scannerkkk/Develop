#include "bits/stdc++.h"
using namespace std;
const int N = 1010,M = 1e5 + 10;
const int mod = 31011;
struct UFS {
    int f[N];
    void clr() {for(int i = 1;i <= N;i++) f[i] = i;}
    int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}
    bool merge(int x,int y){int fx = find(x),fy = find(y);if(fx == fy) return false;f[fx] = fy;return true;}
}ufs;
struct MST {
    int fr,to,wi;
    bool operator < (const MST &other) const {
        return wi < other.wi;
    }
}e[M];
int n,m,cnt,num;
long long mat[N][N],w[N];
int vis[N],id[N];
int ans = 1;
bool Kruscal()
{
    int siz = 0;
    sort(e + 1,e + 1 + m);
    ufs.clr();
    for(int i = 1;i <= m;i++) {
        if(ufs.merge(e[i].fr,e[i].to)) {
            siz ++;
            vis[i] = true; 
            if(w[cnt] != e[i].wi) w[++cnt] = e[i].wi;
        }
    }
    return siz == n - 1;
}
void link(int v)
{
    num = 0;
    ufs.clr();
    for(int i = 1;i <= m;i++) if(vis[i] && e[i].wi != v) ufs.merge(e[i].fr,e[i].to);
    for(int i = 1;i <= n;i++) if(ufs.find(i) == i) id[i] = ++ num;
    for(int i = 1;i <= n;i++) id[i] = id[ufs.find(i)];
    for(int i = 1;i <= m;i++) {
        if(e[i].wi != v) continue;
        int x = id[e[i].fr],y = id[e[i].to];
        if(x == y) continue;
        mat[x][x] ++,mat[y][y] ++;
        mat[x][y] --,mat[y][x] --;
    }
}
int gauss()
{
    int res = 1;
    for(int i = 2;i <= num;i++) {
        for(int j = i + 1;j <= num;j++) {
            while(mat[i][i]) {
                int v = mat[j][i] / mat[i][i];
                for(int k = i;k <= num;k++) mat[j][k] = (mat[j][k] - mat[i][k] * v % mod + mod) % mod;
                swap(mat[i],mat[j]);
                res = -res;
            }
            swap(mat[i],mat[j]);
            res = -res;
        }
        res = res * mat[i][i] % mod;
    }
    return (res + mod) % mod;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= m;i++) cin >> e[i].fr >> e[i].to >> e[i].wi;
    if(!Kruscal()) cout << 0 << endl;
    else {
        for(int i = 1;i <= cnt;i++) {
            memset(mat,0,sizeof(mat));
            link(w[i]);
            ans = 1LL * ans * gauss() % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
