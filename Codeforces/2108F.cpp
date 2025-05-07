/**
 * @file 2108F.cpps
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-07
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

int64_t a[maxn], delt[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto chk = [&](int x) -> bool {
        for (int i = 1; i <= n; i++) delt[i] = 0;

        int64_t cur = 0;
        for (int i = 1; i <= n; i++) {
            int64_t tar = max(0, x - 1 - (n - i));
            if (cur < tar) return false;
            delt[min((int64_t)n, i + (a[i] + cur - tar))]--;
            cur += 1 + delt[i];
        }

        return true;
    };

    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) >> 1;
        (chk(m) ? l : r) = m;
    }

    cout << l << endl;

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