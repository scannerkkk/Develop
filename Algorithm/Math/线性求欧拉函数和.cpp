#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
int prime[N],is_prime[N];
long long s[N];
int cnt;
int main()
{
    int n;
    cin >> n;
    s[1] = 1;
    for(int i = 2;i <= n;i++) {
        if(!is_prime[i]) {
            prime[++cnt] = i;
            s[i] = i - 1;
        }
        for(int j = 1;prime[j] <= n / i;j++) {
            is_prime[prime[j] * i] = true;
            if(i % prime[j] == 0) {
                s[i * prime[j]] = s[i] * prime[j];
                break;
            }
            else s[i * prime[j]] = s[i] * (prime[j] - 1);
        }
    }
    long long res = 0;
    for(int i = 1;i <= n;i++) res += s[i];
    cout << res << endl;
    return 0;
}
