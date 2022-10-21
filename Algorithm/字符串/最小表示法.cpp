#include "bits/stdc++.h"
using namespace std;
int a[600010];
int n;
//可以解决类似于循环同构串的最小字典序问题
//原串abcd
//循环同构串 abcd  bcda  cdab dabc
//时间复杂度为O(n)
int get_min()
{
	for(int i = 1;i <= n;i++) a[i + n] = a[i];
	int i = 1,j = 2;
	while(i <= n && j <= n) {
		int k = 0;
		while(k < n && a[i + k] == a[j + k]) k++;
		if(a[i + k] > a[j + k]) i += k + 1;
		else j += k + 1;
		if(i == j) j++;
	}
	return min(i,j);
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	int idx = get_min();
	for(int i = idx;i - idx < n;i++) printf("%d ",a[i]);
	return 0;
}
