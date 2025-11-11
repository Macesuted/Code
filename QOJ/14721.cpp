/**
 * @file 14721.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

using pii = pair<int, int>;

int a[maxn][maxn];
bool vis[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    bool rev = false;
    if (n % 3) swap(n, m), rev = true;

    auto print = [&](void) -> void {
        cout << "Yes" << endl;

        if (rev)
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) cout << a[j][i];
                cout << endl;
            }
        else
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) cout << a[i][j];
                cout << endl;
            }

        return;
    };

    if (m <= 2) {
        if (n >= 9) return cout << "No" << endl, void();
        int b = n / 3;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) a[i][j] = (i - 1) / b;
        return print();
    }

    if (m == 3) {
        for (int i = 1; i <= n; i += 3)
            if (i % 6 == 1) {
                a[i + 0][1] = 2, a[i + 0][2] = 1, a[i + 0][3] = 0;
                a[i + 1][1] = 2, a[i + 1][2] = 0, a[i + 1][3] = 1;
                a[i + 2][1] = 0, a[i + 2][2] = 2, a[i + 2][3] = 1;
            } else {
                a[i + 0][1] = 0, a[i + 0][2] = 1, a[i + 0][3] = 2;
                a[i + 1][1] = 1, a[i + 1][2] = 0, a[i + 1][3] = 2;
                a[i + 2][1] = 1, a[i + 2][2] = 2, a[i + 2][3] = 0;
            }
        return print();
    }

    if (m == 4) {
        for (int i = 1; i <= n; i += 3)
            if (i % 6 == 1) {
                a[i + 0][1] = 1, a[i + 0][2] = 0, a[i + 0][3] = 0, a[i + 0][4] = 2;
                a[i + 1][1] = 1, a[i + 1][2] = 1, a[i + 1][3] = 2, a[i + 1][4] = 0;
                a[i + 2][1] = 2, a[i + 2][2] = 2, a[i + 2][3] = 1, a[i + 2][4] = 0;
            } else {
                a[i + 0][1] = 2, a[i + 0][2] = 0, a[i + 0][3] = 0, a[i + 0][4] = 1;
                a[i + 1][1] = 0, a[i + 1][2] = 2, a[i + 1][3] = 1, a[i + 1][4] = 1;
                a[i + 2][1] = 0, a[i + 2][2] = 1, a[i + 2][3] = 2, a[i + 2][4] = 2;
            }
        return print();
    }

    for (int i = 1; i <= n; i += 3)
        for (int j = 1; j <= m; j += 3)
            if ((i % 6 == 1) ^ (j % 6 == 1)) {
                a[i + 0][j + 0] = 0, a[i + 0][j + 1] = 1, a[i + 0][j + 2] = 1;
                a[i + 1][j + 0] = 1, a[i + 1][j + 1] = 0, a[i + 1][j + 2] = 2;
                a[i + 2][j + 0] = 2, a[i + 2][j + 1] = 2, a[i + 2][j + 2] = 0;
            } else {
                a[i + 0][j + 0] = 2, a[i + 0][j + 1] = 2, a[i + 0][j + 2] = 0;
                a[i + 1][j + 0] = 1, a[i + 1][j + 1] = 0, a[i + 1][j + 2] = 2;
                a[i + 2][j + 0] = 0, a[i + 2][j + 1] = 1, a[i + 2][j + 2] = 1;
            }
    return print();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
