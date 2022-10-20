#include "bits/stdc++.h"
using namespace std;
vector<int> nums;
const int N = 200010;
int a[N],root[N],idx;//空间复杂度4n+nlogn 前一个n是操作数，后一个是数据量(保险开4n+)
struct node{
	int l,r;
	int cnt;
}seg[N * 20];
int find(int x)
{
	return lower_bound(nums.begin(),nums.end(),x) - nums.begin();
}
int build(int l,int r)
{
	int p = ++idx;
	if(l == r) return p;
	int mid = (l + r) >> 1;
	seg[p].l = build(l,mid);
	seg[p].r = build(mid + 1,r);
	return p;
}
//用值域做l和r，离散化来限制值域
int insert(int old,int l,int r,int x)
{
	int q = ++idx;
	seg[q] = seg[old];
	if(l == r) {
		seg[q].cnt++;
		return q;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) seg[q].l = insert(seg[old].l,l,mid,x);
	else seg[q].r = insert(seg[old].r,mid + 1,r,x);
	seg[q].cnt = seg[seg[q].l].cnt + seg[seg[q].r].cnt;
	return q;
}
int query(int q,int p,int l,int r,int k)
{
	if(l == r) return r;
	//l-r的新插入的元素个数，这些元素明显会比右子树的元素小
	int cnt = seg[seg[q].l].cnt - seg[seg[p].l].cnt;
	int mid = (l + r) >> 1;
	if(k <= cnt) return query(seg[q].l,seg[p].l,l,mid,k);
	else return query(seg[q].r,seg[p].r,mid+1,r,k - cnt);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	//离散化去重
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	int len = nums.size() - 1;
	root[0] = build(0,len);
	//插入元素，每个元素相当于一颗新树
	for(int i = 1;i <= n;i ++) root[i] = insert(root[i - 1],0,len,find(a[i]));
	while(m --) {
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",nums[query(root[r],root[l - 1],0,len,k)]);
	}
	return 0;
}
