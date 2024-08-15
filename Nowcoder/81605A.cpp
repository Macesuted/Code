/**
 * @file 81605A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

void solve(void) {
    string s;
    cin >> s;
    int cur = 0, rest = 0;
    for (int i = 0; i < 5; i++)
        if (s[i] == 'Y')
            cur++;
        else if (s[i] == '-')
            rest++;
    if (cur + rest < 4) return cout << -1 << endl, void();
    if (cur >= 4) return cout << 1 << endl, void();
    cout << 0 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}