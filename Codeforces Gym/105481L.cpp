/**
 * @file 105481L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

typedef tuple<int64_t, int64_t, bool> tllb;

vector<tllb> f;
int64_t base;

bool chk(int64_t n) {
    for (int64_t v = 1; v <= 1e16; v *= 100)
        if (n % (4 * v) == 0 && n % (100 * v) != 0) return true;
    return false;
}

void solve(void) {
    int64_t n, ans = 0;
    cin >> n, n += base;
    for (auto [c, v, typ] : f) {
        int64_t t = n / v;
        if (typ && t == 25) {
            ans += 25 * c - 1;
            break;
        }
        n -= t * v, ans += t * c;
    }
    while (chk(ans)) ans--;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    f.emplace_back(1, 1, false);
    for (int64_t v = 1; v <= 1e16; v *= 100) {
        int64_t x = get<1>(f.back());
        f.emplace_back(4 * v, 4 * x - 1, true);
        x = get<1>(f.back());
        f.emplace_back(100 * v, 25 * x + 1, false);
    }
    reverse(f.begin(), f.end());

    int64_t n = 2024;
    base = 0;
    for (auto [c, v, t] : f)
        while (n >= c) n -= c, base += v;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}