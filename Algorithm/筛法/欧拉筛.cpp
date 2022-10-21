#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
bool vis[N];
int prime[N],cnt;
void get_prime(int n)
{
    for(int i = 2;i <= n;i++){
        if(!vis[i]) prime[++cnt] = i;
        for(int j = 1;prime[j] <= n / i;j++){
            vis[i * prime[j]] = true;
            if(i % prime[j] == 0) break;
        }
    }
    cout<<cnt<<endl;
}
int main()
{
    int n;
    cin >> n;
    get_prime(n);
    return 0;
}

