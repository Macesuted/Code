/**
 * @file 108306B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005
#define mod 998244353

const int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool mem1;

int64_t f[maxn][5][2][2][2][2], g[maxn][3][2][15], h[maxn][3][4][40];
int a[maxn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }
void Add(int64_t &x, int64_t y) { return x = Mod(x + y), void(); }

void solve() {
    int n;
    string s;
    cin >> n >> s;

    for (int i = 1; i <= n; i++) a[i] = s[i - 1] - '0';

    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));

    f[0][0][0][0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 4; j++)
            for (int Y10 = 0; Y10 < 2; Y10++)
                for (int Y1 = 0; Y1 < 2; Y1++)
                    for (int Y20 = 0; Y20 < 2; Y20++)
                        for (int Y2 = 0; Y2 < 2; Y2++) {
                            int64_t v = f[i - 1][j][Y10][Y1][Y20][Y2];

                            Add(f[i][j][Y10][Y1][Y20][Y2], v);

                            if (j == 0) Add(f[i][1][Y10 | (a[i] > 0)][a[i] & 1][0][0], v);
                            if (j == 1) Add(f[i][2][Y10 | (a[i] > 0)][(Y1 * 10 + a[i]) % 4 > 0][0][0], v);
                            if (j == 2) Add(f[i][3][Y10][Y1][Y20 | (a[i] > 0)][a[i] & 1], v);
                            if (j == 3) Add(f[i][4][Y10][Y1][Y20 | (a[i] > 0)][(Y2 * 10 + a[i]) % 4 > 0], v);
                        }

    for (int i = 1; i <= n; i++) {
        if (a[i] <= 1) {
            for (int Y10 = 0; Y10 < 2; Y10++)
                for (int Y1 = 0; Y1 < 2; Y1++)
                    for (int Y20 = 0; Y20 < 2; Y20++)
                        for (int Y2 = 0; Y2 < 2; Y2++) {
                            if (!Y10 && !Y20) continue;
                            int t = !Y2;
                            if (!Y20 && Y1) t = 0;
                            Add(g[i][1][t][a[i] * 10], f[i - 1][4][Y10][Y1][Y20][Y2]);
                        }
        }
        for (int j = 1; j <= 2; j++)
            for (int Y = 0; Y < 2; Y++)
                for (int M = 0; M <= 12; M++) {
                    int64_t v = g[i - 1][j][Y][M];

                    Add(g[i][j][Y][M], v);

                    if (j == 1 && 1 <= M + a[i] && M + a[i] <= 12) Add(g[i][2][Y][M + a[i]], v);
                }
    }

    auto getDay = [&](int Y, int M) -> int { return (M == 2 && Y ? 1 : 0) + day[M]; };

    for (int i = 1; i <= n; i++) {
        if (a[i] <= 3)
            for (int Y = 0; Y < 2; Y++)
                for (int M = 1; M <= 12; M++) Add(h[i][1][getDay(Y, M) - 28][a[i] * 10], g[i - 1][2][Y][M]);

        for (int j = 1; j <= 2; j++)
            for (int P = 0; P < 4; P++)
                for (int D = 0; D <= 31; D++) {
                    int64_t v = h[i - 1][j][P][D];

                    Add(h[i][j][P][D], v);

                    if (j == 1 && 1 <= D + a[i] && D + a[i] <= 28 + P) Add(h[i][2][P][D + a[i]], v);
                }
    }

    int64_t ans = 0;
    for (int P = 0; P < 4; P++)
        for (int i = 1; i <= 28 + P; i++) Add(ans, h[n][2][P][i]);

    cout << ans << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}