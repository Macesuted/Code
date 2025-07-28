/**
 * @file 6187.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

#define maxn 100005

using tiii = tuple<int, int, int>;

int fa[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1, x, y; i <= n; i++) cin >> x >> y;

        vector<tiii> edges;
        int64_t ans = 0, cnt = m;
        for (int i = 1, x, y, w; i <= m; i++) cin >> x >> y >> w, ans += w, edges.emplace_back(w, x, y);
        sort(edges.begin(), edges.end(), greater<tiii>());

        for (int i = 1; i <= n; i++) fa[i] = i;

        for (auto [w, x, y] : edges) {
            x = getfa(x), y = getfa(y);
            if (x != y) fa[x] = y, ans -= w, cnt--;
        }

        cout << cnt << ' ' << ans << endl;
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