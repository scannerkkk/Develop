#include "bits/stdc++.h"
using namespace std;
bool cmp(vector<int> &A,vector<int> &B)
{
	if(A.size() != B.size()) return A.size() > B.size();
	for(int i = A.size() - 1;i >= 0;i--){
		if(A[i] != B[i])
			return A[i] > B[i];
	}
	return true;
}
vector<int> add(vector<int> &A,vector<int> &B)
{
	vector<int> C;
	int s=0;
	for(int i = 0;i < A.size()|| i < B.size();i++){
		if(i < A.size()) s += A[i];
		if(i < B.size()) s += B[i];
		C.push_back(s % 10);
		s /= 10;
	}
	if(s) C.push_back(1);
	return C;
} 
vector<int> sub(vector<int> &A,vector<int> &B)
{
	vector<int> C;
	for(int i = 0,s = 0;i < A.size();i++){
		//s表示借位
		s = A[i] - s;
		if(i < B.size()) s -= B[i];
		C.push_back((s + 10) % 10);
		if(s < 0) s = 1;
		else s = 0;
	}
	while(C.size() > 1 && C.back() == 0){
		C.pop_back();
	}
	return C;
}
vector<int> mul(vector<int> &A,vector<int> &B)
{
	int mx=max(A.size(),B.size()) + 1;
	vector<int> C(2 * mx),PC;
	for(int i = 0;i < A.size();i++)
		for(int j = 0;j < B.size();j++) 
			C[i+j] += A[i] * B[j];
	for(int i = 0;i < A.size() + B.size();i++){
		C[i + 1] += C[i] / 10;
		C[i] = C[i] % 10;
	}
	int i;
	for(i = A.size() + B.size() - 1;i >= 1;i--){
		if(C[i]) break;
	}
	for(int j=0;j <= i;j++){
		PC.push_back(C[j]);
	}
	return PC;
}
vector<int> div(vector<int> &A,int b,int &r)
{
	vector<int> C;
	r = 0;
	for(int i = A.size() - 1;i >= 0;i--){
		r = r * 10 + A[i];
		C.push_back(r / b);
		r = r % b;
	}
	reverse(C.begin(),C.end());
	while(C.size() > 1 && C.back() == 0) C.pop_back();
	return C;
}
/*********
答案C都是从后往前遍历
	1.减法用法：
  	 vector<int> C;
	 if(!cmp(A,B)) cout<<"-",C = sub(B,A);
	 else C = sub(A,B);
	 C从后往前遍历是答案
	
	
	2.高精度除只能做到一个大数除以一个小数
	  并且会带一个余数
*********/
int main()
{
	string a;
	int b,r;
	cin >> a >> b;
	vector<int>A,C;
	for(int i = a.size() - 1;i >= 0;i--) A.push_back(a[i]-'0');
	return 0;
}
