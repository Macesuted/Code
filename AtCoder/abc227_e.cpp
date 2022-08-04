/**
 * @file abc227_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool mem1;

#define maxn 33

int a[maxn];
long long f[maxn][maxn][maxn][maxn * maxn];

void solve(void) {
    string s;
    cin >> s;
    s = ' ' + s;
    int n = s.size() - 1;
    for (int i = 1; i <= n; i++) a[i] = (s[i] == 'K' ? 1 : (s[i] == 'E' ? 2 : 3));
    int k;
    cin >> k;
    int cnt[4] = {0, 0, 0, 0};
    for (int i = 1; i <= n; i++) cnt[a[i]]++;
    f[0][0][0][0] = 1;
    for (int i = 0; i <= cnt[1]; i++)
        for (int j = 0; j <= cnt[2]; j++)
            for (int k = 0; k <= cnt[3]; k++) {
                int p[4] = {n, n + 1, n + 1, n + 1};
                int rest[4] = {0, i, j, k};
                for (int x = 1, cnt = 0; x <= n; x++)
                    if (rest[a[x]])
                        rest[a[x]]--;
                    else
                        p[a[x]] = min(p[a[x]], cnt++);
                if (p[1] != n + 1) {
                    for (int t = 0; t + p[1] <= n * n; t++) f[i + 1][j][k][t + p[1]] += f[i][j][k][t];
                }
                if (p[2] != n + 1) {
                    for (int t = 0; t + p[2] <= n * n; t++) f[i][j + 1][k][t + p[2]] += f[i][j][k][t];
                }
                if (p[3] != n + 1) {
                    for (int t = 0; t + p[3] <= n * n; t++) f[i][j][k + 1][t + p[3]] += f[i][j][k][t];
                }
            }
    long long ans = 0;
    for (int i = 0; i <= min(n * n, k); i++) ans += f[cnt[1]][cnt[2]][cnt[3]][i];
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
