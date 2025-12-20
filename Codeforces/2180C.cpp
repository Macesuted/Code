/**
 * @file 2180C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, k;
    cin >> n >> k;

    vector<int> a(k);
    for (int i = 30; i >= 0; i--) {
        if (n >> i & 1) {
            assert(a[0] + (1 << i) <= n);
            a[0] += 1 << i;
            for (size_t j = 1; j + 1 < a.size(); j += 2) a[j] += 1 << i, a[j + 1] += 1 << i;
        } else
            for (size_t j = 0; j + 1 < a.size() && a[j + 1] + (1 << i) < n; j += 2) a[j] += 1 << i, a[j + 1] += 1 << i;
        sort(a.begin(), a.end());
    }

    for (auto x : a) cout << x << ' ';
    cout << endl;

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
