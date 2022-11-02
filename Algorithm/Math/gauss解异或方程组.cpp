#include "bits/stdc++.h"
using namespace std;
const int N = 110;
int a[N][N],n;
int Gauss()
{
    int r,c;
    for(r = 1,c = 1;c <= n;c ++) {
        int t = r;
        //找元
        for(int i = r;i <= n;i++) {
            if(a[i][c]) {
                t = i;
                break;
            }
        }
        //无元
        if(!a[t][c]) continue;
        //换元
        for(int i = c;i <= n + 1;i++) swap(a[r][i],a[t][i]);
        //消元
        for(int i = r + 1;i <= n;i++) {
            if(a[i][c]) for(int j = n + 1;j >= c;j--) a[i][j] ^= a[r][j];
        }
        r++;
    }
    if(r <= n) {
        for(int i = r;i <= n;i++) if(a[i][n + 1]) return 0;
        return 1;
    }
    for(int i = n;i >= 1;i--) 
        for(int j = i - 1;j >= 1;j--) 
            a[j][n + 1] ^= a[j][i] & a[i][n + 1];
    return 2;
}
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n + 1;j++)
            cin >> a[i][j];
    int f = Gauss();
    if(f == 0) cout << "No solution" << endl;
    else if(f == 1) cout << "Multiple sets of solutions" << endl;
    else for(int i = 1;i <= n;i++) cout << a[i][n + 1] << endl;; 
    return 0;
}
