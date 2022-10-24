#include "bits/stdc++.h"
using namespace std;
int fa[10000],dep[10000];
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(u);
}
//按秩合并+路径压缩
void merge(int x,int y)
{
    int fx = find(x);
    int fy = find(y);
    if(dep[fx] < dep[fy]) swap(fx,fy);
    fa[fy] = fx;
    dep[fx] = max(dep[fy] + 1,dep[fx]);
}
int main()
{
    int n,m,p;
    cin >> n >> m >> p;
    for(int i = 1;i <= 5000;i++) fa[i] = i,dep[i] = 0;
    for(int i = 1;i <= m;i++){
        int l,r;
        cin >> l >> r;
        merge(l,r);
    }
    for(int i = 1;i <= p;i++){
        int l,r;
        cin >> l >> r;
        if(find(l) == find(r)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
