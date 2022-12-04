#include "bits/stdc++.h"
#define ull unsigned long long
using namespace std;
const int N = 60, MAXN = 55;
int n;
vector<int> G[N];
vector<ull> hs[N];
int primes[N], is_prime[1010], siz[N];
ull g[N], f[N];
void init()
{
    for (int i = 1; i <= MAXN; i++)
    {
        G[i].clear();
    }
}
void getPrimes()
{
    int cnt = 0;
    for (int i = 2; i <= 1000; i++)
    {
        if (!is_prime[i])
        {
            primes[cnt++] = i;
        }
        if (cnt > MAXN)
            break;
        for (int j = 0; primes[j] <= 1000 / i; j++)
        {
            is_prime[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}
void dfs1(int now, int fa)
{
    siz[now] = f[now] = 1;
    for (auto x : G[now])
    {
        if (x == fa)
            continue;
        dfs1(x, now);
        siz[now] += siz[x];
        f[now] += f[x] * primes[siz[x]];
    }
}
void dfs2(int now, int fa, ull fv)
{
    g[now] = f[now] + fv * primes[n - siz[now]];
    fv *= primes[n - siz[now]];
    for (auto x : G[now])
    {
        if (x == fa)
            continue;
        dfs2(x, now, fv + f[now] - f[x] * primes[siz[x]]);
    }
}
bool checkHash(int i, int j)
{
    if (hs[i].size() != hs[j].size())
        return false;
    for (int k = 0; k < hs[i].size(); k++)
    {
        if (hs[i][k] != hs[j][k])
        {
            return false;
        }
    }
    return true;
}
void solve()
{
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        init();
        cin >> n;
        int x;
        for (int j = 1; j <= n; j++)
        {
            cin >> x;
            if (x != 0)
            {
                G[j].push_back(x);
                G[x].push_back(j);
            }
        }
        dfs1(1, 0);
        dfs2(1, 0, 0);
        for (int j = 1; j <= n; j++)
        {
            hs[i].push_back(g[j]);
        }
        sort(hs[i].begin(), hs[i].end());
    }
    cout << 1 << endl;
    for (int i = 2; i <= m; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (checkHash(i, j))
            {
                cout << j << endl;
                break;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    getPrimes();
    while (T--)
        solve();
    return 0;
}
