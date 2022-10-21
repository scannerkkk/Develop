#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
int c[N],x[N],sa[N],y[N],rk[N],height[N];
int n,m;
char s[N];
//后缀排序
void getSA()
{
    for(int i = 1;i <= n;i++) c[x[i] = s[i]] ++;
    for(int i = 2;i <= m;i++) c[i] += c[i - 1];
    for(int i = n;i >= 1;i--) sa[c[x[i]] --] = i;
    for(int k = 1;k <= n;k <<= 1) {
        int cnt = 0;
        for(int i = n - k + 1;i <= n;i++) y[++cnt] = i;
        for(int i = 1;i <= n;i++) if(sa[i] > k) y[++cnt] = sa[i] - k;
        for(int i = 1;i <= m;i++) c[i] = 0;
        for(int i = 1;i <= n;i++) c[x[i]] ++;
        for(int i = 2;i <= m;i++) c[i] += c[i - 1];
        for(int i = n;i >= 1;i--) sa[c[x[y[i]]]--] = y[i],y[i] = 0;
        swap(x,y);
        x[sa[1]] = 1,cnt = 1;
        for(int i = 2;i <= n;i++) {
            bool t = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]); 
            if(!t) ++ cnt;
            x[sa[i]] = cnt;
        }
        if(cnt == n) break;
        m = cnt;
    }
}
//求最长公共前缀
void getHeight()
{
    for(int i = 1;i <= n;i++) rk[sa[i]] = i;
    for(int i = 1,k = 0;i <= n;i++) {
        if(rk[i] == 1) continue;
        if(k) k --;
        int j = sa[rk[i] - 1];
        while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++;
        height[rk[i]] = k;
    }
}
int main()
{
    scanf("%s",s + 1);
    n = strlen(s + 1),m = 122;
    getSA();
    getHeight();
    for(int i = 1;i <= n;i++) printf("%d ",sa[i]);
    puts("");
    for(int i = 1;i <= n;i++) printf("%d ",height[i]);
    return 0;
}
