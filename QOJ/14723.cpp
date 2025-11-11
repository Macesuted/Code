/**
 * @file 14723.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int a[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);

    bool chk = true;
    for (int i = 1; i <= n; i++) chk &= (a[i] == b[i]);
    if (chk) return cout << "Yes" << endl, void();

    bool fnd[2] = {false, false};
    for (int i = 1; i < n; i++) fnd[0] |= (a[i] + 1 == a[i + 1]), fnd[1] |= (b[i] + 1 == b[i + 1]);

    if (!fnd[0] || !fnd[1]) return cout << "No" << endl, void();

    int cnt[2] = {0, 0};
    for (int i = 1; i <= n; i++) cnt[0] += a[i] & 1, cnt[1] += b[i] & 1;
    if (cnt[0] == cnt[1]) return cout << "Yes" << endl, void();

    return cout << "No" << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}