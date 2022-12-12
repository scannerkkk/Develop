#include "bits/stdc++.h"
using namespace std;
using ll = long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l, ll r)
{
    ll x = rng() % (r - l + 1) + l;
    return x;
}
int main()
{
    cout << rand(0, 1e12) << endl;
    return 0;
}
