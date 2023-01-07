// Problem: P5071 [Ynoi2015] 此时此刻的光辉
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5071
// Memory Limit: 500 MB
// Time Limit: 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#ifdef dbg
#define D(...) fprintf(stderr, __VA_ARGS__)
#define DD(...) D(#__VA_ARGS__ " = "), debug_helper::debug(__VA_ARGS__), D("\n")
#include "C:\Users\wsyear\Desktop\OI\templates\debug.hpp"
#else
#define D(...) ((void)0)
#define DD(...) ((void)0)
#endif
#define rep(i, j, k) for (int i = (j); i <= (k); ++i)
#define per(i, j, k) for (int i = (j); i >= (k); --i)
#define SZ(v) int((v).size())
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define gc getchar
#define pc putchar
using ll = long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

using namespace std;

template <class T = int> T read() {
  T x = 0; bool f = 0; char ch = gc();
  while (!isdigit(ch)) f = ch == '-', ch = gc();
  while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = gc();
  return f ? -x: x;
}
template <class T> void write(T x) {
  if (x >= 0) { if (x > 9) write(x / 10); pc(x % 10 + 48); }
  else { pc('-'); if (x < -9) write(-x / 10); pc(48 - x % 10); }
}

namespace pr {
  mt19937_64 rnd(random_device{}());
  using ull = unsigned long long;
  using u128 = unsigned __int128;
  
  struct barrett_64 {
    ull mod, r;
    u128 k;
    barrett_64(ull _mod) {
      mod = _mod;
      r = __lg(mod);
      if ((1ull << r) < mod) r++;
      k = ((r == 64 ? u128(0) : u128(1) << r * 2) - 1) / mod + 1;
    }
    ull mul(ull a, ull b) {
      u128 c = ((u128(a) * b >> r) * k) >> r;
      if (c) c--;
      u128 d = u128(a) * b - u128(c) * mod;
      while (d >= mod) d -= mod;
      return d;
    }
    ull sub(ull a, ull b) { return a < b ? a - b + mod : a - b; }
    ull add(ull a, ull b) { return sub(a, mod - b); }
  } reducer(1);
  
  ull gcd(ull a, ull b) { return b ? gcd(b, a % b) : a; }
  ull qpow(ull a, ull b) {
    ull res(1);
    for (; b; b >>= 1, a = reducer.mul(a, a))
      if (b & 1) res = reducer.mul(res, a);
    return res;
  }
  bool is_prime(ull n) {
    if (n <= 1) return false;
    vector<ull> base = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (ull p : base) {
      if (n == p) return true;
      if (n % p == 0) return false;
    } 
    reducer = barrett_64(n);
    ull m = (n - 1) >> __builtin_ctz(n - 1);
    for (ull p : base) {
      ull t = m, a = qpow(p, m);
      while (t != n - 1 && a != 1 && a != n - 1)
        a = reducer.mul(a, a), t *= 2;
      if (a != n - 1 && t % 2 == 0) return false;
    }
    return true;
  }
  ull get_factor(ull n) {
    if (n % 2 == 0) return 2;
    reducer = barrett_64(n);
    auto f = [&](ull x) { return reducer.add(reducer.mul(x, x), 1); };
    ull x = 0, y = 0, tot = 0, p = 1, q, g;
    for (ull i = 0; (i & 0xff) || (g = gcd(p, n)) == 1; i++) {
      if (x == y) {
        x = tot, y = f(x);
        if (++tot == n) tot = 0;
      }
      q = reducer.mul(p, reducer.sub(x, y));
      if (q) p = q;
      x = f(x), y = f(f(y));
    }
    return g;
  }
  
  vector<ull> solve(ull n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    ull d = get_factor(n);
    auto v1 = solve(d), v2 = solve(n / d);
    auto i1 = v1.begin(), i2 = v2.begin();
    vector<ull> ans;
    while (i1 != v1.end() || i2 != v2.end()) {
      if (i1 == v1.end()) ans.push_back(*i2++);
      else if (i2 == v2.end()) ans.push_back(*i1++);
      else {
        if (*i1 < *i2) ans.push_back(*i1++);
        else ans.push_back(*i2++);
      }
    }
    return ans;
  }
}
void work() {
  ll n = read<ll>();
  auto res = pr::solve(n);
  __int128 t = res.back();
   t *= t;
   t *= res[0];
   res.erase(unique(res.begin(),res.end()),res.end());
   if(t == n) {
       write(res[1]);
       putchar(' ');
       write(res[0]);
       putchar('\n');
   }
   else {
       write(res[0]);
       putchar(' ');
       write(res[1]);
       putchar('\n');
   }
}

int main() {
  int t = read();
  while (t--) work();
}
