/**
 * @file 9570.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef pair<int, int> pii;

vector<bool> ban;
vector<int> siz;
vector<vector<int>> graph;

int lim;
int query(int x, int y) {
    assert(lim--);
    cout << "? " << x << ' ' << y << endl;
    int ret;
    cin >> ret;
    return ret;
}

void getSiz(int p, int fa = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != fa && !ban[i]) getSiz(i, p), siz[p] += siz[i];
    return;
}
pii fndRoot(int p, int n, int fa = -1) {
    pii cur = {n - siz[p], p}, ans = {n, 0};
    for (auto i : graph[p])
        if (i != fa && !ban[i]) cur.first = max(cur.first, siz[i]), ans = min(ans, fndRoot(i, n, p));
    return min(ans, cur);
}

int solve(int p) {
    getSiz(p), p = fndRoot(p, siz[p]).second;

    vector<int> neigh;
    for (auto i : graph[p])
        if (!ban[i]) neigh.push_back(i);

    if (neigh.empty()) return p;
    if (neigh.size() == 1) return query(p, neigh[0]) == 0 ? p : neigh[0];
    if (neigh.size() == 2) {
        int ret = query(neigh[0], neigh[1]);
        if (ret == 0) return ban[p] = true, solve(neigh[0]);
        if (ret == 2) return ban[p] = true, solve(neigh[1]);
        return p;
    }
    getSiz(p);

    sort(neigh.begin(), neigh.end(), [&](int a, int b) { return siz[a] > siz[b]; });
    int ret = query(neigh[0], neigh[1]);
    if (ret == 0) return ban[p] = true, solve(neigh[0]);
    if (ret == 2) return ban[p] = true, solve(neigh[1]);
    return ban[neigh[0]] = ban[neigh[1]] = true, solve(p);
}

void solve(void) {
    int n;
    cin >> n;

    lim = 1;
    while (1 << (lim + 1) <= n) lim++;

    ban.clear(), ban.resize(n + 1);
    siz.clear(), siz.resize(n + 1);
    graph.clear(), graph.resize(n + 1);

    for (int i = 1, cl, cr; i <= n; i++) {
        cin >> cl >> cr;
        if (cl) graph[i].push_back(cl), graph[cl].push_back(i);
        if (cr) graph[i].push_back(cr), graph[cr].push_back(i);
    }
    int ans = solve(1);
    cout << "! " << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
