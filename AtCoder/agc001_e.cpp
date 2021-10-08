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

#define maxn 200005
#define maxc 4005
#define deltaC 2002
#define maxv 8005
#define mod 1000000007

typedef pair<int, int> pii;

pii a[maxn];

long long f[maxc][maxc];

long long fac[maxv], ifac[maxv];

inline long long C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

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
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxv; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxv - 1] = Pow(fac[maxv - 1], mod - 2);
    for (int i = maxv - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = {read<int>(), read<int>()};
    for (int i = 1; i <= n; i++) f[deltaC - a[i].first][deltaC - a[i].second]++;
    for (int i = 1; i < maxc; i++)
        for (int j = 1; j < maxc; j++)
            f[i][j] = (f[i][j] + f[i - 1][j] + f[i][j - 1]) % mod;
    long long answer = 0;
    for (int i = 1; i <= n; i++) answer = (answer + f[deltaC + a[i].first][deltaC + a[i].second]) % mod;
    for (int i = 1; i <= n; i++) answer = (answer + mod - C((a[i].first + a[i].second) * 2, a[i].first * 2)) % mod;
    cout << answer * Pow(2, mod - 2) % mod << endl;
    return 0;
}