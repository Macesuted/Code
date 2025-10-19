/**
 * @file 11224.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

using pii = pair<int, int>;

vector<vector<int>> graph;

set<pii>* S[maxn];
int ans[maxn];

void insert(set<pii>* S, int l, int r) {
    auto p = S->lower_bound({l, l});
    if (p != S->end() && p->first == r + 1) r = p->second, p = S->erase(p);
    if (p != S->begin() && (--p)->second == l - 1) l = p->first, S->erase(p);
    S->emplace(l, r);
    return;
}

void dfs(int p, int pre = -1) {
    S[p] = nullptr;
    int ch = -1;
    for (auto q : graph[p]) {
        if (q == pre) continue;
        dfs(q, p);
        if (!S[p] || S[p]->size() < S[q]->size()) S[p] = S[ch = q];
    }
    for (auto q : graph[p]) {
        if (q == pre || q == ch) continue;
        for (auto [l, r] : *S[q]) insert(S[p], l, r);
    }
    if (!S[p]) S[p] = new set<pii>;
    insert(S[p], p, p);
    ans[p] = S[p]->size();
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs(1);
    for (int i = 1; i <= n; i++) cout << ' ' << ans[i];
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    for (int i = 1; i <= _; i++) cout << "Case #" << i << ":", solve();

    return 0;
}
