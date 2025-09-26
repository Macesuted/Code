/**
 * @file 1865.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 10005

using tiil = tuple<int, int, int64_t>;

int64_t a[maxn];
vector<tiil> ans;
vector<map<int, int64_t>> graph;

void op2(int x, int y, int64_t v) {
    if (v == 0) return;
    assert(v > 0);
    ans.emplace_back(x, y, v);
    a[x] ^= v, a[y] ^= v;
    graph[x][y] += v, graph[y][x] += v;
    return;
}
void op3(int x, int y, int z, int64_t v) {
    if (v == 0) return;
    if (v < 0) swap(x, z), v = -v;
    ans.emplace_back(x, z, v);
    a[x] ^= v, a[z] ^= v;
    graph[x][y] += v, graph[y][x] += v;
    graph[y][z] -= v, graph[z][y] -= v;
    return;
}

bool dfs(int p, int f) {
    for (auto [q, w] : graph[p]) {
        if (q == f) continue;
        if (!dfs(q, p)) return false;

        op3(f, p, q, a[q]);
        if (graph[p][q] % 2 != 0) return false;
        int64_t v = graph[p][q] / 2;
        op3(f, p, q, v);
        op3(f, p, q, v);
    }
    return true;
}

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, u, v, w; i < n; i++) cin >> u >> v >> w, graph[u][v] = graph[v][u] = w;

    ans.clear();

    auto print = [&](void) {
        cout << "YES" << endl;
        cout << ans.size() << endl;
        for (auto [x, y, w] : ans) cout << x << ' ' << y << ' ' << w << endl;
        return;
    };

    if (n == 1) {
        if (a[1] == 0)
            cout << "YES" << endl << 0 << endl;
        else
            cout << "NO" << endl;
        return;
    }

    int root = 1;
    while (graph[root].size() > 1) root++;

    int p = graph[root].begin()->first;
    if (!dfs(p, root)) return cout << "NO" << endl, void();

    if (a[p] != a[root]) return cout << "NO" << endl, void();

    op2(root, p, a[p]);

    if (graph[root][p] > 0 || -graph[root][p] % 2 == 1) return cout << "NO" << endl, void();

    op2(root, p, -graph[root][p] / 2);
    op2(root, p, -graph[root][p]);

    return print();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}