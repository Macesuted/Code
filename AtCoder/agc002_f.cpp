/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Solution: https://macesuted.moe/article/agc002f
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar())
        x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 2005
#define maxv 4000005
#define mod 1000000007

long long f[maxn][maxn], fac[maxv], ifac[maxv];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

inline long long C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int main() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxv; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxv - 1] = Pow(fac[maxv - 1], mod - 2);
    for (int i = maxv - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    ios::sync_with_stdio(false);
    int n = read<int>(), k = read<int>();
    if (k == 1) {
        cout << 1 << endl;
        return 0;
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][0];
        for (int j = 1; j <= i; j++)
            f[i][j] = (f[i - 1][j] + f[i][j - 1] * (n - j + 1) % mod * C(n * k - i - (j - 1) * (k - 1) - 1, k - 2)) % mod;
    }
    cout << f[n][n] << endl;
    return 0;
}