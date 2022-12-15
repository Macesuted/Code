/**
 * @file 1761E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-15
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

#define maxn 4005

vector<vector<int>> graph, blk;
bool vis[maxn];
vector<int> cache;

void dfs1(int p) {
    vis[p] = true, cache.push_back(p);
    for (auto i : graph[p])
        if (!vis[i]) dfs1(i);
    return;
}
int dfs2(int p) {
    vis[p] = true;
    for (auto i : graph[p])
        if (!vis[i]) return dfs2(i);
    return p;
}

void solve(void) {
    int n;
    cin >> n, graph.clear(), graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
            if (s[j] == '1') graph[i].push_back(j + 1);
    }
    for (int i = 1; i <= n; i++) vis[i] = false;
    blk.clear();
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs1(i), blk.push_back(cache), cache.clear();
    }
    for (int i = 1; i <= n; i++) vis[i] = false;
    if (blk.size() == 1) return cout << 0 << endl, void();
    for (auto &S : blk) {
        if (S.size() == 1) return cout << 1 << endl << S[0] << endl, void();
        int cnt = 0, v = 0;
        for (auto i : S) cnt += (graph[i].size() + 1 == S.size());
        if (cnt == (int)S.size()) continue;
        while (graph[S[v]].size() + 1 == S.size()) v++;
        return cout << 1 << endl << (cnt ? S[v] : dfs2(S[0])) << endl, void();
    }
    if (blk.size() >= 3) return cout << 2 << endl << blk[0][0] << ' ' << blk[1][0] << endl, void();
    vector<int> minS;
    for (auto &S : blk)
        if (minS.empty() || S.size() < minS.size()) minS = S;
    cout << minS.size() << endl;
    for (auto i : minS) cout << i << ' ';
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