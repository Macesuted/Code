/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 405

typedef pair<int, int> pii;

int a[maxn][maxn], sum[maxn][maxn];

int SUM(int i1, int j1, int i2, int j2) { return sum[i2][j2] - sum[i2][j1 - 1] - sum[i1 - 1][j2] + sum[i1 - 1][j1 - 1]; }
int cost(int i1, int j1, int i2, int j2) {
    return (j2 - j1 - 1 - SUM(i1, j1 + 1, i1, j2 - 1)) +
           (j2 - j1 - 1 - SUM(i2, j1 + 1, i2, j2 - 1)) +
           (i2 - i1 - 1 - SUM(i1 + 1, j1, i2 - 1, j1)) +
           (i2 - i1 - 1 - SUM(i1 + 1, j2, i2 - 1, j2)) +
           SUM(i1 + 1, j1 + 1, i2 - 1, j2 - 1);
}
int limit(int i1, int j1, int i2, int j2) {
    return (j2 - j1 - 1 - SUM(i2, j1 + 1, i2, j2 - 1)) +
           (i2 - i1 - 1 - SUM(i1 + 1, j2, i2 - 1, j2));
}

void work(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            sum[i][j] = a[i][j] = (c == '1');
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] += sum[i][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] += sum[i - 1][j];
    int answer = 16;
    for (int i = 5; i <= n; i++)
        for (int j = 4; j <= m; j++) {
            if (SUM(i - 3, j - 2, i - 1, j - 1) >= answer) continue;
            for (int x = i - 4; x; x--) {
                if (SUM(x + 1, j - 2, i - 1, j - 1) >= answer || limit(x, j - 3, i, j) >= answer) break;
                for (int y = j - 3; y; y--) {
                    if (SUM(x + 1, y + 1, i - 1, j - 1) >= answer || limit(x, y, i, j) >= answer) break;
                    answer = min(answer, cost(x, y, i, j));
                }
            }
        }
    cout << answer << endl;
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