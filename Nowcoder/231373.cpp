#include <bits/stdc++.h>
using namespace std;

#define mod 998244353
#define maxv 10000005

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

long long fac[maxv], ifac[maxv], inv[maxv];

inline long long binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
inline long long BINOM(long long n, int m) {
    long long ans = 1;
    for (long long i = n; i > n - m; i--) ans = ans * (i % mod) % mod;
    for (int i = m; i; i--) ans = ans * inv[i] % mod;
    return ans;
}

void solve(void) {
    int p, K;
    cin >> p >> K;
    cout << ((BINOM(1LL * p * K, p) - K + mod) % mod * Pow(p, mod - 2) + K) % mod << endl;
    return;
}

int main() {
    fac[0] = ifac[0] = inv[0] = 1;
    for (int i = 1; i < maxv; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxv - 1] = Pow(fac[maxv - 1], mod - 2);
    for (int i = maxv - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxv; i++) inv[i] = ifac[i] * fac[i - 1] % mod;
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}