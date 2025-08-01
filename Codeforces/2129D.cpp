/**
 * @file 2129D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 105
#define mod 998244353

int a[maxn];
vector<vector<int64_t>> f[maxn][maxn];
int64_t C[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto resiz = [&](vector<vector<int64_t>>& vec, size_t n, size_t m) -> void {
        if (vec.size() < n + 1) vec.resize(n + 1);
        if (vec[n].size() < m + 1) vec[n].resize(m + 1, 0);
        return;
    };
    auto upd = [&](int l, int r, int c, size_t& tl, size_t& tr) -> void {
        if (l == 1 && r == n) return;
        if (l == 1 && r != n) return tr++, void();
        if (l != 1 && r == n) return tl++, void();
        return (c - l <= r - c ? tl : tr)++, void();
    };

    auto Mod = [&](int64_t x) -> int64_t { return x >= mod ? x - mod : x; };
    auto Add = [&](int64_t& a, int64_t x) -> void { return a = Mod(a + x), void(); };

    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) continue;
        if (i == 1)
            resiz(f[i][i], 0, 1), f[i][i][0][1] = 1;
        else
            resiz(f[i][i], 1, 1), f[i][i][1][0] = 1;
    }

    for (int len = 2; len <= n; len++)
        for (int l = 1, r = len; r <= n; l++, r++) {
            // i == l
            for (size_t xc = (~a[l] ? a[l] : 0); xc < min(f[l + 1][r].size(), size_t(~a[l] ? a[l] : n) + 1); xc++)
                for (size_t xr = 0; xr < f[l + 1][r][xc].size(); xr++) {
                    size_t tl = 0, tr = xr;
                    upd(l, r, l, tl, tr);
                    resiz(f[l][r], tl, tr), Add(f[l][r][tl][tr], f[l + 1][r][xc][xr]);
                }

            for (int i = l + 1; i < r; i++) {
                for (size_t xl = 0; xl < f[l][i - 1].size(); xl++)
                    for (size_t xcl = 0; xcl < min(f[l][i - 1][xl].size(), size_t(~a[i] ? a[i] : n) + 1); xcl++)
                        for (size_t xcr = (~a[i] ? a[i] - xcl : 0);
                             xcr < min(f[i + 1][r].size(), size_t(~a[i] ? a[i] - xcl : n) + 1); xcr++) {
                            for (size_t xr = 0; xr < f[i + 1][r][xcr].size(); xr++) {
                                size_t tl = xl, tr = xr;
                                upd(l, r, i, tl, tr);
                                resiz(f[l][r], tl, tr);
                                Add(f[l][r][tl][tr], f[l][i - 1][xl][xcl] * f[i + 1][r][xcr][xr] % mod * C[r - l][i - l] % mod);
                            }
                        }
            }

            // i == r
            for (size_t xl = 0; xl < f[l][r - 1].size(); xl++)
                for (size_t xr = (~a[r] ? a[r] : 0); xr < min(f[l][r - 1][xl].size(), size_t(~a[r] ? a[r] : n) + 1); xr++) {
                    size_t tl = xl, tr = 0;
                    upd(l, r, r, tl, tr);
                    resiz(f[l][r], tl, tr), Add(f[l][r][tl][tr], f[l][r - 1][xl][xr]);
                }
        }

    resiz(f[1][n], 0, 0), cout << f[1][n][0][0] << endl;

    for (int l = 1; l <= n; l++)
        for (int r = l; r <= n; r++) f[l][r].clear();

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}