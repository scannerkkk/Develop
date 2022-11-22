#include "bits/stdc++.h"
using namespace std;
using db = double;
using ldb = long double;
//减小浮点数累加的差值
//实验得知double和long double精度有点差距
ldb kahan(vector<ldb> nums)
{
    ldb s = 0, c = 0;
    for (auto num : nums)
    {
        ldb y = num - c;
        ldb t = s + y;
        c = (t - s) - y;
        s = t;
    }
    return s;
}
int main()
{
    vector<ldb> nums;
    int n;
    cin >> n;
    ldb s1 = 0;
    for (int i = 1; i <= n; i++)
    {
        ldb t;
        cin >> t;
        nums.push_back(t);
    }
    return 0;
}
