#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ull = unsigned long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
std::mt19937 eng(time(0));
char *p1, *p2, buf[100000];
#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
inline int rd()
{
    char ch = getchar();
    int x = 0, w = 1;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * w;
}
inline void print(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
ll rand(ll l, ll r)
{
    ll x = rng() % (r - l + 1) + l;
    return x;
}
ll ksc(ll x, ll y, ll p)
{
    ll z = ((long double)x / p * y);
    ll t = (ull)x * y - (ull)z * p;
    return (t + p) % p;
}
ll ksm(ll a, ll k, ll p)
{
    ll res = 1;
    while (k)
    {
        if (k & 1)
            res = ksc(res, a, p);
        a = ksc(a, a, p);
        k >>= 1;
    }
    return res;
}
// Miller Rabin随机筛
inline bool MR(int x)
{
    if (x < 2)
        return false;

    if (x == 2)
        return true;

    if (!(x & 1))
        return false;

    ll d = x - 1;
    int s = 0;

    while (!(d & 1))
    {
        d >>= 1;
        s++;
    }

    for (int i = 1; i <= 8; i++)
    {
        ll y = ksm(eng() % (x - 2) + 2, d, x);

        if (y == 1)
            continue;

        for (int j = 1; j <= s; j++)
        {
            if (y == x - 1)
                break;

            y = y * y % x;
        }

        if (y != x - 1)
            return false;
    }

    return true;
}
inline bool prime(ll x)
{
    return MR(x);
}
//求p的非平凡因子
//生成函数f(x) = x * x + c
inline ll rho(ll p)
{
    ll x, y, z, c, g, i, j;
    while (1)
    {
        y = x = rand(0, 1000000) % p;
        z = 1, c = rand(0, 1000000) % p;
        i = 0, j = 1;
        while (++i)
        {
            x = (ksc(x, x, p) + c) % p;
            z = ksc(z, abs(y - x), p);
            if (x == y || !z)
                break;
            if (!(i % 127) || i == j)
            {
                g = __gcd(z, p);
                if (g > 1)
                    return g;
                if (i == j)
                    y = x, j <<= 1;
            }
        }
    }
}
set<int> fc;
bool ok = false;
inline void prho(int p)
{
    if (p == 1)
        return;
    if (prime(p))
    {
        fc.insert(p);
        return;
    }
    int fac = rho(p);
    while (p % fac == 0)
        p /= fac;
    prho(p), prho(fac);
}
const int N = 1e5 + 10;
ll a[N];
void solve()
{
    int n;
    n = rd();
    set<int> st;
    ok = false;
    for (int i = 1; i <= n; i++)
    {
        a[i] = rd();
        if (!ok)
        {
            fc.clear();
            prho(a[i]);
            for (auto x : fc)
            {
                if (st.count(x))
                {
                    ok = true;
                    break;
                }
                else
                {
                    st.insert(x);
                }
            }
        }
        else
        {
            break;
        }
    }
    if (ok)
        puts("YES");
    else
        puts("NO");
}
int main()
{
    srand(time(0));
    int T;
    T = rd();
    while (T--)
    {
        solve();
    }
    return 0;
}
