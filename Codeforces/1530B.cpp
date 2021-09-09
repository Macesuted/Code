/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 30

const int way[2][8] = {{-1, -1, -1, 0, 1, 1, 1, 0}, {-1, 0, 1, 1, 1, 0, -1, -1}};

bool a[maxn][maxn];

void work(void) {
    int n, m;
    cin >> n >> m;
    memset(a, 0, sizeof(a));
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= m; j++)
            if (i == 1 || j == 1 || i == n || j == m) {
                bool check = true;
                for (register int k = 0; k <= 7; k++)
                    if (a[i + way[0][k]][j + way[1][k]]) check = false;
                if (check) a[i][j] = true;
            }
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= m; j++)
            if (a[i][j])
                cout << '1';
            else
                cout << '0';
        cout << endl;
    }
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}