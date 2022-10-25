#include "bits/stdc++.h"
using namespace std;
const int N = 510,M = 2100;
int g[N][N],in[N];
int m,n = 500;
stack <int> ans;
void dfs(int x)
{
    for(int i = 1;i <= n;i++) {
        if(g[x][i]) {
            g[x][i] --,g[i][x] --;
            dfs(i);
        }
    }
    ans.push(x);
}
int main()
{
    cin >> m;
    for(int i = 1;i <= m;i++) {
        int a,b;
        cin >> a >> b;
        g[a][b] ++,g[b][a] ++;
        in[a] ++,in[b] ++;
    }
    int st = 1;
    while(st <= n && !(in[st] & 1)) st ++;
    if(!(in[st] & 1)) st = 1;
    dfs(st);
    while(ans.size()) {
        cout << ans.top() << '\n';
        ans.pop();
    }
    return 0;
}
