/**
 * @file 15478.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int a[maxn], va[maxn], f[maxn];
int64_t g[maxn];
vector<int> graph[maxn];

void dfs(int p, int pre = -1) {
    for (auto q : graph[p]) {
        if (q == pre) continue;

        dfs(q, p);

        if (a[p] > a[q]) {
            if (g[q] >= 0) continue;
            g[p] += g[q];
        } else if (a[p] == a[q]) {
            if (g[q] < 0) throw 1919810;
        } else {
            if (g[q] < 0) throw 114;
            g[p] += g[q];
        }
    }

    if (g[p] < 0 && pre == -1) throw 514;

    return;
}

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) cin >> a[i], va[i] = a[i];
    sort(va + 1, va + n + 1);

    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    for (int i = 1, x; i <= m; i++) cin >> x, f[x]--;
    for (int i = 1, x; i <= k; i++) cin >> x, f[x]++;

    auto check = [&](int v) -> bool {
        for (int i = 1; i <= n; i++) {
            g[i] = f[i];
            if (a[i] >= v) g[i] += m;
        }

        try {
            dfs(1);
        } catch (int e) {
            return false;
        }

        return true;
    };

    int l = 1, r = n + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(va[mid]) ? l : r) = mid;
    }

    cout << va[l] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
