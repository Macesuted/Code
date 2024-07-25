/**
 * @file 102428H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

double f[100][100][100];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for (int i = 0; i < 75; i++) f[75][i][0] = 1;

    auto sum = [&](int i, int j, int k) {
        double tot = 0;
        for (int t = 2; t <= 6; t++) {
            if (i + k + t <= 75)
                tot += f[i][j][k + t];
            else
                tot += 1 - f[j][i][0];
        }
        return tot;
    };

    for (int s = 148; ~s; s--)
        for (int i = 74; ~i; i--) {
            int j = s - i;
            if (j < 0 || j > 74 || i > j) continue;

            double l = 0, r = 1;
            while (l + 1e-8 < r) {
                double m = (l + r) / 2;
                f[i][j][0] = m;

                for (int k = 75 - j; k >= 2; k--) f[j][i][k] = max(1 - f[i][j + k][0], (1 - f[i][j][0] + sum(j, i, k)) / 6);
                f[j][i][0] = (1 - f[i][j][0] + sum(j, i, 0)) / 6;

                if (i != j) {
                    for (int k = 75 - i; k >= 2; k--) f[i][j][k] = max(1 - f[j][i + k][0], (1 - f[j][i][0] + sum(i, j, k)) / 6);
                    f[i][j][0] = (1 - f[j][i][0] + sum(i, j, 0)) / 6;
                }

                (f[i][j][0] < m ? r : l) = m;
            }
        }

    int q;
    cin >> q;
    while (q--) {
        int i, j, k;
        cin >> i >> j >> k;
        double v1 = 1 - f[j][i + k][0], v2 = (1 - f[j][i][0] + sum(i, j, k)) / 6;
        cout << "CH"[v1 > v2] << endl;
    }

    return 0;
}