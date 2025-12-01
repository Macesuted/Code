/**
 * @file FDUPC25P-B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-27
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
    string s, t;
    cin >> s;
    for (size_t i = 0; i < s.size(); i++) {
        t.push_back(s[i]);
        if (i >= 10 && s.substr(i - 10, 11) == "TuLingJiang") t.push_back('~');
    }

    cout << t << endl;

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
