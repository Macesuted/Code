/**
 * @file 451E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define mod 1000000007

int64_t a[25], inv[50];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int64_t binom(int64_t n, int64_t m) {
    int64_t ans = 1;
    for (int64_t i = n - m + 1; i <= n; i++) ans = i % mod * ans % mod;
    for (int64_t i = 1; i <= m; i++) ans = ans * inv[i] % mod;
    return ans;
}

void solve(void) {
    int n;
    int64_t s, ans = 0;
    cin >> n >> s;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int S = 0; S < (1 << n); S++) {
        int64_t t = s;
        for (int i = 0; i < n; i++)
            if (S >> i & 1) t -= a[i] + 1;
        if (t < 0) continue;
        ans = (ans + ((__builtin_popcount(S) & 1) ? mod - 1 : 1) * binom(t + n - 1, n - 1)) % mod;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    inv[0] = 1;
    for (int i = 1; i < 50; i++) inv[i] = Inv(i);

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}