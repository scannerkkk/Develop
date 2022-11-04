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
const int N = 1e6 + 10;
vector <int> G[N << 1];
struct SAM {
    ll cnt[N << 1];
    int tot,np,p,fa[N << 1],len[N << 1],ch[N << 1][26];
    void init(int n) {
        tot = np = 1;
        for(int i = 1;i <= 2 * n;i++) {
            fa[i] = len[i] = 0;
            memset(ch[i],0,sizeof(ch[i]));
        }
    }
    void insert(int c) {
        p = np,np = ++ tot;//p回跳指针，np新店，q链接点，nq新链接点
        len[np] = len[p] + 1,cnt[np] = 1;
        for(;p && !ch[p][c];p = fa[p]) ch[p][c] = np;
        int q = ch[p][c];
        if(!p) fa[np] = 1;//出现新字符
        else if(len[p] + 1 == len[q]) fa[np] = q;//若连接点合法
        else {  //连接点不合法，那么就新造   
            int nq = ++ tot;
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            len[nq] = len[p] + 1; fa[nq] = fa[q]; fa[q] = fa[np] = nq;
            for(;p && (ch[p][c] == q);p = fa[p]) ch[p][c] = nq;
        }
    }
}sam;
ll ans = 0;
void dfs(int now)
{
    for(auto x:G[now]) {
        dfs(x);
        sam.cnt[now] += sam.cnt[x];
    }
    if(sam.cnt[now] > 1) ans = max(ans,sam.cnt[now] * sam.len[now]);
}
void solve()
{
    string s;
    cin >> s;
    sam.init(s.size());
    for(int i = 0;i < s.size();i++) sam.insert(s[i] - 'a');
    for(int i = 2;i <= sam.tot;i++) G[sam.fa[i]].push_back(i);
    dfs(1);
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T = 1;
    while(T --) solve();
    return 0;
}
