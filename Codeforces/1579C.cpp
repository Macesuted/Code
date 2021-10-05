/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 21

char a[maxn][maxn];
bool vis[maxn][maxn];

void work(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= m; j++)
            cin >> a[i][j], vis[i][j] = false;
    for (register int i = n; i; i--)
        for (register int j = 1; j <= m; j++) {
            if (a[i][j] == '.') continue;
            bool check = true;
            for (register int h = 0; h <= k; h++)
                if (!(i - h > 0 && j - h > 0 && j + h <= m && a[i - h][j - h] == '*' && a[i - h][j + h] == '*'))
                    check = false;
            if (!check) {
                if (vis[i][j]) continue;
                cout << "NO" << endl;
                return;
            }
            int h = 0;
            while (i - h > 0 && j - h > 0 && j + h <= m && a[i - h][j - h] == '*' && a[i - h][j + h] == '*') {
                vis[i - h][j - h] = vis[i - h][j + h] = true;
                h++;
            }
        }
    cout << "YES" << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}