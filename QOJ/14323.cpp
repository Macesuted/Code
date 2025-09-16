/**
 * @file 14323.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

using pii = pair<int, int>;

void solve(void) {
    int n, m;
    cin >> n >> m;

    set<int> nodes, graph[n + 1];

    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, nodes.insert(x), nodes.insert(y), graph[x].insert(y), graph[y].insert(x);

    if (n == 2) {
        cout << "YES" << endl;
        cout << 1 << ' ' << 2 << endl;
        return;
    }

    vector<int> emp;
    for (int i = 1; i <= n; i++)
        if (!nodes.count(i)) emp.push_back(i);

    vector<vector<int>> blks;
    while (!nodes.empty()) {
        int p = *nodes.begin();
        vector<int> rec;
        for (auto q : nodes)
            if (!graph[p].count(q)) rec.push_back(q);
        for (auto x : rec) nodes.erase(x);
        blks.push_back(rec);
    }

    int64_t cnt = 0, sum = 0;
    for (size_t i = 0; i < blks.size(); i++) cnt += blks[i].size() * sum, sum += blks[i].size();

    if (cnt != m) return cout << "NO" << endl, void();

    if ((int)blks.size() == n - 1) {
        if (emp.size() != 1) return cout << "NO" << endl, void();
        cout << "YES" << endl;
        for (int i = 0; i < n - 1; i++) cout << emp[0] << ' ' << blks[i][0] << endl;
        return;
    }

    if (blks.size() == 2) {
        if (emp.size() < 2) return cout << "NO" << endl, void();
        cout << "YES" << endl;
        for (size_t i = 0; i < 2; i++)
            for (auto p : blks[i]) cout << emp[i] << ' ' << p << endl;
        if (emp.size() == 2) return cout << emp[0] << ' ' << emp[1] << endl, void();
        cout << emp[0] << ' ' << emp[2] << endl;
        cout << emp[2] << ' ' << emp[1] << endl;
        for (size_t i = 3; i < emp.size(); i++) cout << emp[2] << ' ' << emp[i] << endl;
        return;
    }

    if (emp.size() < blks.size() + 1) return cout << "NO" << endl, void();
    cout << "YES" << endl;
    for (size_t i = 0; i < blks.size(); i++)
        for (auto p : blks[i]) cout << emp[i] << ' ' << p << endl;
    for (size_t i = 0; i < blks.size(); i++) cout << emp[i] << ' ' << emp[blks.size()] << endl;
    for (size_t i = blks.size() + 1; i < emp.size(); i++) cout << emp[blks.size()] << ' ' << emp[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}