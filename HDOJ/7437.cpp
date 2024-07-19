/**
 * @file 7437.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 998244353
#define maxn 10000005

typedef pair<int, int> pii;

pii a[30];
int64_t fac[maxn], ifac[maxn], inv2;

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
    int n, tot = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c >> a[i].second, a[i].first = c - 'a', tot += a[i].second;
    }
    sort(a + 1, a + n + 1);

    auto f = [&](void) {
        bool chk = true;
        int sum = 0;
        for (int i = 1; i <= n; i++) chk &= (a[i].second % 2 == 0), sum += a[i].second;
        if (!chk) return inv2;
        int64_t ans = fac[sum];
        for (int i = 1; i <= n; i++) ans = ans * ifac[a[i].second] % mod;
        ans = inv(ans) * fac[sum / 2] % mod;
        for (int i = 1; i <= n; i++) ans = ans * ifac[a[i].second / 2] % mod;
        return (mod + 1 - ans) * inv2 % mod;
    };

    if (!(tot & 1)) return cout << f() << endl, void();
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        a[i].second--;
        ans = (ans + (mod + 1 - f()) * (a[i].second + 1)) % mod;
        a[i].second++;
    }
    ans = ans * inv(tot) % mod;
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    inv2 = inv(2);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}