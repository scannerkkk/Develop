#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
vector<ll> alls;
vector<PLL> add,query;
const int N=3e5+10;
//acwing 802区间和
ll a[N],s[N];
//查找离散化坐标
int find(int x){
    int l = 0,r = alls.size() - 1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1; 
    }
    return r + 1;
}
int main()
{
    int n,m;
    cin >> n >> m;

    //加值操作
    for(int i = 0;i < n;i++){
        ll x,c;
        cin >> x >> c;
        add.push_back({x,c});
        alls.push_back(x);
    }

    //查询操作
    for(int i = 0;i < m;i++){
        ll l,r;
        cin >> l >> r;
        query.push_back({l,r});
        alls.push_back(l);
        alls.push_back(r);
    }

    //去重 unique底层是双指针，故需要排序
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());

    //执行加操作
    for(auto it:add){
        int x = find(it.first);
        a[x] += it.second;
    }

    //预处理前缀和
    for(int i = 1;i <= alls.size();i++) s[i] = s[i - 1] + a[i];

    //处理查询
    for(auto it:query){
        int l = find(it.first);
        int r = find(it.second);
        cout<<s[r] - s[l - 1] << endl;
    }
    return 0;
}
