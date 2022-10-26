#include "bits/stdc++.h"
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define PII pair<int,int>
#define PDD pair<double,double>
#define fi first
#define se second
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define mt 114514
#define lim 0.95
const double eps = 1e-4;
const int N = 110;
using namespace std;
double ans = 1e9 + 10;
PDD p[N];
int n;
//等概率生成l-r中间的点
double rand(double l,double r)
{
    return (double) rand() / RAND_MAX * (r - l) + l;
}
double get_dis(PDD a,PDD b)
{
    double x1 = (a.fi - b.fi);
    double y1 = (a.se - b.se);
    return sqrtl(x1 * x1 + y1 * y1);
}
double calc(PDD t)
{
    double s = 0;
    for(int i = 1;i <= n;i++) s += get_dis(t,p[i]);
    ans = min(ans,s);
    return s;
}
void simulateAnneal()
{
    PDD pt = {rand(0,10000),rand(0,10000)};
    //t表示温度，注意t的范围必须为可以生成所有区域内的点，否则会被卡掉
    //t每次乘的是一个降温系数，若时间超限则可以降低系数，快速降温；若答案不对，可以升系数，让他极限接近于1
    for(double t = 1e4;t > eps;t *= 0.99) {
        PDD rpt = {rand(pt.fi - t,pt.fi + t),rand(pt.se - t,pt.se + t)};
        double delta = calc(rpt) - calc(pt);
        //如果成功了，则直接继承那个新点；否则以一定概率接受那个点
        if(exp(-delta / t) > rand(0,1)) pt = rpt;
    }
}
void solve()
{
    srand(mt);
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> p[i].fi >> p[i].se;
    //卡时函数，尽可能多跑几次模拟退火，以确保答案正确
    while((double)clock() / CLOCKS_PER_SEC < lim) simulateAnneal();//lim为题目时间限制
    cout << fixed << setprecision(0) << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T --) solve();
    return 0;
}
