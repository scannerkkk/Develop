#include "bits/stdc++.h"
#define fa(x) tr[x].p
#define sz(x) tr[x].siz
#define va(x) tr[x].v
#define son(x, k) tr[x].s[k]
#define lz(x) tr[x].lazy
using namespace std;
const int N = 2e5 + 10;
struct Node
{
    int p, v, siz, lazy;
    int s[2];
    void init(int _p, int _v)
    {
        p = _p, v = _v;
        siz = 1;
    }
} tr[N];
int root, idx;
inline void push_up(int x)
{
    sz(x) = sz(son(x, 1)) + sz(son(x, 0)) + 1;
}
inline void push_dw(int x)
{
    if (lz(x))
    {
        swap(son(x, 0), son(x, 1));
        lz(son(x, 0)) ^= 1;
        lz(son(x, 1)) ^= 1;
        lz(x) = 0;
    }
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
    if (!k)
    {
        root = x;
    }
}
inline int get_va(int k)
{
    int x = root;
    while (true)
    {
        push_dw(x);
        if (sz(son(x, 0)) >= k)
            x = son(x, 0);
        else if (sz(son(x, 0)) + 1 == k)
            return x;
        else
            k -= sz(son(x, 0)) + 1, x = son(x, 1);
    }
    return x;
}
inline void insert(int v)
{
    int x = root, p = 0;
    while (x && va(x) != v)
    {
        p = x, x = son(x, v > va(x));
    }
    x = ++idx;
    son(p, v > va(p)) = x;
    tr[x].init(p, v);
    splay(x, 0);
}
int n, q;
inline void print(int x)
{
    push_dw(x);
    if (son(x, 0))
        print(son(x, 0));
    if (va(x) >= 1 && va(x) <= n)
        printf("%d ", va(x));
    if (son(x, 1))
        print(son(x, 1));
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 0; i <= n + 1; i++)
    {
        insert(i);
    }
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_va(l), r = get_va(r + 2);
        splay(l, 0), splay(r, l);
        lz(son(r, 0)) ^= 1;
    }
    print(root);
    return 0;
}
