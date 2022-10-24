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
const int N = 1e5 + 10,M = 1e6 + 10;
struct Edge {int nt,to;} e[M];
int cor[M],h[M],sz[M],pm[M];
int tot = 0,idx = 0;
void add(int a,int b) 
{
    e[++ idx] = {h[a],b};
    h[a] = idx,sz[a] ++;
}
//合并的时候小链向大链合并，时间复杂度为Onlogn
void merge(int &x,int &y)
{
    if(x == y) return ;
    if(sz[x] > sz[y]) swap(x,y);
    for(int i = h[x];~i;i = e[i].nt) {
        int j = e[i].to;
        tot -= (cor[j - 1] == y) + (cor[j + 1] == y);
    }
    for(int i = h[x];~i;i = e[i].nt) {
        int j = e[i].to;
        cor[j] = y;
        if(e[i].nt == -1) {
            e[i].nt = h[y];
            h[y] = h[x];
            h[x] = -1;
            break;
        }
    }
    sz[y] += sz[x],sz[x] = 0;
}
void solve()
{
    int n,m;
    memset(h,-1,sizeof(h));
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        cin >> cor[i];
        add(cor[i],i);
        if(cor[i] != cor[i - 1]) tot ++;
    }
    //新开一个数组记录颜色，该变颜色的时候，这个指针也要互换
    for(int i = 0;i < M;i++) pm[i] = i;
    while(m --) {
        int op,x,y;
        cin >> op;
        if(op == 1) {
            cin >> x >> y;
            merge(pm[x],pm[y]);
        }
        else cout << tot << endl;
    }
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
