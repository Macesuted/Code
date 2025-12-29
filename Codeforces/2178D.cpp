/**
 * @file 2178D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-27
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

#define maxn 200005

using pii = pair<int, int>;

int a[maxn];
int id[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    if (m * 2 > n) return cout << -1 << endl, void();

    for (int i = 1; i <= n; i++) id[i] = i;
    sort(id + 1, id + n + 1, [&](int x, int y) { return a[x] < a[y]; });
    sort(a + 1, a + n + 1);

    vector<pii> ans;

    if (m > 0) {
        for (int i = 1; i < m; i++) ans.emplace_back(n - i + 1, i);
        for (int i = m; i + 1 < n - m + 1; i++) ans.emplace_back(i, i + 1);
        ans.emplace_back(n - m + 1, n - m);
    } else {
        int h = a[n], p = 1;
        while (a[n - 1] < h && p < n - 1) ans.emplace_back(p, n), h -= a[p++];
        if (a[n - 1] < h) return cout << -1 << endl, void();
        while (p < n) ans.emplace_back(p, p + 1), p++;
    }

    cout << ans.size() << endl;
    for (auto [x, y] : ans) cout << id[x] << ' ' << id[y] << endl;

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
