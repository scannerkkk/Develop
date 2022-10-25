#include "bits/stdc++.h"
using namespace std;
const int N = 5e6 + 10;
int d[N],p[N],f[N];
int n,m;
//应用
//1.无向完全图的不同生成树/n个点的无根树计数 = n^(n - 2)
//2.n个点的有根树计数 = n^(n - 1)
//3.n个点，每点度数为di的无根树计数 = (n - 2)! / ((d1 - 1)! * (d2 - 1)! * (d3 - 1)! * ..... * (dn - 1)!);
//tree to prufer
void ttp()
{
    for(int i = 1;i < n;i ++) {
        scanf("%d",&f[i]);
        d[f[i]] ++;
    }
    for(int i = 1,j = 1;i <= n - 2;j ++,i ++) {
        while(d[j]) j ++;
        p[i] = f[j];
        while(i <= n - 2 && --d[p[i]] == 0 && p[i] < j) p[i + 1] = f[p[i]],i ++;
    }
    long long ans = 0;
    for(int i = 1;i <= n - 2;i++) ans ^= 1LL * i * p[i];
    printf("%lld\n",ans);
}
//prufer to tree
void ptt()
{
    for(int i = 1;i <= n - 2;i++) {
        scanf("%d",&p[i]);
        d[p[i]] ++;
    }
    p[n - 1] = n;
    for(int i = 1,j = 1;i <= n - 1;i ++,j ++) {
        while(d[j]) j ++;
        f[j] = p[i];
        while(i <= n - 1 && --d[p[i]] == 0 && p[i] < j) f[p[i]] = p[i + 1],i ++;
    }
    long long ans = 0;
    for(int i = 1;i < n;i++) ans ^= 1LL * i * f[i];
    printf("%lld\n",ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    if(m == 1) ttp();
    else ptt();
    return 0;
}
