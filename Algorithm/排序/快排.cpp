//快排
#include "bits/stdc++.h"
using namespace std;
int a[100010];
void quick_sort(int a[],int l,int r)
{
    if(l >= r) return ;
    int st = l - 1,ed = r + 1,x = a[(l + r) >> 1];
    while(st < ed){
        while(a[--ed] > x) ;
        while(a[++st] < x) ;
        if(st < ed) swap(a[st],a[ed]);
    }
    quick_sort(a,l,ed);
    quick_sort(a,ed+1,r);
}
int main()
{
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) cin >> a[i];
    quick_sort(a,0,n-1);
    for(int i = 0;i < n;i++) cout<<a[i]<<' ';
    return 0;
}
