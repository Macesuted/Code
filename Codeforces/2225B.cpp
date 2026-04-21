/**
 * @file 2225B.cpp
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
    string s;
    cin >> s;
    int n = s.size();

    int cnt = 0;
    for (int i = 1; i < n; i++) cnt += s[i] == s[i - 1];

    cout << (cnt <= 2 ? "YES" : "NO") << endl;

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
