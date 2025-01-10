/**
 * @file 105586G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-04
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

#define maxn 1000005

int a[maxn];

void solve(void) {
    int n, q, x, cnt[3] = {0, 0, 0};
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i] + 1]++;
    cin >> x;
    if (cnt[1] || cnt[0] == cnt[2]) return cout << "Yes" << endl, void();
    if (n <= 2) return cout << "No" << endl, void();

    for (int i = 2; i + 1 < n; i++)
        if (a[i] != a[i + 1]) return cout << "Yes" << endl, void();

    if (cnt[0] < cnt[2]) {
        if (!cnt[0]) return cout << "No" << endl, void();
        cout << "Yes" << endl, void();
    } else {
        if (a[1] == 1 && a[n] == 1) return cout << "Yes" << endl, void();
        if (a[1] == -1 && a[n] == -1) {
            if (n == 3 && a[2] == 1) return cout << "No" << endl, void();
            if (n == 4) return cout << "No" << endl, void();
            return cout << "Yes" << endl, void();
        }
        if (n == 3) return cout << "No" << endl, void();
        return cout << "Yes" << endl, void();
    }
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