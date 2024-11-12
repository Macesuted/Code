/**
 * @file 9622.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

const int64_t lim = 1e9;

int64_t exgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) return x = 1, y = 0, a;
    int64_t d = exgcd(b, a % b, y, x);
    return y -= a / b * x, d;
}

void solve(void) {
    int64_t a, b;
    cin >> a >> b;

    int64_t beta1 = 1;
    while (b % 2 == 0) b /= 2, beta1 *= 2;
    while (b % 5 == 0) b /= 5, beta1 *= 5;

    if (b == 1) return cout << "0 1" << endl, void();
    a %= b;

    int ansc = INT_MAX, ansd = 1;
    for (int64_t beta2 = 1; beta2 * b <= lim; beta2 *= 2)
        for (int64_t beta3 = 1; beta2 * beta3 * b <= lim; beta3 *= 5) {
            int64_t v = (b - beta2 * beta3 % b * a % b) % b, x, y;
            exgcd(beta1, b, x, y);
            x = (v * x % b + b) % b, y = beta2 * beta3 * b;
            int64_t gg = gcd(x, y);
            x /= gg, y /= gg;
            if (ansc > x) ansc = x, ansd = y;
        }

    cout << ansc << ' ' << ansd << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}