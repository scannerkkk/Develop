#include "bits/stdc++.h"
using namespace std;
const int N = 20010;
int cnt;
int f[N],d[N];
unordered_map<int,int> mp;
//食物链
int get(int x)
{
    if(!mp.count(x)) mp[x] = ++ cnt;
    return mp[x];
}
//维护相对关系，同时更新树
int find(int x)
{
    if(x == f[x]) return x;
    int root = find(f[x]);
    d[x] ^= d[f[x]];
    return f[x] = root;
}
int main()
{
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i = 0;i < N;i++) f[i] = i;
    int res = m;
    while(m --){
        int x,y,fx,fy,s = 0;
        string op;
        cin >> x >> y >> op;
        x = get(x - 1),y = get(y);
        if(op == "odd") s = 1;
        fx = find(x),fy = find(y);
        //0表示和根同类，1表示不同类
        if(fx == fy){
            if(d[x] ^ d[y] ^ s){
                res = res - m - 1;
                break;
            }
        }
        else{
            f[fy] = fx;
            d[fy] = d[x] ^ d[y] ^ s;
        }
    }
    printf("%d\n",res);
    return 0;
}
