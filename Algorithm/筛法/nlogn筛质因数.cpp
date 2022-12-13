#include "bits/stdc++.h"
#define rep(i, z, n) for (int i = z; i <= n; i++)
#define per(i, n, z) for (int i = n; i >= z; i--)
#define ll long long
#define db double
#define PII pair<int, int>
#define fi first
#define se second
#define endl "\n"
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
using namespace std;
const int N = 1e7 + 10;
int not_prime[N], primes[N], small[N], cnt;
void init()
{
    int n = 1e7;
    for (int i = 2; i <= n; i++)
    {
        if (!not_prime[i])
        {
            primes[++cnt] = i;
            small[i] = i;
        }
        for (int j = 1; primes[j] <= n / i; j++)
        {
            not_prime[primes[j] * i] = true;
            if (!small[primes[j] * i])
                small[primes[j] * i] = primes[j];
            if (i % primes[j] == 0)
            {
                small[i] = primes[j];
                break;
            }
        }
    }
}
void solve()
{
    int l, r;
    cin >> l >> r;
    if (r - l == 1)
    {
        cout << "-1" << endl;
        return;
    }
    if (__gcd(l, r) != 1)
    {
        cout << 0 << endl;
        return;
    }
    int cnt = r - l;
    int ans = cnt;
    while (small[cnt] > 1)
    {
        ans = min(ans, small[cnt] - l % small[cnt]);
        cnt /= small[cnt];
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
