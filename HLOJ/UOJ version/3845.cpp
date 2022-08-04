/**
 * @file tower.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-02
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 256M
 *
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
T read(void) {
    char c = getchar();
    T f = +1, x = 0;
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar(x ^ 48), void();
    if (x > 9) write(x / 10);
    return putchar((x % 10) ^ 48), void();
}

bool mem1;

#define maxn 500005
#define maxsqrt3k 1000005
#define mod 998244353

long long a[maxn], f[maxsqrt3k], g[maxsqrt3k], p2[maxsqrt3k], p3[maxsqrt3k], p3k;

long long calc(long long a, long long K) {
    if (a <= 0) return numeric_limits<long long>::max();
    if (K / a / a >= a) return K / a / a;
    return upper_bound(p2, p2 + maxsqrt3k, K / a) - p2 - 1;
}
long long solve(long long A, long long B) {
    A = min({A, B, p3k});
    long long p = upper_bound(g + 1, g + A + 1, B, greater<long long>()) - g - 1;
    return ((p + 1) * B + f[A] + mod - f[p] + mod - A * (A + 1) / 2 % mod) % mod;
}

void solve(void) {
    int n = read<int>();
    long long K = read<long long>();
    p3k = upper_bound(p3, p3 + maxsqrt3k, K) - p3 - 1;
    for (int i = 1; i < maxsqrt3k; i++) g[i] = K / i / i;
    for (int i = 1; i < maxsqrt3k; i++) f[i] = (g[i] + f[i - 1]) % mod;
    a[0] = a[n + 1] = 0;
    for (int i = 1; i <= n; i++) a[i] = read<long long>();
    for (int i = 1; i <= n; i++)
        if (a[i - 1] <= 0 && a[i] == -1 && a[i + 1] <= 0) return write(-1), putchar('\n'), void();
    for (int i = 1; i < n; i++)
        if (a[i] > 0 && a[i + 1] > 0 && K / a[i] / a[i + 1] < min(a[i], a[i + 1]))
            return write(0), putchar('\n'), void();
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] != -1) continue;
        if (a[i - 1] != -1 && a[i + 1] != -1)
            ans = ans * (min(calc(a[i - 1], K), calc(a[i + 1], K)) + 1) % mod;
        else if (i < n && a[i - 1] != -1 && a[i + 1] == -1) {
            long long A = calc(a[i - 1], K), B = calc(a[i + 2], K);
            ans = ans * (solve(A, B) + solve(B, A) + min({A, B, p3k}) + 1) % mod;
        }
    }
    return write(ans), putchar('\n'), void();
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tower.in", "r", stdin), freopen("tower.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxsqrt3k; i++) p2[i] = 1LL * i * i, p3[i] = 1LL * i * i * i;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
}