/*****************************
bitset, 圧位
    bitset<10000> s;
    ~, &, |, ^
    >>, <<
    ==, !=
    []

    count()  返回有多少个1

    any()  判断是否至少有一个1
    none()  判断是否全为0

    set()  把所有位置成1
    set(k, v)  将第k位变成v
    reset()  把所有位变成0
    flip()  等价于~
    flip(k) 把第k位取反
    
    
二进制中1的个数
 int :
__builtin_popcount()
long long :
__builtin_popcountll()
****************************/
#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
bitset<N> tmp,ans;
int main()
{
    int n;
    //牛客练习赛22 简单瞎搞题
    cin >> n;
    //把第0为弄为1
    ans.set(0);
    while(n--){
        int l,r;
        cin >> l >> r;
        //全部赋值为0
        tmp.reset();
        for(int i = l;i <= r;i++) tmp |= (ans << i * i);
        ans = tmp;
    }
    cout<<ans.count()<<endl;
    return 0;
}


