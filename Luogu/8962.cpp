/**
 * @file 8962.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 405

int64_t fac[maxn], C[maxn][maxn];
int lef[maxn], rig[maxn];

void solve(int l, int r, int le = 0, int ri = 0) {
    if (l > r) return;
    int mid = (l + r) / 2;
    lef[mid] = le, rig[mid] = ri;
    return solve(l, mid - 1, le, ri + 1), solve(mid + 1, r, le + 1, ri);
}

void solve(void) {
    int mod, n;
    cin >> mod >> n;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    for (int i = 0; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 1; i <= n; i++) {
        solve(1, i);
        for (int j = 1; j <= i; j++) {
            int64_t ans = 0;
            for (int k = 1; k <= i; k++)
                if (lef[k] <= j - 1 && rig[k] <= i - j)
                    ans = (ans + C[j - 1][lef[k]] * fac[lef[k]] % mod * C[i - j][rig[k]] % mod * fac[rig[k]] % mod *
                                     fac[i - 1 - lef[k] - rig[k]]) %
                          mod;
            cout << ans << ' ';
        }
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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