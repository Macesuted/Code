/**
 * @file 10485.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 505

int64_t a[maxn], sum[maxn], g[maxn][maxn], h[maxn];
bitset<maxn> f[maxn][maxn];

void solve(void) {
    int n, mod, c;
    cin >> n >> mod >> c;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i], a[i] %= mod;

    auto Mod = [&](int x) -> int { return x >= mod ? x - mod : x; };

    for (int l = n; l >= 1; l--) {
        f[l][l - 1][0] = true;

        for (int r = l; r <= n; r++) {
            f[l][r] = f[l][r - 1];
            for (int x = l; x < r; x++)
                if (g[x + 1][r] != -1) f[l][r] |= f[l][x] << g[x + 1][r];

            g[l][r] = -1;
            int64_t s = (sum[r] - sum[l - 1]) % mod;
            for (int v = 0; v <= n; v++, s = Mod(s + mod - c))
                if (f[l][r][v] && s == c) {
                    g[l][r] = v + 1;
                    break;
                }
        }
    }

    h[0] = 0;
    for (int r = 1; r <= n; r++) {
        h[r] = max(h[r], h[r - 1]);
        for (int l = r; l >= 1; l--)
            if (g[l][r] != -1) h[r] = max(h[r], h[l - 1] + (sum[r] - sum[l - 1] - g[l][r] * c) / mod);
    }

    cout << h[n] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
