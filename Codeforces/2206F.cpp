/**
 * @file 2206F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
constexpr int N = 2097152, mod = 998244353, G = 3;

constexpr int inv(int x, int k = mod - 2) {
    int r = 1;
    for (; k; k >>= 1, x = x * (LL)x % mod)
        if (k & 1) r = x * (LL)r % mod;
    return r;
}
int rev[N], rt[N], lim, last;
void preNTT(int n) {
    lim = 1;
    while (lim < n) lim <<= 1;
    if (lim == last) return;
    last = lim;
    for (int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1 ? lim >> 1 : 0);
    for (int k = 2; k <= lim; k <<= 1) {
        rt[k >> 1] = 1;
        LL v = inv(G, (mod - 1) / k);
        for (int i = k / 2 + 1; i < k; ++i) rt[i] = rt[i - 1] * v % mod;
    }
}
void NTT(int *f, bool ty = true) {
    if (!ty) reverse(f + 1, f + lim);
    for (int i = 0; i < lim; ++i)
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int k = 1; k < lim; k <<= 1)
        for (int i = 0; i < lim; i += k << 1)
            for (int j = i, *bf = rt + k, x; j < (i | k); ++j, ++bf) {
                x = f[j | k] * (LL)*bf % mod;
                if ((f[j | k] = f[j] - x) < 0) f[j | k] += mod;
                if ((f[j] += x) >= mod) f[j] -= mod;
            }
    if (ty) return;
    LL v = mod - (mod - 1) / lim;
    for (int i = 0; i < lim; ++i) f[i] = f[i] * v % mod;
}
vector<int> operator*(const vector<int> &a, const vector<int> &b) {
    if (a.empty() || b.empty()) return vector<int>();
    static int tf[N], tg[N];
    int n = a.size(), m = b.size();
    preNTT(n + m - 1);
    memcpy(tf, a.data(), n << 2), memset(tf + n, 0, (lim - n) << 2), NTT(tf);
    memcpy(tg, b.data(), m << 2), memset(tg + m, 0, (lim - m) << 2), NTT(tg);
    for (int i = 0; i < lim; ++i) tf[i] = tf[i] * (LL)tg[i] % mod;
    NTT(tf, false);
    return vector<int>(tf, tf + n + m - 1);
}

void solve(void) {
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) A[i] = s[i] - '0', B[n - 1 - i] = (s[i] == '0');

    vector<int> C = A * B;

    vector<int64_t> F(n + 1);

    for (int i = 1; i < n; i++) F[i] = C[n - 1 + i] + C[n - 1 - i];

    int64_t base = 0;

    vector<vector<int>> chld(n + 1);

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) chld[j].push_back(i);

    for (int i = 1; i < n; i++) {
        if (A[i]) continue;
        base += A[i - 1];
        for (auto j : chld[i]) F[j] -= A[i - 1];
    }

    for (int i = 0; i < n - 1; i++) {
        if (A[i]) continue;
        base += A[i + 1];
        for (auto j : chld[i + 1]) F[j] -= A[i + 1];
    }

    sort(F.begin(), F.end(), greater<int64_t>());

    cout << F[k - 1] + base << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}