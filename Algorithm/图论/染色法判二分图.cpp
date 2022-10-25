#include "bits/stdc++.h"
using namespace std;
struct node{
    int nxt;
    int to;
}e[200010];
int he[100010],cnt,color[100010];
void add(int u,int v)
{
    e[++cnt].nxt = he[u];
    e[cnt].to = v;
    he[u] = cnt;
}
bool dfs(int u,int c)
{
    color[u] = c;
    for(int i = he[u];i != -1;i = e[i].nxt){
        //如果没有被染色
        if(!color[e[i].to]){
            //如果出现了矛盾
            if(!dfs(e[i].to,3 - c)) return false;      
        }
        //如果同一个点被染成了同一个颜色，那么就是
        else if(color[e[i].to] == c) return false;
    }
    return true;
}
int main()
{
    int n,m;
    memset(he,-1,sizeof(he));
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }
    
    bool flag = true;
    for(int i = 1;i <= n;i++){
        if(!color[i]) if(!dfs(i,1)) flag = false;
    }
    if(flag) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}
