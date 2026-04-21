/**
 * @file 2225C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n;
    cin >> n;
    string s[2];
    cin >> s[0] >> s[1];

    int f = INT64_MAX, g = 0;
    for (int i = 0; i < n; i++) {
        int ng = g + (s[0][i] != s[1][i]);
        if (i) ng = min(ng, f + (s[0][i - 1] != s[0][i]) + (s[1][i - 1] != s[1][i]));
        f = g, g = ng;
    }

    cout << g << endl;

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
