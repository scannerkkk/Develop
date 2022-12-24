#include "bits/stdc++.h"
#define son(x, k) tr[x].s[k]
#define fa(x) tr[x].p
#define sz(x) tr[x].siz
#define cn(x) tr[x].cnt
#define va(x) tr[x].v
using namespace std;
const int N = 2e6 + 10;
char *p1, *p2, buf[100000];
#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
inline int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (ch < 48 || ch > 57)
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (ch >= 48 && ch <= 57)
        x = x * 10 + ch - 48, ch = nc();
    return x * f;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
struct node
{
    int s[2];
    int p, v, cnt, siz;
    void init(int _p, int _v)
    {
        p = _p, v = _v;
        cnt = siz = 1;
    }
} tr[N];
int root, idx;
inline void push_up(int x)
{
    sz(x) = sz(son(x, 1)) + sz(son(x, 0)) + cn(x);
}
inline void rotate(int x)
{
    int y = fa(x), z = fa(y), k = son(y, 1) == x;
    son(z, son(z, 1) == y) = x, fa(x) = z;
    son(y, k) = son(x, k ^ 1), fa(son(x, k ^ 1)) = y;
    son(x, k ^ 1) = y, fa(y) = x;
    push_up(y), push_up(x);
}
inline void splay(int x, int k)
{
    while (fa(x) != k)
    {
        int y = fa(x), z = fa(y);
        if (z != k)
        {
            (son(y, 0) == x) ^ (son(z, 0) == y) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
    k == 0 ? root = x : root;
}
inline void find(int v)
{
    int x = root;
    while (son(x, v > va(x)) && v != va(x))
        x = son(x, v > va(x));
    splay(x, 0);
}
inline int get_pre(int v)
{
    find(v);
    int x = root;
    if (va(x) < v)
        return x;
    x = son(x, 0);
    while (son(x, 1))
        x = son(x, 1);
    return x;
}
inline int get_suf(int v)
{
    find(v);
    int x = root;
    if (va(x) > v)
        return x;
    x = son(x, 1);
    while (son(x, 0))
        x = son(x, 0);
    return x;
}
inline void del(int v)
{
    int pre = get_pre(v), suf = get_suf(v);
    splay(pre, 0), splay(suf, pre);
    int num = son(suf, 0);
    if (cn(num) > 1)
        cn(num)--, splay(num, 0);
    else
        son(suf, 0) = 0, splay(suf, 0);
}
inline int get_rk(int v)
{
    int x = root, res = 0;
    while (x)
    {
        if (va(x) == v)
        {
            res += sz(son(x, 0));
            splay(x, 0);
            return res;
        }
        else if (va(x) > v)
            x = son(x, 0);
        else
            res += sz(son(x, 0)) + cn(x), x = son(x, 1);
    }
    if (va(x) == v)
        splay(x, 0);
    else
        splay(fa(x), 0);
    return res;
}
inline int get_va(int k)
{
    int x = root;
    while (true)
    {
        int y = son(x, 0);
        if (sz(y) + cn(x) < k)
        {
            k -= sz(y) + cn(x);
            x = son(x, 1);
        }
        else
        {
            if (sz(y) >= k)
                x = y;
            else
                break;
        }
    }
    splay(x, 0);
    return va(x);
}
inline void insert(int v)
{
    int x = root, p = 0;
    while (x && va(x) != v)
    {
        p = x, x = son(x, v > va(x));
    }
    if (x)
    {
        cn(x)++;
    }
    else
    {
        x = ++idx;
        son(p, v > va(p)) = x;
        tr[x].init(p, v);
    }
    splay(x, 0);
}
int main()
{
    //哨兵
    insert(-2e9), insert(2e9);
    int n;
    n = read();
    while (n--)
    {
        int op, v;
        op = read(), v = read();
        if (op == 1)
        {
            insert(v);
        }
        else if (op == 2)
        {
            del(v);
        }
        else if (op == 3)
        {
            printf("%d\n", get_rk(v));
        }
        else if (op == 4)
        {
            printf("%d\n", get_va(v + 1));
        }
        else if (op == 5)
        {
            printf("%d\n", va(get_pre(v)));
        }
        else
        {
            printf("%d\n", va(get_suf(v)));
        }
    }
    return 0;
}
