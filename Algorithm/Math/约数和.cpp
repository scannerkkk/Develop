#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;

/*************


如果 N=p1c1∗p2c2∗…∗pkckN=p1c1∗p2c2∗…∗pkck
约数个数：(c1+1)∗(c2+1)∗…∗(ck+1)(c1+1)∗(c2+1)∗…∗(ck+1)
约数之和：  (p10+p11+…+p1c1)∗…∗(pk0+pk1+…+pkck)


while(a --) t = (t * p + 1) % mod;

t=t∗p+1t=t∗p+1
t=1t=1
t=p+1t=p+1
t=p2+p+1t=p2+p+1
……
t=pb+pb−1+…+1
*************/
int main()
{
    unordered_map<int,int> mp;
    int n;
    cin >> n;
    while(n --){
        int x;
        cin >> x;
        for(int i =2;i <= x / i;i++) while(x % i == 0) mp[i] ++,x /= i;
        
        if(x > 1) mp[x] ++;
    }
    
    long long res = 1;
    for(auto pc:mp) {
        int p = pc.first,a = pc.second;
        long long t = 1;
        while(a --) t = (t * p + 1) % mod;
        res = res * t % mod;
    }
    cout<<res<<endl;
    return 0;
}
