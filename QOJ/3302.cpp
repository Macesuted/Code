/**
 * @file 3302.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005

using pii = pair<int, int>;

int fa[maxn], siz[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n, m;
    cin >> n >> m;

    map<int, vector<pii>> edges;
    for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, edges[w].emplace_back(x, y);

    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;

    int64_t ans = 0;
    for (auto it = edges.rbegin(); it != edges.rend(); it++) {
        auto& [v, S] = *it;

        for (auto [x, y] : S)
            if (getfa(x) == getfa(y)) return cout << -1 << endl, void();

        for (auto [x, y] : S) {
            x = getfa(x), y = getfa(y);
            if (x == y) continue;
            ans += (int64_t)v * siz[x] * siz[y];
            fa[x] = y, siz[y] += siz[x];
        }
    }

    int rest = n;
    for (int i = 1; i <= n; i++)
        if (fa[i] == i) ans += (int64_t)siz[i] * (rest -= siz[i]);

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}