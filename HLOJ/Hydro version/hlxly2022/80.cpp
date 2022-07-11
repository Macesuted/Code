/**
 * @file 80.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 2500005
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

const int64_t inv3 = Inv(3);

int64_t a[5][maxn], b[maxn], rev[maxn], fac[maxn], ifac[maxn];

void DFT(int64_t a[], int len, int mode) {
    for (int i = 0; i < len; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < len; i <<= 1) {
        int64_t base = Pow(mode == 1 ? 3 : inv3, (mod - 1) / (i << 1));
        for (int j = 0; j < len; j += i << 1) {
            int64_t w = 1;
            for (int k = j; k < j + i; k++, w = w * base % mod)
                tie(a[k], a[k + i]) = make_pair((a[k] + w * a[k + i]) % mod, (a[k] + mod - w * a[k + i] % mod) % mod);
        }
    }
    if (mode == -1) {
        int64_t inv = Inv(len);
        for (int i = 0; i < len; i++) a[i] = a[i] * inv % mod;
    }
    return;
}

void solve(void) {
    int v[5], k, c[5];
    cin >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> k;
    if (v[0] + v[1] + v[2] + v[3] + v[4] != k) return cout << 0 << endl, void();
    c[0] = v[3] + v[4], c[1] = v[0] + v[4], c[2] = v[0] + v[1], c[3] = v[1] + v[2], c[4] = v[2] + v[3];
    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
    int ttlen = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; 2 * j <= c[i]; j++)
            a[i][j] = ((j & 1) ? mod - 1 : 1) * ifac[c[i] - 2 * j] % mod * ifac[j] % mod, ttlen++;
    int len = 1, lgLen = 0;
    while (len < ttlen) len <<= 1, lgLen++;
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lgLen - 1));
    for (int i = 0; i < 5; i++) DFT(a[i], len, +1);
    for (int i = 0; i < len; i++) b[i] = a[0][i] * a[1][i] % mod * a[2][i] % mod * a[3][i] % mod * a[4][i] % mod;
    DFT(b, len, -1);
    int64_t ans = 0;
    for (int i = 0; i < len && i <= k; i++)
        ans = (ans + fac[k] * fac[2 * k - 2 * i] % mod * ifac[k - i] % mod * b[i]) % mod;
    cout << ans * Inv(Pow(2, k)) % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}