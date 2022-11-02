#include "bits/stdc++.h"
using namespace std;
//当p不是质数，但a和p仍然互质时，只能用exgcd计算逆元
int exgcd(int a,int p,int &x,int &y)
{
	if(!p){
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(p,a % p,y,x);
	y -= a / p * x;
	return d;
}
int inv(int a,int p)
{
	int x,y;
	if(exgcd(a,p,x,y) == 1){
		x = (x % p + p)% p;
		return x;
	}else{
		//不存在逆元
		return -1;
	}
}
int main()
{
	int a,p;
	cin >> a >> p;
	cout<<inv(a,p);
	return 0;
}
