#include "bits/stdc++.h"
#define PII pair<int,int>
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define vi vector<int>
#define debug(x) cerr << "!!!" << x << endl;
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buf[100000];
inline ll read()
{
    ll x = 0,f = 1;
    char ch = nc();
    while(ch < '0'||ch > '9')
    {
        if(ch == '-') f = -1;
        ch = nc();
    }
    while(ch >= '0'&&ch<='9') x = x * 10 + ch - '0',ch = nc();
    return x * f;
}
inline void write(ll x)
{
    if(x > 9) write(x / 10);
    if(x < 0) putchar('-'),x = -x;
    putchar(x % 10 + '0');
}
const int N = 205000,M = 1e6 + 10;
struct query {
    int l,r;
    int t,id;
}qu[N];
struct modify {
    int pos;
    int color;
}mo[N];
int a[N],belong[N],ans[N],cnt[M];
int block,siz,n,m,cntm,cntq;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    siz = pow(n,3.0 / 4.0);
    for(int i = 1;i <= n;i++) belong[i] = (i - 1) / siz;
    rep(i,1,n) cin >> a[i];
    rep(i,1,m) {
        char op[10];
        cin >> op;
        if(op[0] == 'Q') {
            ++ cntq;
            cin >> qu[cntq].l >> qu[cntq].r;
            qu[cntq].t = cntm;
            qu[cntq].id = cntq; 
        }
        else if(op[0] == 'R'){
            ++ cntm;
            cin >> mo[cntm].pos >> mo[cntm].color;
        }
    }
    sort(qu + 1,qu + 1 + cntq,[](query &a,query &b){
        return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : ((belong[a.r] ^ belong[b.r]) ? belong[a.r] < belong[b.r] : a.t < b.t);
    });
    int l = 1,r = 0,t = 0,tot = 0;
    rep(i,1,cntq) {
        int ql = qu[i].l,qr = qu[i].r,qt = qu[i].t;
        while(l < ql) tot -= !--cnt[a[l++]];
        while(l > ql) tot += !cnt[a[--l]]++;
        while(r < qr) tot += !cnt[a[++r]]++;
        while(r > qr) tot -= !--cnt[a[r--]];
        while(t < qt) {
            ++ t;
            if(mo[t].pos >= ql && mo[t].pos <= qr) tot -= !--cnt[a[mo[t].pos]] - !cnt[mo[t].color]++;
            swap(a[mo[t].pos],mo[t].color);
        }
        while(t > qt) {
            if(mo[t].pos >= ql && mo[t].pos <= qr) tot -= !--cnt[a[mo[t].pos]] - !cnt[mo[t].color]++;
            swap(a[mo[t].pos],mo[t].color);
            -- t;
        }
        ans[qu[i].id] = tot;
    }
    rep(i,1,cntq) write(ans[i]),putchar('\n');
    return 0;
}
