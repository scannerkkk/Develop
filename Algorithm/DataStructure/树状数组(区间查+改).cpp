#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll tr1[N],tr2[N];//tr1维护bi,tr2维护i*bi
int n,m;
ll lowbit(int x)
{
    return x & (-x);
}
void add(ll tr[],int x,ll c)
{
    while(x <= n){
        tr[x] += c;
        x += lowbit(x);
    }
}
ll sig(ll tr[],ll x){
    ll res = 0;
    while(x > 0){
        res += tr[x];
        x -= lowbit(x);
    }
    return res;
}
ll qry(int x)
{
    return sig(tr1,x)*(x + 1)-sig(tr2,x);
}
int main()
{
    ll last=0,x;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%lld",&x);
        add(tr1,i,x-last);
        add(tr2,i,i*(x-last));
        last = x;
    }
    
    while(m--){
        int l,r;
        char op[2];
        scanf("%s%d%d",op,&l,&r);
        if(op[0] == 'C'){
            scanf("%lld",&x);
            add(tr1,l,x);add(tr1,r+1,-x);
            add(tr2,l,l*x);add(tr2,r+1,(r+1)*-x);
        }
        else{
            printf("%lld\n",qry(r) - qry(l-1));
        }
    }
    return 0;
}
