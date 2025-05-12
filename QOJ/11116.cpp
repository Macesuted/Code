/**
 * @file 11116.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

int query(int x, int y) {
    if (x == y) return 0;
    cout << "? " << x + 1 << ' ' << y + 1 << endl;
    int ret;
    cin >> ret;
    return ret;
}

vector<tiii> graph;

void solve(const vector<int>& node, const vector<int>& dist) {
    if (node.size() == 1) return;
    if (node.size() == 2) return graph.emplace_back(node[0], node[1], dist[1]), void();

    int n = node.size(), p = 0;
    for (int i = 0; i < n; i++)
        if (dist[i] > dist[p]) p = i;

    vector<int> pdist;
    pdist.push_back(dist[p]);
    for (int i = 1; i < n; i++) pdist.push_back(query(node[p], node[i]));

    vector<pii> chain;
    for (int i = 0; i < n; i++)
        if (dist[i] + pdist[i] == dist[p]) chain.emplace_back(dist[i], node[i]);
    sort(chain.begin(), chain.end());

    for (int i = 1; i < (int)chain.size(); i++)
        graph.emplace_back(chain[i - 1].second, chain[i].second, chain[i].first - chain[i - 1].first);

    vector<vector<int>> cnode(chain.size()), cdist(chain.size());
    for (int i = 0; i < n; i++) {
        int w = (dist[i] + pdist[i] - dist[p]) / 2, d = dist[i] - w,
            x = lower_bound(chain.begin(), chain.end(), pii{d, 0}) - chain.begin();
        cnode[x].push_back(node[i]), cdist[x].push_back(w);
    }

    for (int i = 0; i < (int)chain.size(); i++) {
        for (int j = 0; j < (int)cnode[i].size(); j++)
            if (cnode[i][j] == chain[i].second) swap(cnode[i][j], cnode[i][0]), swap(cdist[i][j], cdist[i][0]);
        solve(cnode[i], cdist[i]);
    }

    return;
}

void solve(void) {
    int n;
    cin >> n;

    graph.clear();

    vector<int> dist, nodes;
    for (int i = 0; i < n; i++) nodes.push_back(i), dist.push_back(query(0, i));

    solve(nodes, dist);

    cout << "!";
    for (auto [x, y, w] : graph) cout << ' ' << x + 1 << ' ' << y + 1 << ' ' << w;
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}