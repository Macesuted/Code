/**
 * @file 963E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxr 55
#define mod 1000000007

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int64_t f[maxr * 2][maxr * 2][maxr * 2], a[maxr * 2][maxr * 2];

void solve(void) {
    int R;
    int64_t a1, a2, a3, a4;
    cin >> R >> a1 >> a2 >> a3 >> a4;
    int64_t aa = Inv((a1 + a2 + a3 + a4) % mod);
    a1 = a1 * aa % mod, a2 = a2 * aa % mod, a3 = a3 * aa % mod, a4 = a4 * aa % mod;
    int64_t inva2 = Inv(a2);
    for (int x = -R; x <= +R; x++) f[x + maxr][int(sqrt(R * R - x * x)) + maxr][x + maxr] = 1;
    for (int y = +R; y >= -R; y--)
        for (int d = sqrt(R * R - y * y), x = -d; x <= +d; x++)
            for (int i = -R; i <= +R + 1; i++)
                f[x + maxr][y - 1 + maxr][i + maxr] =
                    (f[x + maxr][y + maxr][i + maxr] + (i == R + 1 ? mod - 1 : 0) + mod -
                     f[x - 1 + maxr][y + maxr][i + maxr] * a1 % mod + mod - f[x + 1 + maxr][y + maxr][i + maxr] * a3 % mod +
                     mod - f[x + maxr][y + 1 + maxr][i + maxr] * a4 % mod) *
                    inva2 % mod;
    for (int x = -R; x <= +R; x++)
        for (int y = -sqrt(R * R - x * x) - 1, i = -R; i <= +R + 1; i++)
            a[x + R][i + R] = f[x + maxr][y + maxr][i + maxr] * (i == R + 1 ? mod - 1 : 1) % mod;
    for (int i = 0; i <= 2 * R; i++) {
        int p = i;
        for (int j = i + 1; j <= 2 * R; j++)
            if (a[j][i]) p = j;
        for (int j = 0; j <= 2 * R + 1; j++) swap(a[i][j], a[p][j]);
        int64_t d = Inv(a[i][i]);
        for (int j = i; j <= 2 * R + 1; j++) a[i][j] = a[i][j] * d % mod;
        for (int j = 0; j <= 2 * R; j++) {
            if (i == j) continue;
            int64_t d = a[j][i];
            for (int k = i; k <= 2 * R + 1; k++) a[j][k] = (a[j][k] - a[i][k] * d % mod + mod) % mod;
        }
    }
    int64_t ans = f[maxr][maxr][R + 1 + maxr];
    for (int i = 0; i <= 2 * R; i++) ans = (ans + a[i][2 * R + 1] * f[maxr][maxr][i - R + maxr]) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
