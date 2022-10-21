#include <bits/stdc++.h>
using namespace std;
//在本地运行不了，但是在牛客上能运行
using i128 = __int128;
inline i128 read()
{
    i128 x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

inline void write(i128 x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

int main()
{
    i128 a = read();
    i128 b = read();
    write(a + b);
    return 0;
}
