// Problem: Dinic/ISAP求最大流
// Contest: AcWing
// URL: https://www.acwing.com/problem/content/2174/
// Memory Limit: 64 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 1e5 + 10, M = 2e5 + 10;
int he[N], idx, S, T;
int cur[N], d[N];
struct Edge
{
    int nt, to;
    ll wi;
} e[M];
void add(int u, int v, int w)
{
    e[idx] = {he[u], v, w};
    he[u] = idx;
    idx++;

    e[idx] = {he[v], u, 0};
    he[v] = idx;
    idx++;
}
bool bfs()
{
    //求增广路，用d表示分层图，防止有环产生
    memset(d, -1, sizeof(d));
    queue<int> que;
    que.push(S);
    cur[S] = he[S];
    d[S] = 0;
    while (que.size())
    {
        int v = que.front();
        que.pop();
        for (int i = he[v]; ~i; i = e[i].nt)
        {
            int j = e[i].to, w = e[i].wi;
            if (d[j] == -1 && w)
            {
                d[j] = d[v] + 1;
                cur[j] = he[j];
                if (j == T)
                {
                    return true;
                }
                que.push(j);
            }
        }
    }
    return false;
}
ll dfs(int u, ll limit)
{
    if (u == T)
        return limit;
    ll mxFlow = 0;
    //求最大流，给反边加上流，可以反悔
    for (int i = cur[u]; ~i && mxFlow < limit; i = e[i].nt)
    {
        ll j = e[i].to, &w = e[i].wi;
        cur[u] = i;
        if (d[j] == d[u] + 1 && w)
        {
            ll tmp = dfs(j, min(w, limit - mxFlow));
            if (!tmp)
            {
                d[j] = -1;
            }
            w -= tmp, e[i ^ 1].wi += tmp, mxFlow += tmp;
        }
    }
    return mxFlow;
}
ll dinics()
{
    ll mxFlow = 0, flow = 0;
    while (bfs())
    {
        while (flow = dfs(S, 1e18))
            mxFlow += flow;
    }
    return mxFlow;
}
void solve()
{
    int n, m;
    memset(he, -1, sizeof(he));
    cin >> n >> m >> S >> T;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    cout << dinics() << endl;
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
