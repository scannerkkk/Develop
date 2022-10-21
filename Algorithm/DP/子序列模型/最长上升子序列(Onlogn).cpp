#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int dp1[N],dp2[N],idx,cur1,cur2,a[N];
int main()
{
    int i = 1;
    while(cin >> a[i])i++;
    for(int j = 1;j < i;j++) {
        //这里时lower_bound，因为相等的话不需要新建系统
        if(cur2 == 0) dp2[++cur2] = a[j];
        else {
            idx = lower_bound(dp2 + 1,dp2 + 1 + cur2,a[j]) - dp2;
            if(idx == cur2 + 1)  dp2[++cur2] = a[j];
            else dp2[idx] = a[j];
        }
        
        //注意求上升要用upper_bound，因为相等的话需要新建系统
        if(cur1 == 0) dp1[++cur1] = -a[j];
        else {
            idx = upper_bound(dp1 + 1,dp1 + 1 + cur1,-a[j]) - dp1;
            if(idx == cur1 + 1) dp1[++cur1] = -a[j];
            else dp1[idx] = -a[j];
        }
    }
    cout << cur1 << endl << cur2 << endl;
    return 0;
}
