#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int heap[N],sz;
void down(int u)
{
	int t = u;
	if(u * 2 <= sz && heap[u * 2] < heap[t]) t = u * 2;
	if(u * 2 + 1 <= sz && heap[u * 2 + 1] < heap[t]) t = u * 2 + 1;
	if(u != t){
		swap(heap[u],heap[t]);
		down(t);
	}
}
void up(int u)
{
	while(u  / 2 && heap[u / 2] > heap[u]){
		swap(heap[u],heap[u/2]);
		u /= 2;	
	}
}
int main()
{
	int m;
	scanf("%d%d",&sz,&m);
	for(int i= 1;i <= sz;i++) scanf("%d",heap + i);
	//O(n)建堆
	for(int i = sz / 2;i;i--) down(i);
		
	while(m--){
		printf("%d ",heap[1]);
		heap[1] = heap[sz];
		sz--;
		down(1);
	}
	return 0;
}
