/**
 * @file B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 5005
#define mod 1000000007

bool mem1;

int cnt[maxn];
int f[3][maxn][maxn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

bool mem2;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, cnt[x]++;
    f[1][0][0] = 1;
    for (int i = 1; i <= m; i++) {
        int p = i % 3, q = (i + 1) % 3;
        for (int j = 0; j <= cnt[i + 1]; j++)
            for (int k = 0; k <= cnt[i + 2]; k++) f[q][j][k] = 0;
        for (int j = 0; j <= cnt[i]; j++)
            for (int k = 0; k <= cnt[i + 1]; k++)
                if (f[p][j][k]) {
                    int vl = (cnt[i] - j) % 3, vr = min({cnt[i] - j, cnt[i + 1] - k, cnt[i + 2]});
                    while ((cnt[i] - j - vr) % 3) vr--;
                    if (vl > vr) continue;
                    f[q][k + vl][vl] = Mod(f[q][k + vl][vl] + f[p][j][k]);
                    f[q][k + vr + 3][vr + 3] = Mod(f[q][k + vr + 1][vr + 1] + mod - f[p][j][k]);
                }
        for (int j = 0; j <= cnt[i + 1]; j++)
            for (int k = 0; k <= cnt[i + 2]; k++) f[q][j + 3][k + 3] = Mod(f[q][j + 3][k + 3] + f[q][j][k]);
    }
    cout << f[(m + 1) % 3][0][0] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}