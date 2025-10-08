/**
 * @file 8472.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-06
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

int cnt;

vector<vector<int>> graph;
vector<int> typ;

int newNode(void) { return graph.push_back(vector<int>()), typ.push_back(0), ++cnt; }

vector<int> solve(int l, int r) {
    if (l == r) return vector<int>(1, l);

    int mid = (l + r) >> 1;
    vector<int> pl = solve(l, mid), pr = solve(mid + 1, r);
    pl.push_back(-1), pr.push_back(-1);

    vector<vector<int>> val(pl.size(), vector<int>(pr.size()));
    for (size_t i = 0; i < pl.size(); i++)
        for (size_t j = 0; j < pr.size(); j++)
            val[i][j] = newNode(), typ[val[i][j]] = 1, graph[val[i][j]].push_back(pl[i]), graph[val[i][j]].push_back(pr[j]);

    vector<int> ret(pl.size() + pr.size() - 2);
    for (size_t i = 0; i < pl.size() + pr.size() - 2; i++) ret[i] = newNode(), typ[ret[i]] = 2;
    for (size_t i = 0; i < pl.size(); i++)
        for (size_t j = 0; j < pr.size(); j++)
            if (i + j < ret.size()) graph[ret[i + j]].push_back(val[i][j]);

    return ret;
}

void solve(void) {
    int n;
    cin >> n, cnt = n;
    graph.resize(n + 1), typ.resize(n + 1);

    vector<int> ans = solve(1, n);
    int ret = newNode();
    typ[ret] = 1;
    graph[ret].push_back(ans[n / 2]);

    cout << cnt - n << endl;
    for (int i = n + 1; i <= cnt; i++) {
        cout << (typ[i] == 1 ? "AND" : "OR") << ' ' << graph[i].size();
        for (auto x : graph[i]) cout << ' ' << x;
        cout << endl;
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