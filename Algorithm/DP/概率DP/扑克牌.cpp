#include "bits/stdc++.h"
using namespace std;
const int N = 14;
const double inf = 1e16;
double f[N][N][N][N][5][5];
int A,B,C,D;
double dp(int a,int b,int c,int d,int x,int y)
{
    if(a + (x == 0) + (y == 0) >= A && b + (x == 1) + (y == 1) >= B &&
       c + (x == 2) + (y == 2) >= C && d + (x == 3) + (y == 3) >= D) return 0;
    int s = 54 - (a + b + c + d) - (x != 4) - (y != 4);
    if(s <= 0) return f[a][b][c][d][x][y] = inf;
    if(f[a][b][c][d][x][y]) return f[a][b][c][d][x][y];
    double res = 0;
    if(a < 13) res += (13.0 - a) / s * (dp(a + 1,b,c,d,x,y) + 1);
    if(b < 13) res += (13.0 - b) / s * (dp(a,b + 1,c,d,x,y) + 1);
    if(c < 13) res += (13.0 - c) / s * (dp(a,b,c + 1,d,x,y) + 1);
    if(d < 13) res += (13.0 - d) / s * (dp(a,b,c,d + 1,x,y) + 1);
    if(x == 4) {
        double v = inf;
        for(int i = 0;i < 4;i++) v = min(v,1.0 / s * (dp(a,b,c,d,i,y) + 1));
        res += v; 
    }
    if(y == 4) {
        double v = inf;
        for(int i = 0;i < 4;i++) v = min(v,1.0 / s * (dp(a,b,c,d,x,i) + 1));
        res += v;
    }
    return f[a][b][c][d][x][y] = res;
}
int main()
{
    cin >> A >> B >> C >> D;
    double ans = dp(0,0,0,0,4,4);
    if(ans >= inf / 2) ans = -1;
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}
