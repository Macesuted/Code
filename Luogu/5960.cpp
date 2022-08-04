/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 5005

typedef pair<int, int> pii;

int dist[maxn], cnt[maxn];
bool vis[maxn];

vector<vector<pii>> graph;

bool spfa(int S, int limit) {
    static queue<int> que;
    que.push(S), dist[S] = 0, vis[S] = true;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) {
                dist[i.first] = dist[p] + i.second;
                if (++cnt[i.first] > limit) return false;
                if (!vis[i.first]) que.push(i.first), vis[i.first] = true;
            }
        vis[p] = false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int to = read<int>(), from = read<int>(), dist = read<int>();
        graph[from].push_back({to, dist});
    }
    for (int i = 1; i <= n; i++) graph[0].push_back({i, 0});
    memset(dist, 0x3f, sizeof(dist));
    if (!spfa(0, n + 2)) return cout << "NO" << endl, 0;
    for (int i = 1; i <= n; i++) cout << dist[i] << ' ';
    cout << endl;
    return 0;
}