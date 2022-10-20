#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int son[N * 32][2],idx,a[N];
void insert(int x)
{
    int p = 0;
    for(int i = 31;i >= 0;i--){
        if(!son[p][(x>>i)&1]) son[p][(x>>i)&1] = ++idx;
        p = son[p][(x>>i)&1];
    }
}
int query(int x)
{
    int p = 0,res = 0;
    for(int i = 31;i >= 0;i--){
        if(son[p][!((x>>i)&1)]) {
            p = son[p][!((x>>i)&1)];
            res += (1<<i);
            continue;
        }
        if(son[p][(x>>i)&1]) {
            p = son[p][(x>>i)&1];
            continue;
        }
        break;
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++){
        cin>>a[i];
        insert(a[i]);
    }
    int mx=-1;
    for(int i = 1;i <= n;i++){
        mx=max(mx,query(a[i]));
    }
    cout<<mx<<endl;
    return 0;
}
