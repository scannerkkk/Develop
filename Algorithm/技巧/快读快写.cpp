#include <bits/stdc++.h>
using namespace std;
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x = 0,f = 1;
    char ch = nc();
    while(ch < '0'||ch > '9')
    {
        if(ch == '-') f = -1;
        ch = nc();
    }
    while(ch >= '0'&&ch<='9') x = x * 10 + ch - '0',ch = nc();
    return x * f;
}
inline void write(int x){
    if(x > 9) write(x / 10);
    if(x < 0) putchar('-'),x = -x;
    putchar(x % 10 + '0');
}
int main() {
    int n;
    while((n = read()),n){
        write(n);
        putchar(' ');
    }
}
