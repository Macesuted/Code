/**
 * @file abc360_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
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

#define mod 998244353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

void solve(void) {
    int n, k;
    cin >> n >> k;
    int64_t ans = 1, sum = (int64_t)n * (n + 1) % mod * inv(2) % mod;
    while (k--) {
        int64_t down = inv((int64_t)n * n % mod);
        ans = (((int64_t)(n - 1) * (n - 1) % mod + 1) * down % mod * ans + down * (sum + mod - ans) * 2) % mod;
    }
    cout << ans << endl;
    return;
}
/*

total = n*n
same = n
no = (n - 1) * (n - 1)

*/

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