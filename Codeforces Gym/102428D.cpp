/**
 * @file 102428D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

typedef pair<double, int> pdi;

const double PI = acos(-1);

int x[maxn], y[maxn], w[maxn];

int n;

map<double, int> S;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i] >> w[i];

    S[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (w[i] <= w[j]) continue;
            double f = atan2(y[j] - y[i], x[j] - x[i]);
            double fl = f + 0.5 * PI + 1e-6, fr = f + 1.5 * PI - 1e-6;
            if (fl > 2 * PI) fl -= 2 * PI, fr -= 2 * PI;
            if (fl < 0) fl += 2 * PI, fr += 2 * PI;
            if (fr > 2 * PI)
                S[fl]++, S[0]++, S[fr - 2 * PI]--;
            else
                S[fl]++, S[fr]--;
        }

    int cnt = 0;
    for (auto [v, d] : S)
        if ((cnt += d) == 0) return cout << "Y" << endl, 0;
    cout << "N" << endl;
    return 0;
}