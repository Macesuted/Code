/**
 * @file 102465E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 10005

string a[maxn];
int v[maxn], vl[maxn], vr[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n, suml = 0, sumr = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> v[i], v[i] *= 100, suml += max(0, v[i] - 50), sumr += min(10000, v[i] + 49);
    for (int i = 1; i <= n; i++) {
        suml -= max(0, v[i] - 50), sumr -= min(10000, v[i] + 49);
        vl[i] = max({0, v[i] - 50, 10000 - sumr}), vr[i] = min({10000, v[i] + 49, 10000 - suml});
        if (vl[i] > vr[i]) return cout << "IMPOSSIBLE" << endl, 0;
        suml += max(0, v[i] - 50), sumr += min(10000, v[i] + 49);
    }
    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ' << vl[i] / 100 << '.' << vl[i] / 10 % 10 << vl[i] % 10 << ' ' << vr[i] / 100 << '.'
             << vr[i] / 10 % 10 << vr[i] % 10 << endl;

    return 0;
}