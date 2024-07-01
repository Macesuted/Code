/**
 * @file P10679.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005

const int way[2][4] = {{0, +1, 0, -1}, {+1, 0, -1, 0}};
string a[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    a[0] = a[n + 1] = string(m + 2, '#');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = '#' + a[i] + '#';
    string ans1 = "A", ans2 = "AA";
    bool v = false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '#') continue;
            ans1 = max(ans1, string(1, a[i][j]));
            for (int t = 0; t < 4; t++) {
                int x = i + way[0][t], y = j + way[1][t];
                if (a[x][y] != '#') ans2 = max(ans2, string(1, a[i][j]) + string(1, a[x][y])), v = true;
            }
        }
    if (!v)
        cout << ans1 << endl;
    else {
        if (ans2[0] == ans2[1])
            cout << ans2[0] << endl;
        else
            cout << ans2 << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}