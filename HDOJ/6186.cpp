/**
 * @file 6186.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

#define maxn 100005

uint32_t a[maxn], pre[3][maxn], suf[3][maxn];

void solve(void) {
    int n, q;
    while (cin >> n >> q) {
        for (int i = 1; i <= n; i++) cin >> a[i];

        pre[0][0] = suf[0][n + 1] = UINT32_MAX;
        for (int i = 1; i <= n; i++) pre[0][i] = pre[0][i - 1] & a[i];
        for (int i = n; i >= 1; i--) suf[0][i] = suf[0][i + 1] & a[i];

        pre[1][0] = suf[1][n + 1] = 0;
        for (int i = 1; i <= n; i++) pre[1][i] = pre[1][i - 1] | a[i];
        for (int i = n; i >= 1; i--) suf[1][i] = suf[1][i + 1] | a[i];

        pre[2][0] = suf[2][n + 1] = 0;
        for (int i = 1; i <= n; i++) pre[2][i] = pre[2][i - 1] ^ a[i];
        for (int i = n; i >= 1; i--) suf[2][i] = suf[2][i + 1] ^ a[i];

        for (int i = 1, p; i <= q; i++) {
            cin >> p;
            cout << (pre[0][p - 1] & suf[0][p + 1]) << ' ' << (pre[1][p - 1] | suf[1][p + 1]) << ' '
                 << (pre[2][p - 1] ^ suf[2][p + 1]) << endl;
        }
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}