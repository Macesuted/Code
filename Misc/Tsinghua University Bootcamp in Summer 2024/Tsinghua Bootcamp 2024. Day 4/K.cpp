/**
 * @file K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 1005
#define maxm 10005

typedef pair<int, int> pii;

bool f[maxn][maxn];
int rest[maxn][maxn], cur[maxn][maxn];
pii h[maxm];

bool solve(void) {
    int n, k, m;
    cin >> n >> k >> m;
    if (k <= 2) return true;
    if (k == 4) return m == 1;
    for (int i = 1; i <= m; i++) cin >> h[i].first >> h[i].second;
    sort(h + 1, h + m + 1);
    f[n][n] = true;
    for (int i = n; i; i--)
        for (int j = n; j; j--) {
            if (!f[i][j]) continue;
            if (!rest[i][j]) rest[i][j] = h[++cur[i][j]].second;
            if (rest[i][j] >= i) f[i][j - 1] = true, rest[i][j - 1] = rest[i][j] - i, cur[i][j - 1] = cur[i][j];
            if (rest[i][j] >= j) f[i - 1][j] = true, rest[i - 1][j] = rest[i][j] - j, cur[i - 1][j] = cur[i][j];
        }
    for (int i = 1; i <= n; i++)
        if (f[i][0] || f[0][i]) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) cout << (solve() ? "YES" : "NO") << endl;

    return 0;
}