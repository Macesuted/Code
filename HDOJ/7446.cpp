/**
 * @file 7446.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef tuple<int, int, int, int> tiiii;

int f[35][35][2000], id[50][50], X[30], Y[30], A[30], B[30], C[30];
bool vis[35][35][2000];
priority_queue<tiiii, vector<tiiii>, less<tiiii>> que;

void solve(void) {
    int n, m, q, d, sx, sy;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            id[i][j] = -1;
            for (int S = 0; S < (1 << q); S++) f[i][j][S] = -1e9, vis[i][j][S] = false;
        }
    cin >> d;
    for (int i = 0; i < q; i++) cin >> X[i] >> Y[i] >> A[i] >> B[i] >> C[i], id[X[i]][Y[i]] = i;
    cin >> sx >> sy;

    auto waste = [&](int x, int y, int S) {
        int sum = 0;
        for (int i = 0; i < q; i++)
            if (!(S >> i & 1) && abs(x - X[i]) + abs(y - Y[i]) <= C[i]) sum += B[i];
        return sum;
    };

    que.emplace(f[sx][sy][0] = 0, sx, sy, 0);
    while (!que.empty()) {
        auto [val, x, y, S] = que.top();
        que.pop();
        if (vis[x][y][S]) continue;
        vis[x][y][S] = true;
        for (int tx = x - 1, T = S; tx >= max(1, x - d); tx--) {
            int ty = y;
            if (id[tx][ty] >= 0 && !(T >> id[tx][ty] & 1))
                T |= 1 << id[tx][ty];
            else {
                int v = val - waste(tx, ty, T);
                if (f[tx][ty][T] < v) que.emplace(f[tx][ty][T] = v, tx, ty, T);
            }
        }
        for (int tx = x + 1, T = S; tx <= min(n, x + d); tx++) {
            int ty = y;
            if (id[tx][ty] >= 0 && !(T >> id[tx][ty] & 1))
                T |= 1 << id[tx][ty];
            else {
                int v = val - waste(tx, ty, T);
                if (f[tx][ty][T] < v) que.emplace(f[tx][ty][T] = v, tx, ty, T);
            }
        }
        for (int ty = y - 1, T = S; ty >= max(1, y - d); ty--) {
            int tx = x;
            if (id[tx][ty] >= 0 && !(T >> id[tx][ty] & 1))
                T |= 1 << id[tx][ty];
            else {
                int v = val - waste(tx, ty, T);
                if (f[tx][ty][T] < v) que.emplace(f[tx][ty][T] = v, tx, ty, T);
            }
        }
        for (int ty = y + 1, T = S; ty <= min(m, y + d); ty++) {
            int tx = x;
            if (id[tx][ty] >= 0 && !(T >> id[tx][ty] & 1))
                T |= 1 << id[tx][ty];
            else {
                int v = val - waste(tx, ty, T);
                if (f[tx][ty][T] < v) que.emplace(f[tx][ty][T] = v, tx, ty, T);
            }
        }
    }
    int ans = 0;
    for (int S = 0; S < (1 << q); S++) {
        int delt = 0;
        for (int i = 0; i < q; i++)
            if (S >> i & 1) delt += A[i];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) ans = max(ans, f[i][j][S] + delt);
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}