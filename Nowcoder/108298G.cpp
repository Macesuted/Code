/**
 * @file 108298G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s, s = ' ' + s;
    while (q--) {
        string t;
        int a;
        cin >> t >> a, t = ' ' + t;
        int64_t ans = 0;
        int cur = 0;
        for (int i = 1; i < (int)t.size(); i++)
            if (s[i + a - 1] == t[i])
                cur++;
            else
                ans += (int64_t)cur * (cur + 1) / 2, cur = 0;
        cout << ans + (int64_t)cur * (cur + 1) / 2 << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
