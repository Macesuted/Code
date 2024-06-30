/**
 * @file abc360_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
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

void solve(void) {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    s = ' ' + s;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            string p;
            for (int x = j; x <= n; x += i) p.push_back(s[x]);
            if (p == t) return cout << "Yes" << endl, void();
        }
    }
    cout << "No" << endl;
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