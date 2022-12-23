#include "bits/stdc++.h"
#define son(x, k) tr[x].s[k]
#define fa(x) tr[x].p
#define sz(x) tr[x].siz
#define cn(x) tr[x].cnt
#define va(x) tr[x].v
using namespace std;
const int N = 2e5 + 10;
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
    k == 0 ? root = x : root = root;
}
inline void find(int v)
{
    int x = root;
    while (son(x, v > va(x)) && v != va(x))
    {
        x = son(x, v > va(x));
    }
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
    {
        x = son(x, 1);
    }
    return x;
}
inline int get_suf(int v)
{
    find(v);
    int x = root;
    if (va(x) > v)
    {
        return x;
    }
    x = son(x, 1);
    while (son(x, 0))
    {
        x = son(x, 0);
    }
    return x;
}
inline void del(int v)
{
    int pre = get_pre(v), suf = get_suf(v);
    splay(pre, 0), splay(suf, pre);
    int num = son(suf, 0);
    if (cn(num) > 1)
    {
        cn(num)--, splay(num, 0);
    }
    else
    {
        son(suf, 0) = 0, splay(suf, 0);
    }
}
inline int get_rk(int v)
{
    find(v);
    return sz(son(root, 0));
}
inline int get_va(int k)
{
    //插入了哨兵所以要+1
    k++;
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
            {
                x = y;
            }
            else
            {
                break;
            }
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
    insert(-1e9), insert(1e9);
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int op, v;
        scanf("%d%d", &op, &v);
        // cout << "debug:" << m << endl;
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
            printf("%d\n", get_va(v));
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
