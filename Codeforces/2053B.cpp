/**
 * @file 2053B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-28
 *
 * @copyright Copyright (c) 2024
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
    cin >> n;

    vector<int> cnt(2 * n + 1), sum(2 * n + 1), l(n + 1), r(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        if (l[i] == r[i]) cnt[l[i]]++;
    }

    for (int i = 1; i <= 2 * n; i++) sum[i] = sum[i - 1] + (cnt[i] == 0);

    for (int i = 1; i <= n; i++)
        if (l[i] == r[i])
            cout << (cnt[l[i]] == 1);
        else
            cout << (sum[r[i]] - sum[l[i] - 1] > 0);
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