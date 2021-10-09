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

#define maxv 200005
#define maxk 2005
#define mod 1000000007

typedef pair<int, int> pii;

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

long long f[maxk], fac[maxv], ifac[maxv];
pii a[maxk];

inline long long C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int main() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxv; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxv - 1] = Pow(fac[maxv - 1], mod - 2);
    for (int i = maxv - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    ios::sync_with_stdio(false);
    int n = read<int>(), m = read<int>(), k = read<int>();
    for (int i = 1; i <= k; i++) a[i] = {read<int>(), read<int>()};
    a[++k] = {n, m};
    sort(a + 1, a + k + 1);
    for (int i = 1; i <= k; i++) {
        f[i] = C(a[i].first - 1 + a[i].second - 1, a[i].first - 1);
        for (int j = 1; j < i; j++)
            if (a[j].second <= a[i].second)
                f[i] = (f[i] + mod -
                        f[j] * C(a[i].first - a[j].first + a[i].second - a[j].second, a[i].first - a[j].first) % mod) %
                       mod;
    }
    cout << f[k] << endl;
    return 0;
}