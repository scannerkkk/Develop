// Problem: K. Largest Common Submatrix
// Contest: Codeforces - The 2019 ICPC Asia Yinchuan Regional Contest
// URL: https://codeforces.com/gym/104021/problem/K
// Memory Limit: 512 MB
// Time Limit: 1000 ms
#include "bits/stdc++.h"
#define rep(i, z, n) for (int i = z; i <= n; i++)
#define per(i, n, z) for (int i = n; i >= z; i--)
#define endl "\n"
#define ll long long
#define db double
#define PII pair<int, int>
#define fi first
#define se second
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
using namespace std;
const int N = 1e3 + 10;
PII mp[N * N];
int a[N][N], b[N][N], lft[N][N], rit[N][N], hei[N][N];
void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            lft[i][j] = rit[i][j] = j;
            hei[i][j] = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> b[i][j];
            mp[b[i][j]] = {i, j};
        }
    //尝试向右偏移
    for (int i = 1; i <= n; i++)
    {
        for (int j = m - 1; j >= 1; j--)
        {
            PII r = mp[a[i][j + 1]];
            if (a[i][j] == b[r.fi][r.se - 1])
            {
                rit[i][j] = rit[i][j + 1];
            }
        }
    }
    //尝试向左偏移
    for (int i = 1; i <= n; i++)
    {
        for (int j = 2; j <= m; j++)
        {
            PII l = mp[a[i][j - 1]];
            if (a[i][j] == b[l.fi][l.se + 1])
            {
                lft[i][j] = lft[i][j - 1];
            }
        }
    }
    int ans = 0;
    // dp调整悬线高度
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            PII u = mp[a[i - 1][j]];
            if (i > 1 && b[u.fi + 1][u.se] == a[i][j])
            {
                hei[i][j] = hei[i - 1][j] + 1;
                lft[i][j] = max(lft[i][j], lft[i - 1][j]);
                rit[i][j] = min(rit[i][j], rit[i - 1][j]);
            }
            ans = max(ans, hei[i][j] * (rit[i][j] - lft[i][j] + 1));
        }
    }
    cout << ans << endl;
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
