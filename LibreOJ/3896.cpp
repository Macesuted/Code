/**
 * @file 3896.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#ifndef LOCAL
#define endl '\n'
#endif

#define maxn 1005
#define mod 998244353

string a[maxn];
int R[maxn][maxn], D[maxn][maxn];

void solve(void) {
    int n, m, c, f;
    cin >> n >> m >> c >> f;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = " " + a[i];
    memset(R, 0, sizeof(R)), memset(D, 0, sizeof(D));
    for (int i = 1; i <= n; i++)
        for (int j = m - 1; j; j--)
            if (a[i][j] == '0' && a[i][j + 1] == '0') R[i][j] = R[i][j + 1] + 1;
    for (int j = 1; j <= m; j++)
        for (int i = n - 1; i; i--)
            if (a[i][j] == '0' && a[i + 1][j] == '0') D[i][j] = D[i + 1][j] + 1;
    int64_t cntc = 0, cntf = 0;
    for (int j = 1; j < m; j++) {
        int64_t sum = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i][j] == '1') {
                sum = 0;
                continue;
            }
            if (i > 2 && a[i - 1][j] == '0') sum = (sum + R[i - 2][j]) % mod;
            cntc = (cntc + sum * R[i][j]) % mod, cntf = (cntf + sum * R[i][j] * D[i][j]) % mod;
        }
    }
    cout << cntc * c << ' ' << cntf * f << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef LOCAL
    freopen("plant.in", "r", stdin), freopen("plant.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "MEMORY: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1, id;
    cin >> _ >> id;
    while (_--) solve();

#ifdef LOCAL
    cerr << "TIME: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
