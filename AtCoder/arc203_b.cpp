/**
 * @file arc203_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-03
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

int a[maxn], b[maxn];

void solve(void) {
    int n, cnt[2][2] = {{0, 0}, {0, 0}};
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[0][a[i]]++;
    bool same = true;
    for (int i = 1; i <= n; i++) cin >> b[i], cnt[1][b[i]]++, same &= (a[i] == b[i]);

    if (same) return cout << "Yes" << endl, void();
    if (cnt[0][1] != cnt[1][1]) return cout << "No" << endl, void();
    if (cnt[0][1] == 1 && (a[1] == 1 || a[n] == 1 || b[1] == 1 || b[n] == 1)) return cout << "No" << endl, void();
    cout << "Yes" << endl;
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