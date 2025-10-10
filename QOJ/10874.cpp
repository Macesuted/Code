/**
 * @file 10874.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

using pli = pair<int64_t, int>;

int h[2][maxn], f[maxn], indeg[maxn], id[maxn];
bool valid[maxn], vis[maxn];
vector<int> graph[maxn];

void solve(void) {
    vector<int64_t> pos;
    vector<pli> poss[2];
    pos.push_back(0);
    for (int t = 0, m; t < 2; t++) {
        cin >> m;
        int64_t pre = 0;
        for (int i = 1, w, h; i <= m; i++) cin >> w >> h, pos.push_back(pre += w), poss[t].emplace_back(pre, h);
    }

    sort(pos.begin(), pos.end());
    int n = unique(pos.begin(), pos.end()) - pos.begin() - 1;

    for (int t = 1; ~t; t--)
        for (int j = 1, k = 0; j <= n; j++) {
            while (poss[t][k].first < pos[j]) k++;
            h[t][j] = poss[t][k].second, id[j] = k + 1;
        }

    for (int i = 1; i <= n; i++) valid[i] = (h[0][i] == h[1][i]);

    f[0] = INT_MAX;
    for (int i = 1; i <= n; i++) {
        f[i] = min(f[i - 1], h[1][i]);
        if (h[0][i] == f[i])
            f[i] = INT_MAX;
        else
            valid[i] = false;
    }

    f[n + 1] = INT_MAX;
    for (int i = n; i >= 1; i--) {
        f[i] = min(f[i + 1], h[1][i]);
        if (h[0][i] == f[i])
            f[i] = INT_MAX;
        else
            valid[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        if (!h[1][i]) continue;
        if (i - 1 >= 1 && h[1][i - 1] <= h[1][i]) graph[i].push_back(i - 1), indeg[i - 1]++;
        if (i + 1 <= n && h[1][i + 1] <= h[1][i]) graph[i].push_back(i + 1), indeg[i + 1]++;
    }

    vector<int> nodes;
    for (int i = 1; i <= n; i++)
        if (valid[i] && h[1][i]) nodes.push_back(i);
    sort(nodes.begin(), nodes.end(), [&](int x, int y) { return h[1][x] > h[1][y]; });

    vector<int> ans;
    for (auto p : nodes) {
        if (vis[p]) continue;

        ans.push_back(p);
        vis[p] = true;

        for (int i = p - 1, v = h[0][p]; i >= 1 && !vis[i] && h[1][i]; i--)
            if ((v = min(v, h[0][i])) == h[1][i])
                vis[i] = true;
            else
                break;
        for (int i = p + 1, v = h[0][p]; i <= n && !vis[i] && h[1][i]; i++)
            if ((v = min(v, h[0][i])) == h[1][i])
                vis[i] = true;
            else
                break;
    }

    for (int i = 1; i <= n; i++)
        if (h[1][i] && !vis[i]) return cout << -1 << endl, void();

    cout << ans.size() << endl;
    for (auto x : ans) cout << id[x] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}