/**
 * @file 104772E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
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

#define maxn 100005

typedef pair<int, int> pii;

void solve(void) {
    int n;
    cin >> n;
    int f1, f2, f3, f4;
    bool x1 = true, x2 = true, x3 = true, x4 = true;
    set<pii> S;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        int g1 = x, g2 = y, g3 = x - y, g4 = x + y;
        if (i == 1) f1 = g1, f2 = g2, f3 = g3, f4 = g4;
        if (x1 && f1 != g1) x1 = false, S.emplace(f1, y - (f1 - g1)), S.emplace(f1, y), S.emplace(f1, y + (f1 - g1));
        if (x2 && f2 != g2) x2 = false, S.emplace(x - (f2 - g2), f2), S.emplace(x, f2), S.emplace(x + (f2 - g2), f2);
        if (x3 && f3 != g3) {
            x3 = false, S.emplace(x, x - f3), S.emplace(f3 + y, y);
            int d = f3 - g3;
            if (d % 2 == 0) S.emplace(x + d / 2, y - d / 2);
        }
        if (x4 && f4 != g4) {
            x4 = false, S.emplace(x, f4 - x), S.emplace(f4 - y, y);
            int d = f4 - g4;
            if (d % 2 == 0) S.emplace(x + d / 2, y + d / 2);
        }
        for (auto i = S.begin(); i != S.end();)
            if (i->first != x && i->second != y && abs(i->first - x) != abs(i->second - y))
                i = S.erase(i);
            else
                i++;
        // cerr << "###" << x1 << ' ' << f1 << ' ' << x2 << ' ' << f2 << ' ' << x3 << ' ' << f3 << ' ' << x4 << ' ' << f4 << endl;
        // for (auto [x, y] : S) cerr << x << ' ' << y << endl;
        // cerr << endl;
    }
    if (!S.empty()) return cout << "YES" << endl << S.begin()->first << ' ' << S.begin()->second << endl, void();
    if (x1) return cout << "YES" << endl << f1 << ' ' << 0 << endl, void();
    if (x2) return cout << "YES" << endl << 0 << ' ' << f2 << endl, void();
    if (x3) return cout << "YES" << endl << f3 << ' ' << 0 << endl, void();
    if (x4) return cout << "YES" << endl << f4 << ' ' << 0 << endl, void();
    cout << "NO" << endl, void();
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