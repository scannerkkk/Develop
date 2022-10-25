#include "bits/stdc++.h"
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
const int N = 2e6 + 10,M = 2e6 + 10;
int dfn[N],id[N],he[N],low[N],ins[N];
int idx,cnt,ts;
stack <int> stk;
PII e[M];
void add(int a,int b)
{
    e[++ idx] = {he[a],b};
    he[a] = idx;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++ ts;
    ins[u] = true;stk.push(u);
    for(int i = he[u];~i;i = e[i].fi) {
        int j = e[i].se;
        if(!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }
        else if(ins[j]) low[u] = min(low[u],dfn[j]);
    }
    if(low[u] == dfn[u]) {
        cnt ++;
        int y;
        do {
            y = stk.top();
            id[y] = cnt;
            ins[y] = false;
            stk.pop();
        }while(y != u);
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(he,-1,sizeof(he));
    for(int i = 1;i <= m;i++) {
        int x,y,a,b;
        scanf("%d%d%d%d",&x,&a,&y,&b);
        x --,y --;
        add(2 * x + !a,2 * y + b);
        add(2 * y + !b,2 * x + a);
    }
    for(int i = 0;i < 2 * n;i++)
        if(!dfn[i])
            tarjan(i);
    vector <int> v;
    for(int i = 0;i < n;i ++) {
        if(id[i * 2] == id[i * 2 + 1]) {
            puts("IMPOSSIBLE");
            return 0;
        }
        v.push_back(id[i * 2] < id[i * 2 + 1] ? 0 : 1);
    }
    puts("POSSIBLE");
    for(auto x:v) printf("%d ",x);
    return 0;
}
