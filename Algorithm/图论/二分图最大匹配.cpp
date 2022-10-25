#include "bits/stdc++.h"
using namespace std;
const int N = 510;
int n1,n2,m,he[N],cnt,match[N];
bool vis[N];
struct Edge{
    int to;
    int nxt;
}edge[200010];
void add(int u,int v)
{
    edge[++cnt].to = v;
    edge[cnt].nxt = he[u];
    he[u] = cnt;
}
bool find(int x)
{   
    vis[x] = true;
    for(int i = he[x];i != -1;i = edge[i].nxt){
        if(!vis[edge[i].to]){
            vis[edge[i].to] = true;    
            //如果对方没有匹配点，或者有匹配点但是能换一个匹配点
            if(!match[edge[i].to] || find(match[edge[i].to])){
                match[edge[i].to] = x;
                return true;
            }
        }
    }   
    return false;
}
int main()
{
    memset(he,-1,sizeof(he));
    cin >> n1 >> n2 >> m;
    while(m--){
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    int res = 0;
    for(int i = 1;i <= n1;i++){
        //把右半部分访问重新初始化
        memset(vis,0,sizeof(vis));
        if(find(i)) res++;
    }
    cout<<res<<endl;
    return 0;
}
