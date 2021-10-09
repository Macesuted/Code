/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
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

#define maxn 5005

long long f[maxn], g[maxn], C[maxn][maxn], mod;

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    int n = read<int>();
    mod = read<int>();
    for (int i = 0; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 2; i <= n; i += 2) {
        for (int j = 0; j <= i / 2; j++)
            f[i] = (f[i] + C[i / 2][j] * C[i / 2][j]) % mod;
        f[i] = f[i] * C[i][i / 2] % mod;
    }
    for (int i = 2; i <= n; i += 2) {
        g[i] = f[i];
        for (int j = 2; j < i; j += 2) g[i] = (g[i] + mod - f[i - j] * g[j] % mod) % mod;
    }
    long long answer = Pow(4, n) * (n + 1) % mod;
    for (int i = 2; i <= n; i += 2)
        answer = (answer + mod - g[i] * Pow(4, n - i) % mod * (n - i + 1) % mod) % mod;
    cout << answer << endl;
    return 0;
}