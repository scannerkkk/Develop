#include "bits/stdc++.h"
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define PII pair<int,int>
#define fi first
#define se second
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
using namespace std;
const int N = 3e7 + 10;
char s[N],a[N];
int p[N];
void manacher(char *t)
{
    int len = strlen(t),k = 0,mr = 0,mid = 0,ans = 0;
    s[k ++] = '$';s[k ++] = '#';
    for(int i = 0;i < len;i++) s[k ++] = t[i],s[k ++] = '#';
    s[k ++] = '^';
    for(int i = 1;i < k;i++) {
        if(i < mr) p[i] = min(p[2 * mid - i],mr - i);
        else p[i] = 1;
        while(s[i + p[i]] == s[i - p[i]]) p[i] ++;
        if(p[i] + i > mr) mr = p[i] + i,mid = i;
        ans = max(ans,p[i] - 1);
    }
    cout << ans << endl;
}
void solve()
{
    cin >> a;
    manacher(a);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T = 1;
    T = 1;
    while(T --) solve();
    return 0;
}
