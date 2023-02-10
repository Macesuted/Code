/**
 * @file 118.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-10
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

#define maxn 10000005
#define mod 1000000007

int64_t fac2[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = 0;
    for (int v = 4 * n - 1; int64_t(v - 1) * n + 1 >= int64_t(2 * n + 1) * n; v--) {
        int c = 2 * n - v / 2;
        ans = (ans + Pow(v - 2 * n - 1, c - 1) * c % mod * (n == c ? 1 : fac2[2 * n - 2 * c - 1])) % mod;
    }
    cout << ans * fac2[n] % mod * fac2[n - 1] % mod * Inv(fac2[2 * n] * fac2[2 * n - 1] % mod) % mod * Pow(2, n) % mod << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("card.in", "r", stdin), freopen("card.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac2[0] = fac2[1] = 1;
    for (int i = 2; i < maxn; i++) fac2[i] = fac2[i - 2] * i % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}