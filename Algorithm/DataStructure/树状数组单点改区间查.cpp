#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int MAXN = 1e5 + 10;
int n,q;
int op,l1,r1,l2,r2;
int row[MAXN],col[MAXN];
struct node{
	ll bit[MAXN];
	node(){memset(bit,0,sizeof(bit));}
	ll lowbit(int pos){return pos&-pos;}
	void update(int pos,int val){while(pos<=n){bit[pos]+=val,pos+=lowbit(pos);}}
	ll px(int pos){ll sum=0;while(pos>0){sum+=bit[pos],pos-=lowbit(pos);}return sum;}
	ll rangeSum(int l,int r){return px(r)-px(l-1);}
}A,B;
int main()
{
	scanf("%d%d",&n,&q);
	while(q--){
		scanf("%d%d%d",&op,&l1,&r1);
		if(op==1){
			row[l1]++;
			col[r1]++;
			if(row[l1]==1) A.update(l1,1);
			if(col[r1]==1) B.update(r1,1);
		}
		else if(op==2){
			row[l1]--;
			col[r1]--;
			if(row[l1]==0) A.update(l1,-1);
			if(col[r1]==0) B.update(r1,-1);
		}
		else {
			scanf("%d%d",&l2,&r2);
			ll sum1 = A.rangeSum(l1,l2);
			ll sum2 = B.rangeSum(r1,r2);
			if(sum1==(l2-l1+1)||sum2==(r2-r1+1)) puts("Yes");
			else puts("No");
		}
	}	
	return 0;
}
