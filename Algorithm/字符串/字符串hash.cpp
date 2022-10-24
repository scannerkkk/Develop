#include "bits/stdc++.h"
using namespace std;
typedef unsigned long long ULL;
const int N = 1e5 + 10;
char s[N];
ULL h[N],p[N];
const int P = 13331;//玄学数
//时间复杂度O(n) + O(m)
ULL get(int l,int r)
{
	return h[r] - h[l - 1] * p[r - l + 1];
}
int main()
{
	p[0] = 1; 
	int n,m;
	cin >> n >> m >> (s + 1);
	for(int i = 1;i <= n;i++){
		h[i] = h[i - 1] * P + s[i];
		p[i] = p[i - 1] * P;	
	}
	while(m--){
		int l1,r1,l2,r2;
		cin >> l1 >> r1 >> l2 >> r2;
		if(get(l1,r1) == get(l2,r2)) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
