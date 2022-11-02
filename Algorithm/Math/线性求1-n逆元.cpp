#include "bits/stdc++.h"
using namespace std;
const int N = 3e6 + 10;
using ll = long long;
int n,p,inv[N];
void solve()
{
    scanf("%d%d",&n,&p);
    inv[1] = 1;
    for(int i = 1;i <= n;i++) {
        printf("%d\n",inv[i]);
        //线性求1-n逆元
        inv[i + 1] = (1LL * (p - p / (i + 1))) * inv[p % (i + 1)] % p;
    }
}
int main()
{
    int T;
    T = 1;
    while(T --) {
        solve();
    }
    return 0;
}
