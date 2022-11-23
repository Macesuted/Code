/**
 * @file C22084.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 45
#define mod 1000000007

int Mod(int x) { return x >= mod ? x - mod : x; }
int Add(int &a, int b) { return a = Mod(a + b); }

int f[maxn * 2][maxn][maxn * 2];

void solve(void) {
    int n, m;
    cin >> n >> m;
    f[0][0][0] = 1;
    for (int i = 1; i < n + m; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= n + m; k++) {
                int v = f[i - 1][j][k];
                if (!v) continue;
                if (i > m) {
                    if (k != i) Add(f[i][j][k], v);
                    if (max(1, i - n + 1) <= j) Add(f[i][j][0], v);
                } else {
                    if (k != i) Add(f[i][i][k], v);
                    Add(f[i][i][0], v);
                    if (n > 1) {
                        if (k != i) Add(f[i][j][k ? k : i + n - 1], v);
                        if (max(1, i - n + 1) <= j) Add(f[i][j][0], v);
                    }
                }
            }
    int ans = 0;
    for (int i = 0; i <= m; i++) Add(ans, f[n + m - 1][i][0]);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("paint.in", "r", stdin), freopen("paint.out", "w", stdout);
#endif
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