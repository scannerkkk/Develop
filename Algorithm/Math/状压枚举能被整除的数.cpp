#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 20;
ll p[N];
//acwing890
int main()
{
    int n,m;
    ll ans = 0;
    cin >> n >> m;
    for(int i = 1;i <= m;i++) cin >> p[i];
    //状压枚举每个集合
    for(int i = 1;i < (1 << m);i ++){
        ll cnt = 0,res = 1;
        for(int j = 0;j < m;j++){
            if(i >> j & 1){
                cnt++;
                if(res * p[j + 1] > n){
                    res = -1;
                    break;
                }
                res *= p[j + 1];
            }
        }
        if(res != -1){
            if(cnt & 1) ans += n / res;
            else ans -= n / res;
        }
    }
    cout<<ans<<endl;
    return 0;
}
