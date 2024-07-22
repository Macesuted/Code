/**
 * @file 7454.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    map<char, int> cnt;

    string s;
    cin >> s, s = ' ' + s;
    for (int i = 1; i <= 8; i++) cnt[s[i]]++;

    if (s[1] == s[5]) return cout << s[1] << endl, void();
    if (cnt[s[1]] == cnt[s[5]]) return cout << 'N' << endl, void();
    return cout << (cnt[s[1]] > cnt[s[5]] ? s[1] : s[5]) << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}