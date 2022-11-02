#include "bits/stdc++.h"
using namespace std;
const double eps = 1e-7;
const int N = 110;
//所求方程的系数矩阵
double a[N+1][N+2];
int n;
void out()
{
	for(int i = 1;i <= n;i++) {
		if(fabs(a[i][n + 1]) < eps) puts("0.00");
		else printf("%.2lf\n",a[i][n + 1]);
	}
}
void gauss()
{
	int c,r;
	for(c = 1,r = 1;c <= n;c++){
		int t = r;
		//找第c列绝对值最大的那一行，换到第r行
		for(int i = r + 1;i <= n;i++){
			if(fabs(a[i][c]) > fabs(a[t][c]))
				t = i;
		}
		if (fabs(a[t][c]) < eps) continue;
		//把当前这一行放到第r行，因为前面r-1行已经计算好了
		for(int i = c;i <= n + 1;i++) swap(a[t][i],a[r][i]);
		//把当前这一行第c列变成1，其他列也跟着变
		for(int i = n + 1;i >= c;i--) a[r][i] /= a[r][c];
		//把r+1-n行也跟着变换
		for(int i = r + 1;i <= n;i++){
			//如果当前这一行第c列已经是0，那么就不需要操作了
			if(fabs(a[i][c]) <= eps) continue;
			for(int j = n + 1;j >= c;j--){
				a[i][j] -= a[r][j] * a[i][c];
			}
		}
		r++;
	}
	//从后往前回代，把最后解求出来
	for(int i = n - 1;i >= 0;i--)
		for(int j = i + 1;j <= n;j++)
			//因为只需要求解最后的解，因此只需要对i操作
			a[i][n + 1] -= a[j][n + 1] * a[i][j];

	//判断解的情况
	if(r <= n){
		//无解
		for(int i = r;i <= n;i++)
			if(fabs(a[i][n + 1]) > eps){
				puts("No solution");
				return ;
			}
		//无穷解
		puts("Infinite group solutions");
	}
	else{
		//输出解的情况
		out();
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n + 1;j ++)
			scanf("%lf",&a[i][j]);
	gauss();
	return 0;
}
