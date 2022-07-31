/**
 * @file 1704A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, m;
    string a, b;
    cin >> n >> m >> a >> b;
    for (int i = 1; i < m; i++)
        if (a[n - m + i] != b[i]) return cout << "NO" << endl, void();
    int cnt[2] = {0, 0};
    for (int i = 0; i <= n - m; i++) cnt[a[i] - '0']++;
    if (cnt[b[0] - '0'] == 0) return cout << "NO" << endl, void();
    cout << "YES" << endl;
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