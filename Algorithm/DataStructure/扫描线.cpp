// Problem: P5490 【模板】扫描线
#include "bits/stdc++.h"
#define lson(x) x << 1
#define rson(x) x << 1 | 1
#define nson(l, r) (l + r) >> 1
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
ll lazy[N << 3], s[N << 3];
struct Line
{
    ll x, y1, y2;
    ll cover;
    bool operator<(const Line &other) const
    {
        return x < other.x;
    }
} line[N << 3];
struct Segment
{
    ll l, r, v;
} seg[N << 3];
void push_up(int u)
{
    if (lazy[u])
    {
        seg[u].v = seg[u].r - seg[u].l;
    }
    else
    {
        seg[u].v = seg[lson(u)].v + seg[rson(u)].v;
    }
}
void build(int u, ll l, ll r)
{
    if (r - l <= 1)
    {
        seg[u].l = s[l];
        seg[u].r = s[r];
        seg[u].v = 0;
    }
    else
    {
        seg[u] = {s[l], s[r], 0};
        build(lson(u), l, nson(l, r));
        build(rson(u), nson(l, r), r);
        push_up(u);
    }
}
void modify(int u, ll y1, ll y2, ll v)
{
    if (seg[u].l >= y1 && seg[u].r <= y2)
    {
        lazy[u] += v;
        push_up(u);
        return;
    }
    if (y1 < seg[lson(u)].r)
        modify(lson(u), y1, y2, v);
    if (y2 > seg[rson(u)].l)
        modify(rson(u), y1, y2, v);
    push_up(u);
}
int main()
{
    int n;
    scanf("%d", &n);
    ll x1, x2, y1, y2;
    unsigned long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        line[i] = {x1, y1, y2, 1};
        line[i + n] = {x2, y1, y2, -1};
        s[i] = y1, s[i + n] = y2;
    }
    sort(s + 1, s + 1 + 2 * n);
    sort(line + 1, line + 1 + 2 * n);
    build(1, 1, 2 * n);
    modify(1, line[1].y1, line[1].y2, line[1].cover);
    for (int i = 2; i <= 2 * n; i++)
    {
        ans += (line[i].x - line[i - 1].x) * seg[1].v;
        modify(1, line[i].y1, line[i].y2, line[i].cover);
    }
    printf("%llu\n", ans);
    return 0;
}
