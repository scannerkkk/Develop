#include "bits/stdc++.h"
#define PII pair<int,int>
#define x first
#define y second
using namespace std;
const int N = 1e5 + 10;
vector <PII> e[N];
double f[N];
double dp(int u)
{
    if(f[u] >= 0) return f[u];
    f[u] = 0;
    for(auto it:e[u]) {
        int w = it.y,v = it.x;
        f[u] += 1.0 * (w + dp(v)) / e[u].size();
    }
    return f[u];
}
int main()
{
    int n,m;
    cin >> n >> m;
    memset(f,-1,sizeof(f));
    for(int i = 1;i <= m;i++) {
        int a,b,c;
        cin >> a >> b >> c;
        e[a].push_back({b,c});
    }
    cout << fixed << setprecision(2) << dp(1) << endl;
    return 0;
}
