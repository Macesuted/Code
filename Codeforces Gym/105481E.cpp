/**
 * @file 105481E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    int cnt = 0;

    auto flush = [&](int tn, int tm) {
        for (int i = n - 3; i > tn; i -= 4)
            for (int j = 1; j <= m; j++) a[i][j] = a[i + 1][j] = a[i + 2][j] = a[i + 3][j] = ++cnt;
        for (int i = tn + 1; i <= n % 4; i++)
            for (int j = m - 3; j >= 1; j -= 4) a[i][j] = a[i][j + 1] = a[i][j + 2] = a[i][j + 3] = ++cnt;
        for (int i = 1; i <= tn; i++)
            for (int j = m - 3; j > tm; j -= 4) a[i][j] = a[i][j + 1] = a[i][j + 2] = a[i][j + 3] = ++cnt;
        return;
    };
    auto print = [&]() {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cout << a[i][j] << ' ';
            cout << endl;
        }
        return;
    };

    int tn = n % 4, tm = m % 4;
    if (tn == 0 || tm == 0) return flush(0, 0), print();
    if (tn == 2 && tm == 2) {
        if (n >= 6) {
            flush(6, 2);
            a[1][1] = a[1][2] = a[2][1] = a[3][1] = ++cnt;
            a[4][1] = a[5][1] = a[6][1] = a[6][2] = ++cnt;
            a[2][2] = a[3][2] = a[4][2] = a[5][2] = ++cnt;
            return print();
        }
        if (m >= 6) {
            flush(2, 6);
            a[1][1] = a[1][2] = a[1][3] = a[2][1] = ++cnt;
            a[1][4] = a[1][5] = a[1][6] = a[2][6] = ++cnt;
            a[2][2] = a[2][3] = a[2][4] = a[2][5] = ++cnt;
            return print();
        }
    }

    cout << "NO" << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}