#include "bits/stdc++.h"
#define ull unsigned long long
#define PUU pair<unsigned long long, unsigned long long>
using namespace std;
//常用二分+矩阵hash
const int N = 1010;
const int base1 = 131, base2 = 13331;
//mat是原矩阵
ull mat[N][N], h[N][N], p1[N], p2[N];
void init(int n, int m)
{
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        p1[i] = p1[i - 1] * base1;
    }
    for (int i = 1; i <= m; i++)
    {
        p2[i] = p2[i - 1] * base2;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            h[i][j] = h[i][j - 1] * base1 + mat[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            h[i][j] = h[i - 1][j] * base2 + h[i][j];
}
ull getHash(int i, int j, int len1, int len2)
{
    return h[i][j] - h[i - len1][j] * p1[len1] - h[i][j - len2] * p2[len2] +
           h[i - len1][j - len2] * p1[len1] * p2[len2];
}
int main()
{

    return 0;
}
