/**
 * @file 14409.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

using pii = pair<int, int>;

bool notp[maxn];
vector<int> prime;
uint64_t val[maxn];

vector<pii> graph[maxn];
uint64_t dist[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;

    auto $ = [&](int x, int y) -> int { return (x - 1) * n + y - 1; };
    auto _ = [&](int id) -> pii { return {id / n + 1, id % n + 1}; };

    auto addEdge = [&](int x, int y, int v) -> void {
        return graph[x].emplace_back(y, v), graph[y].emplace_back(x, v), void();
    };

    for (int i = 1; i < n; i++)
        for (int j = 1, x; j <= i; j++) cin >> x, addEdge($(i, j), $(i + 1, j), x);

    for (int i = 1; i < n; i++)
        for (int j = 1, x; j <= i; j++) cin >> x, addEdge($(i, j), $(i + 1, j + 1), x);

    for (int i = 2; i <= n; i++)
        for (int j = 1, x; j < i; j++) cin >> x, addEdge($(i, j), $(i, j + 1), x);

    map<uint64_t, int> S;

    queue<int> que;
    que.push($(1, 1)), dist[$(1, 1)] = 0, vis[$(1, 1)] = true;
    while (!que.empty()) {
        int p = que.front();
        que.pop();

        S[dist[p]]++;

        for (auto [q, w] : graph[p]) {
            uint64_t d = dist[p] ^ val[w];
            if (!vis[q]) que.push(q), vis[q] = true, dist[q] = d;
            if (dist[q] != d) return cout << 0 << endl, void();
        }
    }

    int64_t ans = 0;
    for (auto [v, cnt] : S) ans += (int64_t)cnt * (cnt - 1) / 2;
    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    mt19937_64 rnd(114514);

    val[1] = 0;
    for (int i = 2; i < maxn; i++) {
        if (!notp[i]) val[i] = rnd(), prime.push_back(i);
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            notp[i * *j] = true, val[i * *j] = val[i] ^ val[*j];
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

    return 0;
}
