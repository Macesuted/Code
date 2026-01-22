/**
 * @file 15621.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using int128_t = __int128_t;

struct Frac {
    int64_t a, b;

    void norm(void) {
        int64_t g = gcd(a, b);
        a /= g, b /= g;
        return;
    }
    Frac(int64_t x, int64_t y) { a = x, b = y, norm(); }
    bool operator<(const Frac& o) const { return a * o.b < o.a * b; }
    Frac operator*(const Frac& o) const { return {a * o.a, b * o.b}; };
    int128_t floor(void) { return a / b; }
};

Frac solve(int a, int b, int c, int k) {
    int l = 0, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        Frac d = {mid, a};
        int128_t cur = min((Frac{a, 1} * d).floor(), (int128_t)k);
        cur = min(cur * (Frac{b, 1} * d).floor(), (int128_t)k);
        cur = min(cur * (Frac{c, 1} * d).floor(), (int128_t)k);
        (cur < k ? l : r) = mid;
    }
    Frac ans = {a, r};
    ans.norm();
    return ans;
}

void solve(void) {
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    Frac ans = max({solve(a, b, c, k), solve(b, a, c, k), solve(c, a, b, k)});
    return cout << ans.a << ' ' << ans.b << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
