/**
 * @file 108218H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using tiiii = tuple<int, int, int, int>;

void solve(void) {
    int n;
    cin >> n;

    int sum = (int64_t)(n + 2) * (n + 1) * n / 6;
    for (int h = sqrt(sum); h >= 1; h--) {
        if (sum % h) continue;
        int w = sum / h;
        if (w < n) continue;
        vector<tiiii> ans;
        vector<int> cnt(n + 1);
        for (int i = 1; i <= n; i++) cnt[i] = n - i + 1;
        for (int t = 0; t < sum / w; t++) {
            int rest = w, tx = 0;
            for (int i = n; i;)
                if (cnt[i]) {
                    ans.emplace_back(tx, t, tx + i, t + 1), tx += i;
                    rest -= i, cnt[i]--, i = min(i, rest);
                } else
                    i--;
            if (rest) break;
        }
        if (ans.size() != n * (n + 1) / 2) continue;
        cout << (sum / w + w) * 2 << endl;
        for (auto [x1, y1, x2, y2] : ans) cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
        break;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}