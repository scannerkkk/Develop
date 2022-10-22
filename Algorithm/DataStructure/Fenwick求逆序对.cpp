#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
int seg[3][N],a[N],de[N],sc[N];
int n;
int lowbit(int x)
{
    return x & -x;
}
int qry(int p,int x)
{
    int res = 0;
    while(x) {
        res += seg[p][x];
        x -= lowbit(x);
    }
    return res;
}
void add(int p,int x,int v)
{
    while(x <= n) {
        seg[p][x] += v;
        x += lowbit(x);
    }
}
int main()
{
    cin >> n;
    vector <int> nums;
    for(int i = 1;i <= n;i++) {
        cin >> a[i];
        nums.push_back(a[i]);
    }
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    for(int i = 1;i <= n;i++) a[i] = lower_bound(nums.begin(),nums.end(),a[i]) - nums.begin() + 1;
    //求逆正序对
    for(int i = 1;i <= n;i++) {
        de[i] = i - 1 - qry(1,a[i]);
        add(1,a[i],1);
    }
    //求正序对
    for(int i = n;i >= 1;i--) {
        sc[i] = qry(2,a[i]);
        add(2,a[i],1);
    }
    long long ans = 0;
    for(int i = 1;i <= n;i++) ans += 1LL * de[i] * sc[i];
    cout << ans << endl;
    return 0;
}
