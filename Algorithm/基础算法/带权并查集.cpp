#include "bits/stdc++.h"
using namespace std;
const int N = 40010,h = N / 2;
int cnt;
int f[N];
unordered_map<int,int> mp;
int get(int x)
{
    if(!mp.count(x)) mp[x] = ++ cnt;
    return mp[x];
}
int find(int x)
{
    return f[x] == x ? x : f[x] = find(f[x]);
}
int main()
{
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i = 0;i < N;i++) f[i] = i;
    int res = m;
    while(m --){
        int x,y,fx,fy;
        string op;
        cin >> x >> y >> op;
        x = get(x - 1),y = get(y);
        //x表示偶数，x+h表示奇数,带扩展域并查集考虑的是条件
        if(op == "odd"){
            if(find(x) == find(y)){
                res = res - m - 1;
                break;
            }
            f[find(x + h)] = find(y);
            f[find(y + h)] = find(x); 
        }
        else{
            if(find(x + h) == find(y)){
                res = res - m - 1;
                break;
            }
            f[find(x)] = find(y);
            f[find(x + h)] = find((y + h));
        }
    }
    printf("%d\n",res);
    return 0;
}
