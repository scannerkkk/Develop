#include "bits/stdc++.h"
#define fi first
#define se second
#define ull unsigned long long
#define PUU pair<unsigned long long, unsigned long long>
using namespace std;
const int N = 1e5 + 10;
const int mod1 = 1e9 + 7, mod2 = 998244353;
const int base1 = 131, base2 = 13331;
ull p1[N], p2[N];
ull v1[N], v2[N];
map<PUU, int> mp;
void init(int n)
{
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        p1[i] = p1[i - 1] * base1 % mod1;
        p2[i] = p2[i - 1] * base2 % mod2;
    }
}
PUU getHash(int l, int r)
{
    PUU v;
    v.fi = v1[r] - v1[l - 1] * p1[r - l + 1] % mod1;
    v.se = v2[r] - v2[l - 1] * p2[r - l + 1] % mod2;
    return v;
}
void doubleHash(string s)
{
    for (int i = 1; i <= s.size(); i++)
    {
        v1[i] = (v1[i - 1] * base1 + s[i - 1]) % mod1;
        v2[i] = (v2[i - 1] * base2 + s[i - 1]) % mod2;
    }
    return;
}
void solve()
{
    init(10000);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        doubleHash(s);
        mp[getHash(1, s.size())]++;
    }
    cout << mp.size() << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
