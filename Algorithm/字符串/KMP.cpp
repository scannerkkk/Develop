#include "bits/stdc++.h"
using namespace std;
const int N=1e6+10;
char s[N],p[N];
int nt[N];
//s是主串，p为模式串，n为主串长度，m为模式串长度
int main()
{
	int n,m;
	scanf("%d%s",&m,p + 1);
	scanf("%d%s",&n,s + 1);
	//求解next数组
	for(int i = 2,j = 0;i <= m;i++){
		while(j && p[i] != p[j + 1]) j = nt[j];
		if(p[i] == p[j + 1]) j++;
		nt[i] = j;
	}
	
	//匹配字符串
	for(int i = 1,j = 0;i <= n;i++){
		while(j && s[i] != p[j + 1]) j = nt[j];
		if(s[i] == p[j + 1]) j++;
		//匹配成功
		if(j == m) {
			printf("%d ",i - j);
			j = nt[j];
		}
	}
	return 0;
}   
