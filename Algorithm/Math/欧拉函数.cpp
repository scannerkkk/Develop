#include "bits/stdc++.h"
#define ll long long
using namespace std;
const int N = 1e6 + 10;
ll phi[N];
int prime[N],cnt;
bool vis[N];
ll get_eulers(int n)
{
	ll res = 0;
	phi[1] = 1;
	for(int i = 2;i <= n;i++){
		if(!vis[i]) {
			prime[++cnt] = i;
			//如果i是质数，与i互质的个数为i - 1
			phi[i] = i - 1;
		}
		for(int j = 1;prime[j] <= n / i;j++){
			vis[prime[j] * i] = true;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j]; 
				break;
			}else{
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for(int i = 1;i <= n;i++) res += phi[i];
	return res;
}
int main()
{
	int n;
	cin >> n;
	cout << get_eulers(n) << endl;
	return 0;
}
