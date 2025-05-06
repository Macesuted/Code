/**
 * @file 2107E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-06
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

vector<vector<int>> graph;

int64_t calc(int64_t n) { return n * (n - 1) / 2; }

int solve(int n, int64_t& k) {
    graph.push_back({});
    int p = graph.size() - 1;
    while (n > 1) {
        int x = min(n - 1, (int)sqrt(k * 2) + 1);
        while (calc(x) > k) x--;
        n -= x, k -= calc(x);
        int u = solve(x, k);
        graph[p].push_back(u);
    }
    return p;
}

void solve(void) {
    int n;
    int64_t k;
    cin >> n >> k;

    graph.clear();
    solve(n, k);

    if (k > 1) return cout << "No" << endl, void();

    cout << "Yes" << endl;
    for (size_t i = 0; i < graph.size(); i++)
        for (size_t j : graph[i]) cout << i + 1 << ' ' << j + 1 << endl;

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