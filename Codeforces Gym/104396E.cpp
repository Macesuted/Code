/**
 * @file 104396E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005
#define mod 1'000'000'007

using pii = pair<int, int>;

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int64_t fac[maxn], ifac[maxn], iv[maxn];

int64_t C(int n, int m) { return n < m ? 0 : fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int x, k;
    cin >> x >> k;

    vector<int> vals;
    for (int i = 1; i * i <= x; i++) {
        if (x % i) continue;
        vals.push_back(i);
        if (i * i < x) vals.push_back(x / i);
    }
    sort(vals.begin(), vals.end()), vals.pop_back();

    int64_t ans = 0;
    for (auto G : vals) {
        int L = x / G - 1;

        vector<int> rec;
        for (int i = 2; i * i <= L; i++) {
            if (L % i) continue;
            int cnt = 1;
            while (L % i == 0) L /= i, cnt++;
            rec.push_back(cnt);
        }
        if (L > 1) rec.push_back(2);

        int m = rec.size();

        for (int S = 0; S < (1 << m); S++)
            for (int T = 0; T < (1 << m); T++) {
                int prod = 1, coef = ((__builtin_popcount(S) ^ __builtin_popcount(T)) & 1) ? -1 : +1;
                for (int i = 0; i < m; i++) prod *= rec[i] - (S >> i & 1) - (T >> i & 1);
                ans = (ans + mod + coef * C(prod, k)) % mod;
            }
        cerr << L << " " << ans << endl;
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

    fac[0] = ifac[0] = iv[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxn; i++) iv[i] = ifac[i] * fac[i - 1] % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}