#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>
#include <cstdio>
#include <climits>
#define PII pair<int,int>
#define rep(i,z,n) for(int i = z;i <= n; i++)
#define per(i,n,z) for(int i = n;i >= z; i--)
#define ll long long
#define db double
#define vi vector<int>
#define debug(x) cerr << "!!!" << x << endl;
using namespace std;
inline ll rd()
{
	ll s,r;
	r = 1;
	s = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-')
			r = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + (ch ^ 48);
		ch = getchar();
	}
	return s * r;
}
inline void wt(ll x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) wt(x / 10);
	putchar(x % 10 + '0');
}
ll gcd(ll a,ll b)
{
	if(!b) return a;
	else return gcd(b,a%b);
}
ll lcm(ll a,ll b)
{
	return a*b/gcd(a,b);
}
const int N=2e5+10;
int n,lgx,q;
ll st[N][32],Log[N];
ll search(int l,int r)
{
	int ver=Log[r-l+1];
	//令r-(1<<ver)+1+(1<<ver)-1==r 区间分成了l-(1<<ver)-1  (1<<ver)-r
	return max(st[l][ver],st[r-(1<<ver)+1][ver]);
}	
void initLog()
{
	Log[0]=0,Log[1]=0,Log[2]=1;
	for(int i=3;i<=n;i++) Log[i]=Log[i/2]+1;
}
void buildST()
{
	initLog();
	for(int i=1;i<=Log[n];i++) for(int j=1;j+(1<<i)-1<=n;j++){
		st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	}
}
int main()
{
	n=rd(),q=rd();
	for(int i=1;i<=n;i++) st[i][0]=rd();
	buildST();
	while(q--){
		int l,r;
		l=rd(),r=rd();
		printf("%lld\n",search(l,r));
	}
	return 0;
}
