/**
 * @file 1172-1006.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

namespace FastIO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Ir = Ibuf, *Il = Ibuf;
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
int read(void) {
    int x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
}  // namespace FastIO
using FastIO::read;

#define maxn 105

using tiii = tuple<int, int, int>;
using tlii = tuple<int64_t, int, int>;

const int way[4][2] = {{0, +1}, {0, -1}, {+1, 0}, {-1, 0}};

int a[maxn][maxn];
bool vis[maxn][maxn];

void solve(void) {
    int n = read(), m = read();

    vector<tiii> rec;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = read(), rec.emplace_back(a[i][j], i, j);
    sort(rec.begin(), rec.end(), greater<tiii>());

    auto floodfill = [&](auto& self, int x, int y) -> void {
        vis[x][y] = true;
        for (int t = 0; t < 4; t++) {
            int tx = x + way[t][0], ty = y + way[t][1];
            if (tx < 1 || tx > n || ty < 1 || ty > m || vis[tx][ty] || a[tx][ty] > a[x][y]) continue;
            self(self, tx, ty);
        }
        return;
    };

    vector<tiii> S;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) vis[i][j] = false;
    floodfill(floodfill, 1, 1), S.emplace_back(a[1][1], 1, 1);
    for (auto [v, x, y] : rec) {
        if (vis[x][y]) continue;
        floodfill(floodfill, x, y), S.emplace_back(v, x, y);
    }
    sort(S.begin(), S.end());

    auto calc = [&](int x1, int y1, int x2, int y2) -> int64_t {
        return ((int64_t)1 << 34) + 114 * abs(x1 - x2) + 5141 * abs(y1 - y2) + (int64_t)919810 * abs(a[x1][y1] - a[x2][y2]);
    };

    int64_t ans = 0;
    for (size_t t = 0; t + 1 < S.size(); t++) ans += calc(get<1>(S[t]), get<2>(S[t]), get<1>(S[t + 1]), get<2>(S[t + 1]));

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}
