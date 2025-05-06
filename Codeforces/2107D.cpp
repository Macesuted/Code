/**
 * @file 2107D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
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

#define maxn 200005

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

vector<vector<int>> graph;
bool ban[maxn];
unordered_set<int> rest;
int pre[maxn];

pii getFar(int p, int fa = -1) {
    pii ans = {0, p};
    int xq = p;
    for (auto q : graph[p])
        if (q != fa && !ban[q]) {
            pii v = getFar(q, p);
            if (v > ans) ans = v, xq = q;
        }
    pre[xq] = p;
    return {ans.first + 1, ans.second};
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    for (int i = 1; i <= n; i++) ban[i] = false, rest.insert(i);

    vector<tiii> ans;

    while (!rest.empty()) {
        int i = *rest.begin();

        pii x = getFar(i), y = getFar(x.second);

        int p = y.second;
        while (p != x.second) ban[p] = true, rest.erase(p), p = pre[p];
        ban[x.second] = true, rest.erase(x.second);

        ans.emplace_back(y.first, max(y.second, x.second), min(y.second, x.second));
    }

    sort(ans.begin(), ans.end(), greater<tiii>());

    for (auto [d, x, y] : ans) cout << d << ' ' << x << ' ' << y << ' ';
    cout << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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