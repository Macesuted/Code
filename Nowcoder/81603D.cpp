/**
 * @file 81603D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int base[6][6][6] = {
    {},
    {{10, 0, 5, 0, 0, 2}, {0, 9, 0, 4, 0, 2}, {0, 5, 8, 0, 0, 2}, {4, 0, 4, 8, 0, 2}, {2, 0, 0, 0, 9, 4}},
    {{11, 0, 5, 0, 0, 2}, {0, 10, 0, 4, 0, 2}, {0, 5, 9, 0, 0, 2}, {4, 0, 4, 9, 0, 2}, {2, 0, 0, 0, 10, 4}},
    {{12, 0, 5, 0, 0, 2}, {0, 11, 0, 4, 0, 2}, {0, 6, 10, 0, 0, 2}, {4, 0, 4, 10, 0, 2}, {3, 0, 0, 0, 11, 4}},
    {{13, 0, 5, 0, 0, 2}, {0, 12, 0, 4, 0, 2}, {0, 6, 11, 0, 0, 2}, {4, 0, 4, 11, 0, 2}, {3, 0, 0, 0, 12, 4}},
    {{14, 0, 5, 0, 0, 2}, {0, 13, 0, 4, 0, 2}, {0, 7, 12, 0, 0, 2}, {5, 0, 5, 12, 0, 2}, {4, 0, 0, 0, 13, 4}}};

int umaVal[20], umaLv[7], card[7][25];
bool pres[10], frien[10];

void solve(void) {
    for (int i = 1; i <= 5; i++) cin >> umaVal[i];
    for (int i = 1; i <= 5; i++) cin >> umaVal[10 + i];
    umaVal[6] = 120, umaVal[16] = 0;
    for (int i = 1; i <= 6; i++) {
        cin >> card[i][21] >> card[i][22] >> card[i][23];
        long double val;
        for (int j = 1; j <= 5; j++) cin >> val, umaVal[j] += val;
        for (int j = 1; j <= 5; j++) cin >> card[i][j];
        card[i][6] = 0;
    }
    for (int i = 1; i <= 5; i++) umaVal[i] = min(umaVal[i], 1200);

    int n;
    cin >> n;
    while (n--) {
        for (int i = 1; i <= 6; i++) pres[i] = frien[i] = false;

        int summer, weight, drive, type, nS;
        cin >> summer >> weight >> drive >> type >> nS;
        long double coef = 0.1 * (drive - 2);
        for (int i = 1, x, y; i <= nS; i++) cin >> x >> y, pres[x] = true, frien[x] = y;
        int lv = (summer ? 5 : min(5, (umaLv[type]++ / 4 + 1)));
        for (int X = 1 + weight; X <= 6; X++) {
            long double v[6];
            for (int j = 0; j < 6; j++) v[j] = 0;

            v[0] = base[lv][type][X - 1];
            for (int i = 1; i <= 6; i++)
                if (pres[i]) v[0] += card[i][X];

            v[1] = 1;
            for (int i = 1; i <= 6; i++)
                if (frien[i]) v[1] *= 1 + 0.01 * card[i][21];

            v[2] = 1;
            for (int i = 1; i <= 6; i++)
                if (pres[i]) v[2] += 0.01 * card[i][23];

            v[3] = 1;
            for (int i = 1; i <= 6; i++)
                if (pres[i]) v[3] += 0.01 * card[i][22];
            v[3] = 1 + coef * v[3];

            v[4] = 1 + 0.01 * umaVal[10 + X];

            v[5] = 1;
            for (int i = 1; i <= 6; i++)
                if (pres[i]) v[5] += 0.05;

            int val = umaVal[X] + v[0] * v[1] * v[2] * v[3] * v[4] * v[5] + 1e-4;
            umaVal[X] = (X == 6 ? val : min(val, 1200));
        }

        for (int i = 1; i <= 6; i++) cout << umaVal[i] << ' ';
        cout << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}