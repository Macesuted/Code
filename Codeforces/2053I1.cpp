/**
 * @file 2053I1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-29
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

#define maxn 3000005

typedef pair<int, int> pii;

int a[maxn];
int64_t fl[maxn], fr[maxn];

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    fl[0] = fr[n + 1] = 0;
    for (int i = 1; i <= n; i++) fl[i] = fl[i - 1] + a[i];
    for (int i = n; i; i--) fr[i] = fr[i + 1] + a[i];

    if (fl[n] < 0) return cout << n << endl, void();

    int64_t deltl = 0, deltr = 0;
    int ans = n + (0 < deltl || 0 > deltr);
    for (int i = 1; i <= n; i++) {
        int64_t dl = max(-fl[i - 1], -fl[i]), dr = min(+fr[i], +fr[i + 1]);
        if (dl > deltr || dr < deltl) ans++, deltl = dl, deltr = dr;
        deltl = max(deltl, dl), deltr = min(deltr, dr);
    }

    cout << ans + (0 < deltl || 0 > deltr) << endl;

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