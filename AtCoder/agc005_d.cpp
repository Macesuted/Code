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

#define maxn 2005
#define mod 924844033

long long f[maxn << 1][maxn << 1][2], fac[maxn];
bool beg[maxn << 1];

int main() {
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ios::sync_with_stdio(false);
    int n = read<int>(), k = read<int>(), tail = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n; j += k) beg[++tail] = (j == i);
        for (int j = i; j <= n; j += k) beg[++tail] = (j == i);
    }
    f[0][0][0] = 1;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 0; j <= i; j++) {
            f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % mod;
            if (!beg[i] && j) f[i][j][1] = f[i - 1][j - 1][0];
        }
    long long answer = 0;
    for (int i = 0, id = 1; i <= n; i++, id = -id)
        answer = (answer + mod + id * (f[2 * n][i][0] + f[2 * n][i][1]) * fac[n - i] % mod) % mod;
    cout << answer << endl;
    return 0;
}