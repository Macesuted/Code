/**
 * @file 9523.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 505
#define mod 1000000007

typedef tuple<int, int, int> tiii;

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int x[maxn], v[maxn], coef[maxn];
int64_t f[maxn];
vector<tiii> a;

void insert(int64_t a, int64_t b) {
    for (int i = maxn - 2; ~i; i--) f[i + 1] = (f[i + 1] + f[i] * a) % mod, f[i] = f[i] * b % mod;
    return;
}
void erase(int64_t a, int64_t b) {
    int64_t invb = inv(b);
    for (int i = 0; i < maxn - 1; i++) f[i] = f[i] * invb % mod, f[i + 1] = (f[i + 1] + mod - f[i] * a % mod) % mod;
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x[i], x[i] = -x[i];
    for (int i = 1; i <= m; i++) cin >> v[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a.emplace_back(x[i], v[j], j);
    sort(a.begin(), a.end(),
         [&](const tiii& a, const tiii& b) { return (int64_t)get<0>(a) * get<1>(b) < (int64_t)get<1>(a) * get<0>(b); });

    f[0] = qpow(n, m);
    int64_t ans = 0;
    for (auto [x, y, p] : a) {
        erase(coef[p], n - coef[p]);
        ans = (ans + f[m / 2] * x % mod * inv(y)) % mod;
        coef[p]++;
        insert(coef[p], n - coef[p]);
    }
    cout << ans * inv(qpow(n, m)) % mod << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}