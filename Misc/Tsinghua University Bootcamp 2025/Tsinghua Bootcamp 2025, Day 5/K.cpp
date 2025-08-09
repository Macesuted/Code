/**
 * @file K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

string trans(string s) {
    if ('1' <= s[0] && s[0] <= '9') {
        reverse(s.begin(), s.end());
        string t;
        for (int i = 0; i < (int)s.size(); i++) {
            if (i > 0 && i % 3 == 0) t.push_back('\'');
            t.push_back(s[i]);
        }
        reverse(t.begin(), t.end());
        return t;
    }
    return s;
}

void solve(void) {
    string s;
    cin >> s;
    int p1 = 0;
    while (s[p1] != '=') p1++;
    int p2 = p1;
    while (s[p2] != '+') p2++;
    cout << s.substr(0, p1) << '=' << trans(s.substr(p1 + 1, p2 - p1 - 1)) << '+' << trans(s.substr(p2 + 1)) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}