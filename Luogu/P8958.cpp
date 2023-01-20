/**
 * @file P8958.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005
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

const int inv3 = Inv(3);

int64_t fac[maxn], ifac[maxn], A[maxn << 2], B[maxn << 2];
int rev[maxn << 2];

int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int64_t catalan(int n) { return (binom(n, n / 2) + mod - binom(n, n / 2 - 1)) % mod; }

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
        int64_t invLen = Inv(len);
        for (int i = 0; i < len; i++) a[i] = a[i] * invLen % mod;
    }
    return;
}

void solve(void) {
    int n;
    cin >> n, n <<= 1;
    for (int i = 1; i <= n; i++) cin >> A[i], B[n - i] = A[i];
    int len = 1, lgLen = 0;
    while (len <= 2 * n) len <<= 1, lgLen++;
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lgLen - 1));
    DFT(A, len, +1), DFT(B, len, +1);
    for (int i = 0; i < len; i++) A[i] = A[i] * B[i] % mod;
    DFT(A, len, -1);
    int64_t ans = 0;
    for (int i = n + 1; i <= 2 * n - 1; i += 2) {
        int c = i - n - 1;
        ans = (ans + A[i] * catalan(c) % mod * catalan(n - 2 - c)) % mod;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}