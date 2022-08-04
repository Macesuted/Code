/**
 * @file 3783.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-08
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

#define maxn 35

typedef pair<int, int> pii;

const int way[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};

string a[maxn];
double f[6][243][maxn][maxn], g[243][5], sum[32], p[32];
bool vis[maxn][maxn];
int pow3[6];

void solve(void) {
    int n, m, k, H;
    cin >> n >> m >> k >> H;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = " " + a[i];
    double sum = 0;
    for (int i = 0; i < (1 << k); i++) cin >> p[i], sum += p[i];
    for (int i = 0; i < (1 << k); i++) p[i] /= sum;
    pow3[0] = 1;
    for (int i = 1; i <= k; i++) pow3[i] = pow3[i - 1] * 3;
    for (int i = 0; i < pow3[k]; i++)
        for (int j = 0; j < k; j++) {
            if (i / pow3[j] % 3) continue;
            double sum[2] = {0, 0};
            for (int x = 0; x < (1 << k); x++) {
                bool check = true;
                for (int t = 0; t < k && check; t++)
                    if (i / pow3[t] % 3 && (x >> t & 1) != i / pow3[t] % 3 - 1) check = false;
                if (check) sum[x >> j & 1] += p[x];
            }
            g[i][j] = sum[1] / (sum[0] + sum[1]);
        }
    for (int h = 1; h <= H; h++)
        for (int S = pow3[k] - 1; ~S; S--) {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) vis[i][j] = false, f[h][S][i][j] = 0;
            for (int px = 1; px <= n; px++)
                for (int py = 1; py <= m; py++) {
                    int tc = a[px][py] - 'A';
                    if (vis[px][py] || a[px][py] == '#' ||
                        ('A' <= a[px][py] && a[px][py] <= 'Z' && S / pow3[tc] % 3 != 1))
                        continue;
                    static queue<pii> que;
                    static vector<pii> cache;
                    while (!que.empty()) que.pop();
                    cache.clear(), que.emplace(px, py), vis[px][py] = true;
                    double ans = (a[px][py] == '@' ? 1 : 0);
                    while (!que.empty()) {
                        int x, y;
                        tie(x, y) = que.front(), que.pop(), cache.emplace_back(x, y);
                        for (int t = 0; t < 4; t++) {
                            int tx = x + way[0][t], ty = y + way[1][t];
                            if (tx < 1 || tx > n || ty < 1 || ty > m || a[tx][ty] == '#') continue;
                            int tc = a[tx][ty] - 'A';
                            if (a[tx][ty] == '@') {
                                ans = 1;
                                continue;
                            }
                            if (a[tx][ty] < 'A' || a[tx][ty] > 'Z' || S / pow3[tc] % 3 == 1) {
                                if (!vis[tx][ty]) que.emplace(tx, ty), vis[tx][ty] = true;
                                continue;
                            }
                            if (S / pow3[tc] % 3 == 2) ans = max(ans, f[h - 1][S][tx][ty]);
                            if (S / pow3[tc] % 3 == 0)
                                ans = max(ans, g[S][tc] * f[h - 1][S + 2 * pow3[tc]][tx][ty] +
                                                   (1 - g[S][tc]) * f[h][S + pow3[tc]][tx][ty]);
                        }
                    }
                    for (auto i : cache) f[h][S][i.first][i.second] = ans;
                }
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) {
                    if (a[i][j] < 'A' || a[i][j] > 'Z' || S / pow3[a[i][j] - 'A'] % 3 != 2) continue;
                    for (int t = 0; t < 4; t++) {
                        int tx = i + way[0][t], ty = j + way[1][t];
                        if (tx < 1 || tx > n || ty < 1 || ty > m || a[tx][ty] == '#') continue;
                        int tc = a[tx][ty] - 'A';
                        if (a[tx][ty] == '@') {
                            f[h][S][i][j] = 1;
                            break;
                        }
                        if (a[tx][ty] < 'A' || a[tx][ty] > 'Z' || S / pow3[tc] % 3 == 1) {
                            f[h][S][i][j] = max(f[h][S][i][j], f[h][S][tx][ty]);
                            continue;
                        }
                        if (S / pow3[tc] % 3 == 2) f[h][S][i][j] = max(f[h][S][i][j], f[h - 1][S][tx][ty]);
                        if (S / pow3[tc] % 3 == 0)
                            f[h][S][i][j] = max(f[h][S][i][j], g[S][tc] * f[h - 1][S + 2 * pow3[tc]][tx][ty] +
                                                                   (1 - g[S][tc]) * f[h][S + pow3[tc]][tx][ty]);
                    }
                }
        }
    int sx = 0, sy = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == '$') sx = i, sy = j;
    cout << fixed << setprecision(3) << f[H][0][sx][sy] << endl;
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