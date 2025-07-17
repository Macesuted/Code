/**
 * @file 100431A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
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

using pli = pair<int, int>;

#define maxn 1005

int calc(int x) { return (x & 1) ? x * (x - 1) / 2 : x * x / 2; }

unordered_multiset<int> graph[maxn];

vector<int> dfs(int p) {
    vector<int> ans;
    while (!graph[p].empty()) {
        int q = *graph[p].begin();
        graph[p].erase(graph[p].find(q));
        graph[q].erase(graph[q].find(p));
        vector<int> ret = dfs(q);
        for (auto p : ans) ret.push_back(p);
        ans = ret;
    }
    vector<int> ret;
    ret.push_back(p);
    for (auto x : ans) ret.push_back(x);
    return ret;
}

void solve(void) {
    int n;
    cin >> n;

    if (n == 4) return cout << "2\n1 2 1 2" << endl, void();

    int x = 3;
    while (calc(x + 1) <= n) x++;
    if (calc(x) + 1 == n && (x & 1)) x--;

    for (int i = 1; i <= x; i++)
        for (int j = 1; j <= x; j++)
            if (i != j) graph[i].insert(j);
    if (!(x & 1))
        for (int i = 1; i <= n; i += 2) graph[i].insert(i + 1), graph[i + 1].insert(i);
    graph[1].erase(graph[1].find(2));
    graph[2].erase(graph[2].find(1));

    vector<int> ans = dfs(1);
    // cerr << "! " << ans.size() << endl;
    if ((int)ans.size() < n) {
        if (x & 1) ans.push_back(1);
        while ((int)ans.size() < n) ans.push_back(2 + (ans.back() == 2));
    }

    cout << x << endl;
    for (auto i : ans) cout << i << ' ';
    cout << endl;

    set<pli> S;
    auto ins = [&](int x, int y) -> void {
        assert(x != y);
        S.emplace(min(x, y), max(x, y));
        return;
    };
    for (int i = 0; i + 1 < (int)ans.size(); i++) ins(ans[i], ans[i + 1]);
    ins(ans.front(), ans.back());
    for (int i = 1; i <= x; i++)
        for (int j = i + 1; j <= x; j++) assert(S.count({i, j}));

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("achromatic.in", "r", stdin), freopen("achromatic.out", "w", stdout);
#endif
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