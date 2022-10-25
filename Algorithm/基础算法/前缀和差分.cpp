#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
/**************
一维前缀和
for(int i=1;i<=n;i++) cin >> a[i],sum[i]=sum[i-1] + a[i];
cout<<sum[r]-sum[l-1]<<endl;
***************/
/**************
二维前缀和
sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
printf("%lld\n",sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1]);
***************/
/**************
一维差分
//构造
d[i]=a[i]-a[i-1];
d[l]+=val;
d[r+1]-=val;

//还原
d[i]+=d[i-1];
**************/
/*************
二维差分
构造
d[x1][y1] += val;
d[x1][y2+1] -= val;
d[x2 + 1][y1] -= val;
d[x2+1][y2+1] += val;

还原
d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+d[i][j];
*************/
// void insert(int x1,int y1,int x2,int y2,int val)
// {
	// d[x1][y1] += val;
	// d[x1][y2+1] -= val;
	// d[x2 + 1][y1] -= val;
	// d[x2+1][y2+1] += val;
// }
