#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;

/*******N=ans=d=pα11∗pα22∗⋯∗pαkk(α1+1)(α2+1)…(αk+1)因为任何一个约数d可以表示成pβ11∗pβ22∗⋯∗pβkk,0≤βi≤αi
*********/
int main()
{
    int n;
    cin >> n;
    unordered_map<int,int> mp;
    while(n--){
        int x;
        cin >> x;
        for(int i = 2;i <= x / i;i++){
            while(x % i == 0){
                mp[i] ++;
                x /= i;
            }
        }
        
        if(x > 1) mp[x] ++;
    }
    
    long long res = 1;
    for(auto pc:mp)  res = res * (pc.second + 1) % mod;
    cout<<res<<endl;
    return 0;
}
