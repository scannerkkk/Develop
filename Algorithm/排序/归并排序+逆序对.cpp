#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>
#include <cstdio>
#include <climits>
#define PII pair<int,int>
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define vi vector<int>
#define debug(x) cerr << "!!!" << x << endl;
using namespace std;
inline ll read()
{
    ll s,r;
    r = 1;
    s = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            r = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return s * r;
}
inline void write(ll x)
{
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int n;
const int N=500010;
int Q[N],T[N];
ll merge(int l,int r)
{
    if(l>=r) return 0;
    int mid=(l+r)>>1;
    ll res=merge(l,mid)+merge(mid+1,r);
    int k=0,i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(Q[i]<=Q[j]) T[k++]=Q[i++];
        else T[k++]=Q[j++],res+=mid-i+1;
    }
    while(i<=mid) T[k++]=Q[i++];
    while(j<=r) T[k++]=Q[j++];
    for(i=l,j=0;i<=r;i++,j++) Q[i]=T[j];
    return res;
}
int main()
{
    n=read();
    rep(i,0,n-1) Q[i]=read();
    printf("%lld",merge(0,n-1));
    return 0;
}
