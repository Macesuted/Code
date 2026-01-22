/**
 * @file 15624.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

bool a[maxn][maxn];
set<int> r[maxn], c[maxn];

bool solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++) a[i][j] = (s[j - 1] == '#');
    }

    auto insert = [&](int x, int y) { return r[x].insert(y), c[y].insert(x), a[x][y] = false; };

    for (int i = 1; i <= n; i++) r[i].clear(), r[i].insert(m + 1);
    for (int j = 1; j <= m; j++) c[j].clear(), c[j].insert(n + 1);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!a[i][j]) insert(i, j);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (!a[i][j]) continue;

            if (i + k - 1 > n || j + k - 1 > m) return false;
            if (!a[i + k - 1][j] || !a[i][j + k - 1] || !a[i + k - 1][j + k - 1]) return false;

            unordered_set<int> face;
            if (*r[i].lower_bound(j) >= j + k) face.insert(0);
            if (*r[i + k - 1].lower_bound(j) >= j + k) face.insert(1);
            if (*c[j].lower_bound(i) >= i + k) face.insert(2);
            if (*c[j + k - 1].lower_bound(i) >= i + k) face.insert(3);

            if (face.size() != 3) return false;

            insert(i, j);
            insert(i + k - 1, j);
            insert(i, j + k - 1);
            insert(i + k - 1, j + k - 1);

            if (face.count(0))
                for (int x = j + 1; x < j + k - 1; x++) insert(i, x);
            if (face.count(1))
                for (int x = j + 1; x < j + k - 1; x++) insert(i + k - 1, x);
            if (face.count(2))
                for (int x = i + 1; x < i + k - 1; x++) insert(x, j);
            if (face.count(3))
                for (int x = i + 1; x < i + k - 1; x++) insert(x, j + k - 1);
        }

    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "yes" : "no") << endl;

    return 0;
}
