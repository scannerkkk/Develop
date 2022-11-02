#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 50050;
int mobius[N],primes[N],cnt;
ll s[N];
bool st[N];
//莫比乌斯函数定义：
/*
记M(x) = 
        1. 1(n == 1)
        2. -1^k 
        3. 0(若某个质因子指数大于1)
*/
//线性筛预处理莫比乌斯函数
void init(int n)
{
    mobius[1] = 1;
    for(int i = 2;i <= n;i++) {
        if(!st[i]) {
            primes[++cnt] = i;
            mobius[i] = -1;
        }
        for(int j = 1;primes[j] <= n / i;j++) {
            st[i * primes[j]] = true;
            if(i % primes[j] == 0) {
                mobius[i * primes[j]] = 0;
                break;
            }
            mobius[i * primes[j]] = mobius[i] * -1;
        }
    }
    for(int i = 1;i <= n;i++) s[i] = s[i - 1] + mobius[i];
}
int main()
{
    int T;
    ll ans = 0;
    init(50001);
    cin >> T;
    while(T --) {
        int a,b,d;
        cin >> a >> b >> d;
        a /= d,b /= d;
        int n = min(a,b);
        ans = 0;
        for(int l = 1,r;l <= n;l = r + 1) {
            r = min(n,min(a / (a / l),b / (b / l)));
            ans += (s[r] - s[l - 1]) * (a / l) * (b / l);
        }
        cout << ans << endl;
    }
    return 0;
}
