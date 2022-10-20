#include "bits/stdc++.h"
using namespace std;
const int N=1e5+10;
int son[N][26],cnt[N],idx;
void insert(string s)
{
	int p = 0;
	for(int i = 0,len = s.length();i < len;i++){
		if(!son[p][s[i] - 'a']) son[p][s[i] - 'a'] = ++idx;
		p = son[p][s[i] - 'a'];
	}
	cnt[p]++;
}
int query(string s)
{
	int p = 0;
	for(int i = 0,len = s.length();i < len;i++){
		if(!son[p][s[i] - 'a']) return 0;
		p = son[p][s[i] - 'a'];
	}
	return cnt[p];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string s;
	int n;
	char op;
	cin>>n;
	while(n--){
		cin>>op>>s;
		if(op=='I') insert(s);
		else cout<<query(s)<<endl;
	}
	return 0;
}
