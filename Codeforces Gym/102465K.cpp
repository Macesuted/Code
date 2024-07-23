/**
 * @file 102465K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 705

int f[maxn][maxn], g[maxn][maxn];
string a;
vector<int> enu[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n >> a, a = ' ' + a;

    for (int i = 1; i <= n; i++) {
        for (int j = n - i + 1; j; j--) {
            f[i][j] = 1;
            if (j + 2 * i - 1 <= n) {
                bool chk = true;
                for (int t = 0; t < i && chk; t++) chk &= (a[j + t] == a[j + i + t]);
                if (chk) f[i][j] += f[i][j + i];
            }
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            if (i % j == 0) enu[i].push_back(j);

    for (int len = 1; len <= n; len++)
        for (int l = 1, r = len; r <= n; l++, r++) {
            g[l][r] = r - l + 1;
            for (int i = l; i < r; i++) g[l][r] = min(g[l][r], g[l][i] + g[i + 1][r]);
            for (auto i : enu[len])
                if (f[i][l] * i >= len) g[l][r] = min(g[l][r], g[l][l + i - 1]);
        }

    cout << g[1][n] << endl;

    return 0;
}