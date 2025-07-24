/**
 * @file 104396L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
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

using tiii = tuple<int, int, int>;

void solve(void) {
    int X, Y, Z, n;
    cin >> X >> Y >> Z >> n;

    map<tiii, int> rec;

    auto add = [&](int xl, int yl, int zl, int xr, int yr, int zr, int delt) -> void {
        rec[{xl, yl, zl}] += delt;
        rec[{xr, yl, zl}] -= delt, rec[{xl, yr, zl}] -= delt, rec[{xl, yl, zr}] -= delt;
        rec[{xr, yr, zl}] += delt, rec[{xr, yl, zr}] += delt, rec[{xl, yr, zr}] += delt;
        rec[{xr, yr, zr}] -= delt;
        return;
    };

    add(0, 0, 0, X, Y, Z, -1);

    for (int i = 1, xl, yl, zl, xr, yr, zr; i <= n; i++)
        cin >> xl >> yl >> zl >> xr >> yr >> zr, add(xl, yl, zl, xr, yr, zr, +1);

    for (auto [xyz, v] : rec)
        if (v) return cout << "No" << endl, void();

    cout << "Yes" << endl;

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