/**
 * @file 7464.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 500005
#define endl '\n'

typedef pair<int, int> pii;
typedef pair<int64_t, int> pli;
typedef pair<int, int64_t> pil;

int read(void) {
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -f;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

vector<vector<pil>> graph;
int64_t dist[maxn];
bool vis[maxn];

void solve(void) {
    int n = read(), m = read(), k = read();
    int S = 1, lgS = 0;
    while (S <= n) S <<= 1, lgS++;
    graph.clear(), graph.resize(2 * S + n + 1);
    for (int i = 1; i <= 2 * S + n; i++) dist[i] = INT64_MAX, vis[i] = false;
    for (int i = 1, x, y, t; i <= m; i++)
        x = read(), y = read(), t = read(), graph[2 * S + x].emplace_back(2 * S + y, t),
        graph[2 * S + y].emplace_back(2 * S + x, t);
    for (int i = 1; i <= n; i++) graph[2 * S + i].emplace_back(i, 0), graph[S + i].emplace_back(2 * S + i, 0);
    for (int i = 1; i < S; i++) graph[i].emplace_back(S + i, (int64_t)i * k);
    priority_queue<pli, vector<pli>, greater<pli>> que;
    que.emplace(dist[2 * S + 1] = 0, 2 * S + 1);
    while (!que.empty()) {
        auto [d, p] = que.top();
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto [i, t] : graph[p])
            if (dist[i] > d + t) que.emplace(dist[i] = d + t, i);
        if (p <= S) {
            for (int x = 0; x < lgS; x++)
                if (!(p >> x & 1)) {
                    int q = p ^ (1 << x);
                    if (dist[q] > dist[p]) que.emplace(dist[q] = dist[p], q);
                }
        } else if (p <= 2 * S) {
            p -= S;
            if (__builtin_popcount(p) == 1) continue;
            for (int x = 0; x < lgS; x++)
                if (p >> x & 1) {
                    int q = p ^ (1 << x);
                    if (dist[q + S] > dist[p + S]) que.emplace(dist[q + S] = dist[p + S], q + S);
                }
        }
    }

    for (int i = 2; i <= n; i++) cout << dist[2 * S + i] << ' ';
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}
