/**
 * @file L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 20

int64_t a[maxn][maxn], b[maxn], Sl[1024], Sr[1024];

void solve(void) {
    int n, m;
    int64_t s;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];
    cin >> s;
    int tm = m / 2, om = m - tm;
    for (int S = 0; S < (1 << n); S++) {
        for (int j = 0; j < m; j++) b[j] = 0;
        for (int j = 0; j < (1 << tm); j++) Sl[j] = 0;
        for (int j = 0; j < (1 << om); j++) Sr[j] = 0;
        for (int i = 0; i < n; i++)
            if (S >> i & 1)
                for (int j = 0; j < m; j++) b[j] += a[i][j];
        for (int j = 0; j < tm; j++) Sl[1 << j] = b[j];
        for (int j = 0; j < om; j++) Sr[1 << j] = b[tm + j];
        unordered_map<int64_t, int> St;
        for (int T = 0; T < (1 << tm); T++) {
            if (T) {
                int lb = T & -T;
                Sl[T] = Sl[lb] + Sl[T ^ lb];
            }
            St[Sl[T]] = T;
        }
        for (int T = 0; T < (1 << om); T++) {
            if (T) {
                int lb = T & -T;
                Sr[T] = Sr[lb] + Sr[T ^ lb];
            }
            if (St.count(s - Sr[T])) {
                int64_t rT = St[s - Sr[T]] | (T << tm);
                cout << "YES" << endl;
                vector<pair<int, int>> ans;
                for (int i = 0; i < n; i++)
                    if (!(S >> i & 1)) ans.emplace_back(1, i + 1);
                for (int j = 0; j < m; j++)
                    if (!(rT >> j & 1)) ans.emplace_back(2, j + 1);
                cout << ans.size() << endl;
                for (auto [x, y] : ans) cout << x << ' ' << y << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}