// 1 a，在集合中插入一个新堆，堆中只包含一个数 a。
// 2 x y，将第 x 个插入的数和第 y 个插入的数所在的小根堆合并。数据保证两个数均未被删除。若两数已在同一堆中，则忽略此操作。
// 3 x，输出第 x 个插入的数所在小根堆的最小值。数据保证该数未被删除。
// 4 x，删除第 x 个插入的数所在小根堆的最小值（若最小值不唯一，则优先删除先插入的数）。数据保证该数未被删除。
#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;
int dis[N],l[N],r[N],f[N],v[N];
int idx;
int find(int x)
{
    return x == f[x] ? x : f[x] = find(f[x]);
}
int cmp(int x,int y)
{
    if(v[x] != v[y]) return v[x] < v[y];
    return x < y;
}
int merge(int x,int y)
{
    //当x或者y为0时，另一个作为根节点
    if(!x || !y) return x + y;
    if(cmp(y,x)) swap(x,y);
    r[x] = merge(r[x],y);
    //如果右边距离大于左边距离，则交换左右子树
    if(dis[r[x]] > dis[l[x]]) swap(r[x],l[x]);
    dis[x] = dis[r[x]] + 1;
    return x;
}
int main()
{
    int n,x,y;
    scanf("%d",&n);
    //避免误取0作为根节点
    v[0] = 2e9;
    while(n --) {
        int op;
        scanf("%d",&op);
        if(op == 1) {
            scanf("%d",&v[++ idx]);
            dis[idx] = 1;
            f[idx] = idx;
        }
        else if(op == 2) {
            scanf("%d%d",&x,&y);
            x = find(x),y = find(y);
            if(x != y) {
                if(cmp(y,x)) swap(x,y);
                f[y] = x;
                merge(x,y);
            }
        }
        else if(op == 3) {
            scanf("%d",&x);
            printf("%d\n",v[find(x)]);
        }
        else {
            scanf("%d",&x);
            x = find(x);
            if(cmp(r[x],l[x])) swap(r[x],l[x]);
            //并查集换根操作，实际上不删除x节点
            //把左偏树左节点作为根，左节点的父亲为自己
            f[x] = l[x],f[l[x]] = l[x]; 
            merge(l[x],r[x]);
        }
    }
    return 0;
}
