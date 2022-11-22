#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
ll bell[1010][1010];
// bell[i][i]表示基数为n的集合的划分方法的数量
void init(int n)
{
    bell[1][1] = 1;
    for (int i = 2; i <= n; i++)
    {
        bell[i][1] = bell[i - 1][i - 1];
        for (int j = 2; j <= i; j++)
        {
            bell[i][j] = (bell[i][j - 1] + bell[i - 1][j - 1]) % mod;
        }
    }
}
int main()
{
    init(1000);
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << bell[i][j] << '\t';
        }
        cout << endl;
    }
    return 0;
}
