/**
 * @file 12970.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef pair<int, int> pii;

int f[2][1 << 16][17][17];
pii a[17 * 17];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1, x; i <= n; i++) cin >> x, f[1][x][0][0]++;
    for (int i = 0; i < 16; i++) {
        bool t = i & 1;
        for (int j = 0; j < (1 << 16); j++)
            for (int k = 0; k <= i; k++)
                for (int l = 0; l <= i; l++)
                    if (f[!t][j][k][l]) {
                        int b = j >> i & 1, j_ = j ^ (b << i);
                        if (b)
                            f[t][j_ | (1 << i)][k + 1][l + 1] += f[!t][j][k][l], f[t][j_][k][l + 1] += f[!t][j][k][l];
                        else
                            f[t][j_ | (1 << i)][k][l + 1] += f[!t][j][k][l], f[t][j_][k][l] += f[!t][j][k][l];
                        f[!t][j][k][l] = 0;
                    }
    }
    while (q--) {
        int A, B, C, k, x;
        cin >> A >> B >> C >> k >> x;
        for (int i = 0; i <= 16; i++)
            for (int j = 0; j <= 16; j++) a[i * 17 + j] = {i * A + j * B + (j - i) * C, f[1][x][i][j]};
        sort(a, a + 17 * 17);
        for (int i = 0; i < 17 * 17; k -= a[i++].second)
            if (a[i].second >= k) {
                cout << a[i].first << endl;
                break;
            }
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("bit.in", "r", stdin), freopen("bit.out", "w", stdout);
#endif
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
