#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
struct node
{
    int l, r;
    mutable ll v;
    node(int L, int R, ll V) : l(L), r(R), v(V)
    {
    }
    inline bool operator<(const node &other) const
    {
        return l < other.l;
    }
};
using SIT = set<node>::iterator;
set<node> odt;
ll ksm(ll a, ll p, ll mod1)
{
    ll res = 1;
    a %= mod1;
    while (p)
    {
        if (p & 1)
            res = res * a % mod1;
        a = a * a % mod1;
        p >>= 1;
    }
    return res;
}
//分裂区间
SIT split(int x)
{
    SIT it = odt.lower_bound({x, 0, 0});
    if (it != odt.end() && it->l == x)
        return it;
    --it;
    int L = it->l, R = it->r;
    ll v = it->v;
    odt.erase(it);
    odt.emplace(L, x - 1, v);
    return odt.emplace(x, R, v).first;
}
//区间赋值
void assign(int l, int r, ll v)
{
    //注意应该先弄r+1，否则可能it1迭代器被erase掉了
    SIT it2 = split(r + 1), it1 = split(l);
    odt.erase(it1, it2);
    odt.emplace(l, r, v);
}
//区间加
void add(int l, int r, ll v)
{
    SIT it2 = split(r + 1), it1 = split(l);
    for (auto i = it1; i != it2; i++)
    {
        i->v += v;
    }
}
//区间第k大
ll kth(int l, int r, int k)
{
    vector<pair<ll, int>> rank;
    SIT it2 = split(r + 1), it1 = split(l);
    for (auto i = it1; i != it2; i++)
    {
        rank.emplace_back(i->v, i->r - i->l + 1);
    }
    sort(rank.begin(), rank.end());
    for (auto i : rank)
    {
        k -= i.second;
        if (k <= 0)
            return i.first;
    }
}
//区间幂次和
ll qry(int l, int r, ll p, ll mod1)
{
    SIT it2 = split(r + 1), it1 = split(l);
    ll res = 0;
    for (auto i = it1; i != it2; i++)
    {
        res = (res + (ll)(i->r - i->l + 1) * ksm(i->v, p, mod1) % mod1) % mod1;
    }
    return res;
}
ll n, m, seed, vmax;
ll random()
{
    ll ret = seed;
    seed = (seed * 7 + 13) % mod;
    return ret;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> seed >> vmax;
    for (int i = 1; i <= n; i++)
    {
        ll x = random() % vmax + 1;
        odt.emplace(i, i, x);
    }
    odt.emplace(n + 1, n + 1, 0);
    for (int i = 1; i <= m; i++)
    {
        int op, l, r;
        ll x, y;
        op = random() % 4 + 1;
        l = random() % n + 1;
        r = random() % n + 1;
        if (l > r)
            swap(l, r);
        if (op == 3)
        {
            x = (random() % (r - l + 1) + 1);
        }
        else
        {
            x = (random() % vmax + 1);
        }
        if (op == 4)
            y = (random() % vmax + 1);
        if (op == 1)
            add(l, r, x);
        else if (op == 2)
            assign(l, r, x);
        else if (op == 3)
            cout << kth(l, r, x) << endl;
        else
            cout << qry(l, r, x, y) << endl;
    }
    return 0;
}
