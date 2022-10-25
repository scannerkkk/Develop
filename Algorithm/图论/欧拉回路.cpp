#include "bits/stdc++.h"
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
const int N = 1e5 + 10,M = 4e5 + 10;
int T,n,m,idx;
int in[N],out[N],he[N];
bool use[M];
PII e[M];
stack <int> ans;
/*
欧拉通路：
有向图：图连通，有一个顶点出度大入度1，有一个顶点入度大出度1，其余都是出度=入度。

无向图：图连通，只有两个顶点是奇数度，其余都是偶数度的。

欧拉回路：
有向图：图连通，所有的顶点出度=入度。

无向图：图连通，所有顶点都是偶数度。
*/
void add(int a,int b)
{
    e[idx] = {he[a],b};
    he[a] = idx ++;
}
bool check(int t)
{
    if(t == 1) {
        for(int i = 1;i <= n;i++) 
            if(in[i] + out[i] & 1)
                return false;
    }
    else {
        for(int i = 1;i <= n;i++) 
            if(in[i] != out[i])
                return false;
    }
    return true;
}
void dfs(int x)
{
    for(int &i = he[x];~i;) {
        if(use[i]) {
            i = e[i].fi;
            continue;
        }
        use[i] = true;
        if(T == 1) use[i ^ 1] = true;
        int tmp;
        if(T == 1) {
            tmp = (i / 2 + 1);
            if(i & 1) tmp = -tmp;
        }
        else tmp = i + 1;
        int j = e[i].se;
        i = e[i].fi;
        dfs(j);
        ans.push(tmp);
    }
}
int main()
{
    cin >> T >> n >> m;
    int a,b;
    memset(he,-1,sizeof(he));
    for(int i = 1;i <= m;i++) {
        cin >> a >> b;
        add(a,b);
        if(T == 1) add(b,a);
        in[b] ++,out[a] ++;
    }
    if(!check(T)) {
        cout << "NO" << endl;
        return 0;
    }
    dfs(a);
    if(ans.size() < m) {
        cout << "NO" << endl;
        return 0;
    }
    else {
        cout << "YES" << endl;
        while(ans.size()) {
            cout << ans.top() << ' ';
            ans.pop();
        }
        cout << endl;
    }
    return 0;
}
