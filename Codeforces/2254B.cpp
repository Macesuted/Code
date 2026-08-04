/**
 * @file 2254B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-08-04
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
    string s;
    cin >> n >> s;

    int ans = 0, best = 0;
    for (int l = 0, r; l < (int)s.size(); l = r + 1) {
        r = l;
        while (r + 1 < (int)s.size() && s[r + 1] == s[l]) r++;

        ans++;

        if (l == r && l != 0 && r != (int)s.size() - 1) {
            best = max(best, 1);
            if (s[l - 1] == s[r + 1]) best = max(best, 2);
        }
    }

    cout << ans - best << endl;

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
