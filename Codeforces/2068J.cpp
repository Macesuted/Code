/**
 * @file 2068J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n;
    string s;
    cin >> n >> s;
    int cnt[2] = {0, 0};
    for (int i = 0; i < n; i++) cnt[s[i] == 'R']++;
    if (cnt[0] & 1) return cout << "NO" << endl, void();
    for (int i = 0; i < (cnt[0] >> 1); i++)
        if (s[i] == 'R' || s[s.size() - 1 - i] == 'W') return cout << "NO" << endl, void();
    cout << "YES" << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}