/**
 * @file 1033G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-14
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

#define maxn 105

int64_t a[maxn], b[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    int64_t wa, wb, wf = 0, ws = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int s = 1; s <= 2 * m; s++) {
        for (int i = 1; i <= n; i++) b[i] = a[i] % s;
        b[n + 1] = 0, b[n + 2] = s - 1;
        sort(b + 1, b + n + 3);
        for (int i = n + 2, op = 0; i > 1; i--, op ^= 1) {
            int l = max(b[i - 1] + 1, b[n + 1 - op] / 2 + 1), r = min(b[i], (int64_t)m);
            int L = max(l, s - r), R = min(r, s - l);
            if (L > R) continue;
            (op ? wf : ws) += R - L + 1;
        }
    }
    wa = wb = (1LL * m * m - wf - ws) / 2;
    cout << wa << ' ' << wb << ' ' << wf << ' ' << ws << endl;
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