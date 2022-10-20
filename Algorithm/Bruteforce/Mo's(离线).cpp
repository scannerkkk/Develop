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
    if(x / 10) write(x / 10);
    putchar(x % 10 + '0');
}
const int N = 1e6 + 10;
int a[N],belong[N],ans[N],cnt[N];
int n,block,siz,m,tot;
struct node {
    int l;
    int r;
    int id;
}q[N];
int main()
{
    n = read();
    siz = pow(n,2.0 / 3.0);//可以尝试2.0 / 3.0 或者 3.0 / 4.0 或者 sqrt(n)
    for(int i = 1;i <= n;i++) belong[i] = (i - 1) / siz;
    for(int i = 1;i <= n;i++) a[i] = read();
    m = read();
    for(int i = 1;i <= m;i++) {
        q[i].id = i;
        q[i].l = read();
        q[i].r = read();
    }
    sort(q + 1,q + 1 + m,[](node &c,node &d){
        return (belong[c.l] ^ belong[d.l]) ? (belong[c.l] < belong[d.l]) : ((belong[c.l] & 1) ? c.r < d.r : c.r > d.r);
    });
    int l = 1,r = 0;
    for(int i = 1;i <= m;i++) {
        int ql = q[i].l,qr = q[i].r;
        while(l < ql) tot -= !--cnt[a[l++]];
        while(l > ql) tot += !cnt[a[--l]]++;
        while(r < qr) tot += !cnt[a[++r]]++;
        while(r > qr) tot -= !--cnt[a[r--]];
        ans[q[i].id] = tot;
    }
    for(int i = 1;i <= m;i++) write(ans[i]),putchar('\n');
    return 0;
}
