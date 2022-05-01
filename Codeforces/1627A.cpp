/**
 * @file 1627A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 55

char a[maxn][maxn];

void solve(void) {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    if (a[r][c] == 'B') return cout << 0 << endl, void();
    bool check1 = false;
    for (int i = 1; i <= n; i++)
        if (a[i][c] == 'B') check1 = true;
    for (int i = 1; i <= m; i++)
        if (a[r][i] == 'B') check1 = true;
    if (check1) return cout << 1 << endl, void();
    bool check2 = false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == 'B') check2 = true;
    if (check2) return cout << 2 << endl, void();
    cout << -1 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
