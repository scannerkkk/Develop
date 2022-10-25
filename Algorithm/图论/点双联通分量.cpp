#include "bits/stdc++.h"
using namespace std;
const int N = 510,M = 1010;
struct node {
    int nt;
    int to;
}e[M];
int he[N],dfn[N],low[N],cut[N];
int idx,times,dcc_cnt,root;
stack <int> stk;
vector<int> dcc[N];
void add(int a,int b)
{
    e[++ idx].nt = he[a];
    e[idx].to = b;
    he[a] = idx;
}
void tarjan(int now)
{
    dfn[now] = low[now] = ++ times;
    stk.push(now);
    if(now == root && he[now] == -1) {
        ++ dcc_cnt;
        dcc[dcc_cnt].push_back(now);
        return ;
    }
    int cnt = 0;
    for(int i = he[now];~i;i = e[i].nt) {
        int v = e[i].to;
        if(!dfn[v]) {
            tarjan(v);
            low[now] = min(low[now],low[v]);
            if(dfn[now] <= low[v]) {
                cnt ++;
                if(root != now || cnt > 1) cut[now] = 1;
                int k;
                ++ dcc_cnt;
                do {
                    k = stk.top();
                    stk.pop();
                    dcc[dcc_cnt].push_back(k);
                }while(k != v);
                dcc[dcc_cnt].push_back(now);
            }
        }
        else low[now] = min(low[now],dfn[v]);
    }
}
int main()
{
    int T = 1,m;
    while(scanf("%d",&m) && m) {
        for(int i = 1;i <= dcc_cnt;i++) dcc[i].clear();
        while(stk.size()) stk.pop();
        memset(he,-1,sizeof(he));
        memset(dfn,0,sizeof(dfn));
        memset(cut,0,sizeof(cut));
        dcc_cnt = idx = 0;
        int n = 0;
        for(int i = 1;i <= m;i++) {
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v);add(v,u);
            n = max({n,u,v});
        }
        for(root = 1;root <= n;root++) if(!dfn[root]) tarjan(root);
        unsigned long long ans = 1;
        int res = 0;
        for(int i = 1;i <= dcc_cnt;i++) {
            int cnt = 0;
            for(int j = 0;j < dcc[i].size();j++) if(cut[dcc[i][j]]) cnt++;
            if(cnt == 0) {
                if(dcc[i].size() > 1) ans *= dcc[i].size() * (dcc[i].size() - 1) / 2,res += 2;
                else res++;
            }
            else if(cnt == 1) ans *= dcc[i].size() - 1,res ++;
        }
        // cout << dcc_cnt << endl;
        printf("Case %d: %d %llu\n",T++,res,ans);
    }
    return 0;
}
