/**
 * @file 3500.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifdef MACESUTED
bool mem1;
#endif

template <typename T>
T read(void) {
    T f = +1, num = 0;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
    return f * num;
}
template <typename T>
void write(T num) {
    if (num == 0) return putchar('0'), void();
    if (num < 0) putchar('-'), num = -num;
    if (num > 9) write(num / 10);
    putchar((num % 10) ^ 48);
    return;
}

#define maxn 305

typedef pair<int, int> pii;

int a[maxn][maxn], b[maxn][maxn], cnt[maxn * 2];
long long dist[maxn * 2];
bool vis[maxn * 2];

vector<vector<pii>> graph;

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++) b[i][j] = read<int>();
    for (int i = 1; i <= m; i++) a[1][i] = 0;
    for (int i = 1; i <= n; i++) a[i][1] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= m; j++) a[i][j] = b[i - 1][j - 1] - a[i - 1][j - 1] - a[i - 1][j] - a[i][j - 1];
    graph.clear(), graph.resize(n + m + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if ((i + j) & 1)
                graph[i].emplace_back(n + j, a[i][j]), graph[n + j].emplace_back(i, 1e6 - a[i][j]);
            else
                graph[n + j].emplace_back(i, a[i][j]), graph[i].emplace_back(n + j, 1e6 - a[i][j]);
    static queue<int> que;
    while (!que.empty()) que.pop();
    cnt[0] = 0;
    for (int i = 1; i <= n + m; i++)
        graph[0].emplace_back(i, 1e7), vis[i] = false, dist[i] = numeric_limits<int>::max(), cnt[i] = 0;
    que.push(0), dist[0] = 0;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        vis[p] = false;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) {
                dist[i.first] = dist[p] + i.second;
                if (++cnt[i.first] == n + m + 10) return puts("NO"), void();
                if (!vis[i.first]) vis[i.first] = true, que.push(i.first);
            }
    }
    puts("YES");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            write(((i + j) & 1) ? a[i][j] + dist[i] - dist[n + j] : a[i][j] - dist[i] + dist[n + j]), putchar(' ');
        putchar('\n');
    }
    return;
}

#ifdef MACESUTED
bool mem2;
#endif

int main() {
#ifndef MACESUTED
    // freopen("matrix.in", "r", stdin), freopen("matrix.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << " MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << " ms" << endl;
#endif

    return 0;
}