/**
 * @file 9.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

typedef pair<int, int> pii;

int64_t fac[21];
vector<int> nums;
vector<pii> graph;

bool dfs(int64_t v, int p = 20) {
    if (v == 1) return true;
    for (int i = p; i >= 2; i--)
        if (v % fac[i] == 0) {
            nums.push_back(i);
            if (dfs(v / fac[i], i)) return true;
            nums.pop_back();
        }
    return false;
}

void solve(void) {
    int64_t K;
    cin >> K;
    if (K == 1) return cout << 1 << endl, void();
    nums.clear();
    if (!dfs(K)) return cout << -1 << endl, void();
    int n = nums.size(), m = n + 5;
    graph.clear();
    graph.emplace_back(n + 2, n + 1), graph.emplace_back(n + 1, 1);
    graph.emplace_back(n, n + 3), graph.emplace_back(n + 3, n + 4), graph.emplace_back(n + 4, n + 5);
    for (int i = 1; i < n; i++) graph.emplace_back(i, i + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < nums[i - 1]; j++) graph.emplace_back(i, ++m);
    cout << m << endl;
    for (auto i : graph) cout << i.first << ' ' << i.second << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = 1;
    for (int i = 1; i <= 20; i++) fac[i] = fac[i - 1] * i;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}