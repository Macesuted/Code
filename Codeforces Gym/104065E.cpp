/**
 * @file 104065E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define mod 998244353

typedef pair<int, int> pii;

int a[maxn], b[maxn];
int64_t f[maxn];
vector<vector<pii>> graph;
map<int, int> rec;
multiset<int64_t> S[maxn];

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q, graph.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y, d; i <= m; i++) cin >> x >> y >> d, graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
    for (int i = 1; i <= n; i++) {
        for (auto [j, d] : graph[i]) rec[j] = min(rec.count(j) ? rec[j] : INT_MAX, d);
        graph[i].clear();
        for (auto [j, d] : rec) graph[i].emplace_back(j, d);
        rec.clear();
        sort(graph[i].begin(), graph[i].end(), [&](pii x, pii y) { return graph[x.first].size() > graph[y.first].size(); });
    }
    int B = sqrt(m / log2(n));
    for (int i = 1; i <= n; i++)
        if ((int)graph[i].size() <= B)
            for (auto [j, w] : graph[i]) S[j].insert(w);
    for (int i = 1; i <= q; i++) cin >> b[i];
    for (int i = q; i; i--) {
        if ((int)graph[b[i]].size() <= B)
            for (auto [j, w] : graph[b[i]]) S[j].erase(S[j].find(f[b[i]] + w));
        f[b[i]] = 1e18;
        if (!S[b[i]].empty()) f[b[i]] = *S[b[i]].begin();
        for (auto [j, w] : graph[b[i]]) {
            if ((int)graph[j].size() <= B) break;
            f[b[i]] = min(f[b[i]], f[j] + w);
        }
        if ((int)graph[b[i]].size() <= B)
            for (auto [j, w] : graph[b[i]]) S[j].insert(f[b[i]] + w);
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + f[i] % mod * a[i]) % mod;
    cout << ans << endl;
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