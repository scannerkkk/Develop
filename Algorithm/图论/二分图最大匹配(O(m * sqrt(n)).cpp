// Problem: P2756 飞行员配对方案问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2756
// Memory Limit: 125 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 2e2 + 10, M = 1e5 + 10;
int cur[N], he[N], d[110], idx;
// O(m*sqrt(n))解决二分图最大匹配问题
struct Edge
{
    int nt, to, wi;
} e[M];
int n, m;
void add(int u, int v, int w)
{
    e[idx] = {he[u], v, w};
    he[u] = idx++;

    e[idx] = {he[v], u, 0};
    he[v] = idx++;
}
bool bfs()
{
    queue<int> q;
    q.push(0);
    memset(d, -1, sizeof(d));
    d[0] = 0, cur[0] = he[0];
    while (q.size())
    {
        int v = q.front();
        q.pop();
        for (int i = he[v]; ~i; i = e[i].nt)
        {
            int j = e[i].to, w = e[i].wi;
            if (d[j] == -1 && w)
            {
                d[j] = d[v] + 1;
                cur[j] = he[j];
                if (j == n + 1)
                    return true;
                q.push(j);
            }
        }
    }
    return false;
}
int dfs(int u, int limit)
{
    if (u == n + 1)
        return limit;
    int mxFlow = 0;
    for (int i = cur[u]; ~i && mxFlow < limit; i = e[i].nt)
    {
        int j = e[i].to;
        cur[u] = i;
        if (d[j] == d[u] + 1 && e[i].wi)
        {
            int tmp = dfs(j, min(limit - mxFlow, e[i].wi));
            if (!tmp)
                d[j] = -1;
            e[i].wi -= tmp, mxFlow += tmp, e[i ^ 1].wi += tmp;
        }
    }
    return mxFlow;
}
int dinics()
{
    int mxFlow = 0, Flow = 0;
    while (bfs())
    {
        while (Flow = dfs(0, 1e9))
        {
            mxFlow += Flow;
        }
    }
    return mxFlow;
}
void solve()
{
    memset(he, -1, sizeof(he));
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
    {
        add(0, i, 1);
    }
    for (int i = m + 1; i <= n; i++)
    {
        add(i, n + 1, 1);
    }
    int u, v;
    while (cin >> u >> v && u != -1)
    {
        add(u, v, 1);
    }
    cout << dinics() << endl;
    int cnt = 0;
    for (int i = 0; i < idx; i += 2)
    {
        if (e[i].to < n + 1 && e[i].to > m && !e[i].wi)
        {
            cout << e[i ^ 1].to << ' ' << e[i].to << endl;
        }
    }
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
