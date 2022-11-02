#include "bits/stdc++.h"
using namespace std;
using ll = long long;
/*
同余方程推导：
ax ≡ 1 (mod b)
∵gcd(a,b) == gcd(b,a % b)
ax + by = 1 
=> bx + (a % b)y = 1 
=> bx + (a - a / b * b)y = 1
=> bx + ay - a / b * by = 1
=> b(x - a / b * y) + ay = 1
可以看出原来的x = y1
原来的y = x1 - a / b * y1
特解：a*1 + b*0 = gcd(a,b)
通解：
ax1 + by1 = c
ax2 + by2 = c
=> a(x1 - x2) = b(y2 - y1)
=> a/g (x1 - x2) = b/g (y2 - y1) (同除gcd(a,b))
∵a/g 和 b/g 互质，所以a/g = -k(y1 - y2),b/g = k(x1 - x2)
=> x1 = x2 + b/g*k  y1 = y2 - a/b*k
∵gcd(a,b) == 1 
∴g = 1
∴x1 = x2 + b * k y1 = y2 - a * k
*/
int exgcd(int a,int b,int &x,int &y)
{
    if(!b)  {
        x = 1,y = 0;
        return a;
    }
    int d = exgcd(b,a % b,y,x);
    y -= a / b * x;
}
int main()
{
    int a,b,x,y;
    cin >> a >> b;
    exgcd(a,b,x,y);
    cout << (x % b + b) % b << endl;
    return 0;
}
