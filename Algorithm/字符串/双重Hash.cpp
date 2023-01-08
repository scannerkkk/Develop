#include "bits/stdc++.h"
#define fi first
#define se second
#define mp make_pair
#define ll long long
using namespace std;
const int N = 2e6 + 10;
const ll mod1 = 1000000033;
const ll mod2 = 1000000103;
typedef pair<int,int> hashv;

hashv operator + (hashv a,hashv b)
{
	int c1 = a.fi + b.fi,c2 = a.se + b.se;
	if(c1 >= mod1) c1 -= mod1;
	if(c2 >= mod2) c2 -= mod2;
	return mp(c1,c2);
}
hashv operator - (hashv a,hashv b)
{
	int c1 = a.fi - b.fi,c2 = a.se - b.se;
	if(c1 < 0) c1 += mod1;
	if(c2 < 0) c2 += mod2;
	return mp(c1,c2);
}
hashv operator * (hashv a,hashv b)
{
	int c1 = (ll)a.fi * b.fi % mod1,c2 = (ll) a.se * b.se % mod2;
	return mp(c1,c2);
}

hashv pw[N],s1[N],s2[N];
char s[N];
int main()
{
	int n;
	scanf("%d",&n);
	n *= 2;
	scanf("%s",s + 1);
	hashv base = mp(10331,100313);
	pw[0] = mp(1,1);
	for(int i = 1;i <= n;i++) {
		pw[i] = pw[i - 1] * base;
		s1[i] = s1[i - 1] * base + mp(s[i],s[i]);
	}
	for(int i = n;i >= 1;i--) s2[i] = s2[i + 1] * base + mp(s[i],s[i]);
	for(int i = 0;i <= n / 2;i++) {
		hashv t1 = s1[i] * pw[n / 2 - i] + (s1[n] - s1[i + n / 2] * pw[n / 2 - i]);
		hashv t2 = s2[i + 1] - s2[i + 1 + n / 2] * pw[n / 2];
		if(t1 == t2) {
			for(int j = n / 2 - 1;j >= 0;j--) printf("%c",s[i + j + 1]);
			puts("");
			printf("%d\n",i);
			exit(0);
		}
	}
	puts("-1");
	return 0;
}
