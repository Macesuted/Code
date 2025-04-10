/**
 * @file 9920.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int a[maxn];
int64_t ans[maxn], fl[maxn], fr[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    auto Mod = [&](int v) { return v >= n ? v - n : v; };
    auto pl = [&](int v) { return Mod(v - 1 + n); };
    auto pr = [&](int v) { return Mod(v + 1); };

    fr[0] = 0;
    for (int i = 1; i < n; i++) fr[i] = ((a[i - 1] + fr[i - 1]) >> 1);
    fl[n - 1] = 0;
    for (int i = n - 2; ~i; i--) fl[i] = ((a[i + 1] + fl[i + 1]) >> 1);

    for (int i = 0; i < n; i++) ans[i] = a[i] + fl[i] + fr[i];

    for (int i = 1; i < n; i++) {
        fr[i] = 0;
        for (int j = pr(i); j != i; j = pr(j)) {
            int oVal = a[j] + fr[j];
            fr[j] = ((a[pl(j)] + fr[pl(j)]) >> 1);
            if (((a[j] + fr[j]) >> 1) == (oVal >> 1)) break;
        }
        fr[i - 1] = ((a[pl(i - 1)] + fr[pl(i - 1)]) >> 1);

        fl[i - 1] = 0;
        for (int j = pl(i - 1); j != i - 1; j = pl(j)) {
            int oVal = a[j] + fl[j];
            fl[j] = ((a[pr(j)] + fl[pr(j)]) >> 1);
            ans[j] = max(ans[j], a[j] + fl[j] + fr[j]);
            if (((a[j] + fl[j]) >> 1) == (oVal >> 1)) break;
        }
        fl[i] = ((a[pr(i)] + fl[pr(i)]) >> 1);
        ans[i - 1] = max(ans[i - 1], a[i - 1] + fl[i - 1] + fr[i - 1]);
        ans[i] = max(ans[i], a[i] + fl[i] + fr[i]);
    }

    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
