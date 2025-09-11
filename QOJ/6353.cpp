/**
 * @file 6353.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

using pii = pair<int, int>;

const string base[12] = {"001011", "001101", "010011", "010110", "011001", "011010",
                         "100101", "100110", "101001", "101100", "110010", "110100"};

int a[maxn];
int64_t pw[maxn];

void solve(void) {
    int n, m;
    int64_t k;
    cin >> n >> m >> k;

    if (m == 1) {
        if (k == 1) {
            for (int i = 1; i <= n; i++) cout << 1 << ' ';
            cout << endl;
            return;
        }
        return cout << -1 << endl, void();
    }

    if (m == 2) {
        if (n == 1) {
            if (k == 1) return cout << 1 << endl, void();
            if (k == 2) return cout << 2 << endl, void();
            return cout << -1 << endl, void();
        }
        if (n == 2) {
            if (k == 1) return cout << 1 << ' ' << 2 << endl, void();
            if (k == 2) return cout << 2 << ' ' << 1 << endl, void();
            return cout << -1 << endl, void();
        }

        vector<string> ans;
        for (int i = 0; i < 12; i++) ans.push_back(base[i].substr(0, min(6, n)));
        ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        if (k > (int)ans.size()) return cout << -1 << endl, void();
        for (int i = 0; i < n; i++) cout << ans[k - 1][i % 6] - '0' + 1 << ' ';
        cout << endl;

        return;
    }

    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = min((__int128_t)pw[i - 1] * (m - 2), (__int128_t)1e18);

    auto calc = [&](int rest) -> int64_t {
        if (rest == 0) return 1;
        return min((__int128_t)(m - 2 + (rest == n - 1)) * pw[rest - 1], (__int128_t)1e18);
    };

    k--;

    for (int i = 1; i <= n; i++) {
        int64_t c = calc(n - i);
        int v = 1 + k / c;
        k %= c;
        a[i] = v;
        while (a[i] - (i >= 2 && a[i - 1] <= a[i]) - (i >= 3 && a[i - 2] <= a[i]) < v) a[i]++;
        if (a[i] > m) return cout << -1 << endl, void();
    }

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
