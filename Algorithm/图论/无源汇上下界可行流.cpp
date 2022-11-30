#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 225, M = 3e5 + 10;
ll w[N];
int he[N], cur[N], d[N], in[M], idx;
int S, T;
struct Edge {
    int nt, to;
    ll wi;
} e[M];
void add(int u, int v, ll w) {
    e[idx] = {he[u], v, w};
    he[u] = idx++;

    e[idx] = {he[v], u, 0};
    he[v] = idx++;
}
bool bfs() {
    queue<int> q;
    q.push(0);
    memset(d, -1, sizeof(d));
    d[0] = 0, cur[0] = he[0];

    while (q.size()) {
        int v = q.front();
        q.pop();

        for (int i = he[v]; ~i; i = e[i].nt) {
            int j = e[i].to, w = e[i].wi;

            if (d[j] == -1 && w) {
                d[j] = d[v] + 1;
                cur[j] = he[j];

                if (j == T)
                    return true;

                q.push(j);
            }
        }
    }

    return false;
}
ll dfs(int u, ll limit) {
    if (u == T)
        return limit;

    ll mxFlow = 0;

    for (int i = cur[u]; ~i && mxFlow < limit; i = e[i].nt) {
        cur[u] = i;
        int j = e[i].to;

        if (d[j] == d[u] + 1 && e[i].wi) {
            ll tmp = dfs(j, min(e[i].wi * 1LL, limit - mxFlow));

            if (!tmp)
                d[j] = -1;

            e[i].wi -= tmp, e[i ^ 1].wi += tmp, mxFlow += tmp;
        }
    }

    return mxFlow;
}
ll dinic() {
    ll mxFlow = 0, Flow = 0;

    while (bfs()) {
        while (Flow = dfs(S, 1e12))
            mxFlow += Flow;
    }

    return mxFlow;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    memset(he, -1, sizeof(he));
    int n, m, s, t, u, v;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> s >> t;
        w[v] += s;
        w[u] -= s;
        in[i - 1] = s;
        add(u, v, t - s);
    }

    S = 0, T = 221;
    ll tot = 0;

    for (int i = 1; i <= n; i++) {
        //相当于流入比流出多w[i],那么在差网络中要流出w[i]到汇点
        if (w[i] > 0) {
            tot += w[i];
            add(S, i, w[i]);
        }

        //相当于流出比流入多w[i],那么在差网络中源点要流出w[i]到i
        if (w[i] < 0) {
            add(i, T, -w[i]);
        }
    }

    if (dinic() != tot) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;

        for (int i = 0; i < m * 2; i += 2) {
            cout << e[i ^ 1].wi + in[i / 2] << endl;
        }
    }

    return 0;
}
