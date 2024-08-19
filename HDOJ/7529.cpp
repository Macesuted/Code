/**
 * @file 7529.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005
#define mod 998244353

vector<int> graph[maxn];
bool g[maxn];
int64_t f[maxn], fac[maxn], ifac[maxn], pow2[maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t x) { return qpow(x, mod - 2); }
int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void dfs(int p) {
    if (graph[p].empty()) return f[p] = 1, g[p] = true, void();
    f[p] = 1, g[p] = false;
    int cnt[2] = {0, 1};
    for (auto i : graph[p]) dfs(i), f[p] = f[p] * f[i] % mod, cnt[g[i]]++;
    if (cnt[1] & 1) {
        g[p] = true;
        if (--cnt[1]) f[p] = f[p] * (C(cnt[1], cnt[1] / 2) + C(cnt[1], cnt[1] / 2 - 1)) % mod;
    } else
        f[p] = f[p] * C(cnt[1], cnt[1] >> 1) % mod;
    return;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) graph[i].clear();
    for (int i = 2, x; i <= n; i++) cin >> x, graph[x].push_back(i);
    dfs(1);
    if (g[1]) f[1] = f[1] * 2 % mod;
    cout << qpow(f[1], k) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    fac[0] = ifac[0] = pow2[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod, pow2[i] = pow2[i - 1] * 2 % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}