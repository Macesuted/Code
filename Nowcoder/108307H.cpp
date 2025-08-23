/**
 * @file 108307H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    string s;
    cin >> s;

    if (s[0] == s[2]) return cout << "No" << endl, void();
    if (s[1] == '-' && s[0] != '0') return cout << "No" << endl, void();

    cout << "Yes" << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}