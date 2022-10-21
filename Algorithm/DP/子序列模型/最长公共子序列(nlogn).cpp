#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int p[N],a[N],b[N],ans[N],len;
int binary_search(int k)
{
    int l = 0,r = len;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(p[ans[mid]] >= p[k]) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}
int main()
{
    int n;
    cin >> n;
    memset(ans,0x3f,sizeof(ans));
    for(int i = 1;i <= n;i++) {
        cin >> a[i];
        p[a[i]] = i;
    }
    for(int i = 1;i <= n;i++) cin >> b[i];
    ans[0] = 0;
    for(int i = 1;i <= n;i++) {
        if(p[b[i]] > p[ans[len]]) ans[++len] = b[i];
        else ans[binary_search(b[i])] = b[i];
    }
    cout << len << endl;
    return 0;
}
