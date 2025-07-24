/**
 * @file 104396K.cpp
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

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;

    if (m >= k) return cout << "No" << endl, void();

    if (m == 0) {
        if (n > 26) return cout << "No" << endl, void();
        cout << "Yes" << endl;
        for (int i = 0; i < n; i++) cout << string(k, 'a' + i) << endl;
        return;
    }

    cout << "Yes" << endl;
    for (char x = 'a'; x <= 'z'; x++)
        for (char y = x + 1; y <= 'z'; y++) {
            for (int i = 0; i < k; i++) cout << (i % (m + 1) == m ? y : x);
            cout << endl;
            if (!--n) return;
        }

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