/**
 * @file 16116.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int a[maxn];

void solve(void) {
    int n, b;
    cin >> n >> b;
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = n;
    for (int t = 0; t < b; t++) {
        vector<int> pos;
        for (int i = 0; i < n; i++)
            if (!(a[i] >> t & 1)) pos.push_back(i);

        if (pos.size() == 0) continue;
        if (pos.size() == (size_t)n) return cout << 1 << endl, void();

        for (int i = 0; i < n; i++)
            if (!(a[i] >> t & 1) && !(a[(i + 1) % n] >> t & 1) && !(a[(i + 2) % n] >> t & 1)) return cout << 1 << endl, void();

        vector<pair<int, int>> npos;
        for (size_t i = 0; i < pos.size(); i++) {
            int d = (pos[(i + 1) % pos.size()] + n - pos[i] - 1) % n;
            if (d) ans = min(ans, d);
        }
    }

    cout << max(1, ans) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
