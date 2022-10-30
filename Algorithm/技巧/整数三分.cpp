#include "bits/stdc++.h"
using namespace std;
int a,b,c,l,r;
long long calc(int k)
{
    return 1LL * a * k * k + 1LL * b * k + c;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin >> T;
    while(T --) {
        cin >> a >> b >> c >> l >> r;
        int l1 = l,r1 = r,p1 = l,p2 = l;
        //整数三分极小值
        while(l1 < r1) {
            int lmid = l1 + (r1 - l1) / 3,rmid = r1 - (r1 - l1) / 3;
            long long ans1 = calc(lmid),ans2 = calc(rmid);
            if(ans1 <= ans2) r1 = rmid - 1;
            else l1 = lmid + 1;
        }
        p1 = l1;
        l1 = l,r1 = r;
        //整数三分极大值
        while(l1 < r1) {
            int lmid = l1 + (r1 - l1) / 3,rmid = r1 - (r1 - l1) / 3;
            long long ans1 = calc(lmid),ans2 = calc(rmid);
            if(ans1 <= ans2) l1 = lmid + 1;
            else r1 = rmid - 1;
        }
        p2 = l1;
        cout << calc(p1) << ' ' << calc(p2) << endl;
    }
    return 0;
}
