#include "bits/stdc++.h"
using namespace std;
using ll = long long;
ll a[11],b[11];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b) {
        x = 1,y = 0;
        return ;
    }
    exgcd(b,a % b,y,x);
    y -= a / b * x;
}
int main()
{
    int n;
    ll res = 1,ans = 0;
    cin >> n;
    for(int i = 1;i <= n;i++) {
        cin >> a[i] >> b[i];
        res *= a[i];
    }
    for(int i = 1;i <= n;i++) {
        ll Mi = res / a[i],ti,y;
        exgcd(Mi,a[i],ti,y);
        ans += ti * Mi * b[i];
    }
    cout << (ans % res + res) % res << endl;
    return 0;
}
