/**
 * @file abc227_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 33

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

bool mem1;

int a[maxn][maxn];
bool choose[maxn][maxn];
long long f[maxn][maxn][maxn * 2];

priority_queue<piii, vector<piii>, less<piii>> que;

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            que.push({a[i][j], {i, j}});
        }
    long long ans = numeric_limits<long long>::max();
    while (!que.empty()) {
        pii p = que.top().second;
        que.pop();
        choose[p.first][p.second] = true;
        memset(f, 0x3f, sizeof(f));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (i == 1 && j == 1) {
                    f[i][j][choose[i][j]] = (int)choose[i][j] * a[i][j];
                    continue;
                }
                for (int k = choose[i][j]; k <= i + j; k++)
                    f[i][j][k] = min(f[i - 1][j][k - choose[i][j]], f[i][j - 1][k - choose[i][j]]) + (int)choose[i][j] * a[i][j];
            }
        ans = min(ans, f[n][m][k]);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
