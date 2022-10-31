#include "bits/stdc++.h"
#define rep(i, z, n) for (int i = z; i <= n; i++)
#define per(i, n, z) for (int i = n; i >= z; i--)
#define ll long long
#define db double
#define PII pair<int, int>
#define fi first
#define se second
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
using namespace std;
const int N = 1e5 + 10;
const int MOD = 998244353;
struct mint
{
    ll x; // typedef long long ll;
    mint(ll x = 0) : x((x % MOD + MOD) % MOD) {}
    mint operator-() const { return mint(-x); }
    mint &operator+=(const mint a)
    {
        if ((x += a.x) >= MOD)
            x -= MOD;
        return *this;
    }
    mint &operator-=(const mint a)
    {
        if ((x += MOD - a.x) >= MOD)
            x -= MOD;
        return *this;
    }
    mint &operator*=(const mint a)
    {
        (x *= a.x) %= MOD;
        return *this;
    }
    mint operator+(const mint a) const
    {
        mint res(*this);
        return res += a;
    }
    mint operator-(const mint a) const
    {
        mint res(*this);
        return res -= a;
    }
    mint operator*(const mint a) const
    {
        mint res(*this);
        return res *= a;
    }
    bool operator==(const mint a) const
    {
        return this->x == a.x;
    }
    bool operator!=(const mint a) const
    {
        return this->x != a.x;
    }
    mint pow(ll t) const
    {
        if (!t)
            return 1;
        mint a = pow(t >> 1);
        a *= a;
        if (t & 1)
            a *= *this;
        return a;
    }
    mint inv() const
    {
        return pow(MOD - 2);
    }
    mint &operator/=(const mint a)
    {
        return (*this) *= a.inv();
    }
    mint operator/(const mint a) const
    {
        mint res(*this);
        return res /= a;
    }
};
istream &operator>>(istream &is, const mint &a)
{
    return is >> a.x;
}
ostream &operator<<(ostream &os, const mint &a)
{
    return os << a.x;
}
void solve()
{
    ll a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
    mint t1 = a;
    t1 *= b;
    t1 *= c;

    mint t2 = d;
    t2 *= e;
    t2 *= f;
    cout << (t1 - t2) << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
