/**
 * @file 969.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005
#define mod (int128_t)1'000'000'000'000'000'031

using int128_t = __int128_t;

int128_t qpow(int128_t a, int128_t x) {
    int128_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int64_t ans[maxn];

void solve(void) {
    ans[1000000] = 300;
    for (int i = 999999; i >= 0; i--) ans[i] = qpow(42, ans[i + 1]);
    int n;
    cin >> n;
    cout << ans[n] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
