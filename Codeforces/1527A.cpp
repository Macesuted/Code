/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define maxn 10000005

long long power(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

// long long fac[maxn], inv[maxn];
// void INIT(void) {
//     fac[1] = 1;
//     for (register int i = 2; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
//     inv[maxn - 1] = power(fac[maxn - 1], mod - 2);
//     for (register int i = maxn - 2; i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
//     return;
// }
// long long C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }

void work(void) {
    int n;
    cin >> n;
    int t = 1;
    while ((t << 1) <= n) t <<= 1;
    cout << t - 1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
} // awa