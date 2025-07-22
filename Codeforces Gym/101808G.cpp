/**
 * @file 101808G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
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

void solve(void) {
    int n, X, Y;
    cin >> n >> X >> Y;

    int ans = 0, curX = Y, curY = X;
    vector<int> a(1, 0);
    for (int i = 1, v; i <= n; i++) {
        cin >> v;
        if (v % X != 0 || Y % v != 0)
            ans++;
        else
            curX = gcd(curX, v), curY = lcm(curY, v), a.push_back(v);
    }
    a.push_back(0);

    if (Y % X != 0) return cout << -1 << endl, void();
    if (n == 1 && X != Y) return cout << -1 << endl, void();

    if ((curX == X && curY == Y) || ans >= 2) return cout << ans << endl, void();

    if (ans == 1) return cout << 1 + (gcd(curX / X, Y / curY) > 1), void();

    vector<int> gl(a.size()), gr(a.size()), ll(a.size()), lr(a.size());
    gl[0] = Y, ll[0] = X;
    for (size_t i = 1; i < a.size() - 1; i++) gl[i] = gcd(gl[i - 1], a[i]), ll[i] = lcm(ll[i - 1], a[i]);
    gr[a.size() - 1] = Y, lr[a.size() - 1] = X;
    for (size_t i = a.size() - 2; i > 0; i--) gr[i] = gcd(gr[i + 1], a[i]), lr[i] = lcm(lr[i + 1], a[i]);

    for (size_t i = 1; i < a.size() - 1; i++) {
        int curX = gcd(gl[i - 1], gr[i + 1]), curY = lcm(ll[i - 1], lr[i + 1]);
        if (gcd(curX / X, Y / curY) == 1) return cout << 1 << endl, void();
    }

    cout << 2 << endl;

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