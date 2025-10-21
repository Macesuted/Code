/**
 * @file 5422.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-21
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
    vector<int> cnt(26);
    for (auto c : s) cnt[c - 'a']++;
    int ans = 0;
    for (int i = 0; i < 26; i++) ans = max(ans, cnt[i]);
    cout << s.size() - ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
