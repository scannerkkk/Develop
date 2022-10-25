#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int n,m,k;
//acwing 1091理想的正方形
int mar[N][N],a[N],b[N],mx[N][N],mi[N][N],c[N],d[N],que[N];
void get_mi(int w[],int cp[],int lim)
{
    int hh = 0,tt = -1;
    for(int i = 1;i <= lim;i++) {
        if(hh <= tt && i - que[hh] >= k) hh++;
        while(hh <= tt && w[i] <= w[que[tt]]) tt--;
        que[++tt] = i;
        cp[i] = w[que[hh]];
    }
}
void get_mx(int w[],int cp[],int lim)
{
    int hh = 0,tt = -1;
    for(int i = 1;i <= lim;i++) {
        if(hh <= tt && i - que[hh] >= k) hh++;
        while(hh <= tt && w[i] >= w[que[tt]]) tt--;
        que[++tt] = i;
        cp[i] = w[que[hh]];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m >> k;
    for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) cin >> mar[i][j];
    //按行处理
    for(int i = 1;i <= n;i++) {
        get_mi(mar[i],mi[i],m);
        get_mx(mar[i],mx[i],m);
    }
    
    //按列处理
    int res = INT_MAX;
    for(int i = k;i <= m;i++) {
        for(int j = 1;j <= n;j++) {
            a[j] = mi[j][i];
            b[j] = mx[j][i];
        }
        get_mi(a,c,n);
        get_mx(b,d,n);
        for(int j = k;j <= n;j++) res = min(res,d[j] - c[j]);
    }
    cout << res << endl;
    return 0;
}
