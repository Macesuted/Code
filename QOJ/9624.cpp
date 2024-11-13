/**
 * @file 9624.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 505
#define mod 998244353

string a;
int64_t C[maxn][maxn], f[maxn][maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n;
    cin >> n >> a, a = ' ' + a;

    f[0][0] = 1;
    for (int l = 1; l <= n; l++)
        for (int r = l, cnt[2] = {0, 0}; r <= n; r++) {
            if (a[r] == 'R' && cnt[0]) break;
            cnt[a[r] == 'R']++;

            int64_t coef = 0;

            if (cnt[0] && cnt[1])
                coef = (coef + (C[r - l - 1][cnt[0] - 1] + C[r - l - 1][cnt[1] - 1]) * (r - l)) % mod;
            else if ((cnt[0] && l == 1) || (cnt[1] && r == n))
                coef = Mod(coef + 1);
            if (cnt[0] >= 2) coef = (coef + C[r - l - 1][cnt[0] - 2] * (r - l)) % mod;
            if (cnt[1] >= 2) coef = (coef + C[r - l - 1][cnt[1] - 2] * (r - l)) % mod;

            if (coef == 0) continue;

            for (int k = 1; k <= r; k++) f[r][k] = (f[r][k] + f[l - 1][k - 1] * coef % mod * C[r][l - 1]) % mod;
        }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) cerr << f[i][j] << ' ';
        cerr << endl;
    }

    for (int i = 1; i <= n; i++) cout << f[n][i] << ' ';
    cout << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = Mod(C[i - 1][j - 1] + C[i - 1][j]);
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}