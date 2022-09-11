/**
 * @file arc148_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

set<int> S;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, v; i <= 2 * n; i++) {
        cin >> v, v %= m;
        if (S.count(v))
            S.erase(v);
        else
            S.insert(v);
    }
    if (!(m & 1)) {
        for (auto i : S)
            if (!S.count((i + m / 2) % m)) return cout << "Alice" << endl, void();
        cout << (S.size() / 2 % 2 == 1 ? "Alice" : "Bob") << endl;
    } else
        cout << (S.empty() ? "Bob" : "Alice") << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}