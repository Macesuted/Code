/**
 * @file 16118.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define mod 1'000'000'007

#define maxn 1000005

bool fix[maxn];
int fa[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n, m, rest = 0;
    cin >> n >> m;

    vector<vector<pair<int, int>>> rec(n + 1);
    for (int i = 1, x, y, v; i <= m; i++) {
        cin >> x >> y >> v;
        rec[v].emplace_back(x, y);
    }

    vector<set<int>> graph(n + 1);
    for (int v = 1; v <= n; v++) {
        if (rec[v].empty()) {
            rest++;
            continue;
        }

        sort(rec[v].begin(), rec[v].end());
        rec[v].resize(unique(rec[v].begin(), rec[v].end()) - rec[v].begin());

        map<int, int> cnt;
        for (auto [x, y] : rec[v]) cnt[x]++, cnt[y]++;

        vector<int> ps;
        for (auto [x, c] : cnt)
            if (c == (int)rec[v].size()) ps.push_back(x);

        if (ps.empty()) return cout << 0 << endl, void();
        if (ps.size() == 1) {
            if (fix[ps[0]]) return cout << 0 << endl, void();
            fix[ps[0]] = true;
        } else
            graph[ps[0]].insert(ps[1]), graph[ps[1]].insert(ps[0]);
    }

    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (fix[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();

        while (!graph[p].empty()) {
            int q = *graph[p].begin();
            if (fix[q]) return cout << 0 << endl, void();
            fix[q] = true;
            graph[p].erase(q), graph[q].erase(p);
            que.push(q);
        }
    }

    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (i < j) edges.emplace_back(i, j);

    for (int i = 1; i <= n; i++) fa[i] = i;

    for (auto [x, y] : edges) fa[getfa(y)] = getfa(x);

    vector<int> cntV(n + 1), cntE(n + 1);
    for (int i = 1; i <= n; i++) cntV[getfa(i)]++;
    for (auto [x, y] : edges) cntE[getfa(x)]++;

    int64_t ans = 1;
    for (int i = 1; i <= n; i++) {
        if (getfa(i) != i) continue;
        if (cntE[i] > cntV[i]) return cout << 0 << endl, void();

        if (cntE[i] == cntV[i])
            ans = ans * 2 % mod;
        else
            ans = ans * cntV[i] % mod;
    }

    for (int i = 1; i <= rest; i++) ans = ans * i % mod;

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
