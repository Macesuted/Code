/**
 * @file 6705.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

#define maxn 50005

typedef pair<long long, int> pli;
typedef tuple<long long, int, vector<pli>::iterator> tlit;

vector<vector<pli>> graph;
priority_queue<tlit, vector<tlit>, greater<tlit>> que;
int ques[maxn];
long long answer[maxn];

void solve(void) {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    graph.clear(), graph.resize(n + 1);
    while (!que.empty()) que.pop();
    for (int i = 1, x, y, t; i <= m; i++) scanf("%d%d%d", &x, &y, &t), graph[x].emplace_back(t, y);
    for (int i = 1; i <= n; i++)
        if (!graph[i].empty()) sort(graph[i].begin(), graph[i].end()), que.emplace(graph[i].front().first, i, graph[i].begin());
    int maxq = 0;
    for (int i = 1; i <= q; i++) scanf("%d", ques + i), maxq = max(maxq, ques[i]);
    for (int i = 1; i <= maxq; i++) {
        answer[i] = get<0>(que.top());
        int p = get<1>(que.top());
        auto ptr = get<2>(que.top());
        que.pop();
        if (ptr + 1 != graph[p].end()) que.emplace(answer[i] - ptr->first + (ptr + 1)->first, p, ptr + 1);
        int q = ptr->second;
        if (!graph[q].empty()) que.emplace(answer[i] + graph[q].front().first, q, graph[q].begin());
    }
    for (int i = 1; i <= q; i++) printf("%lld\n", answer[ques[i]]);
    return;
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) solve();
    return 0;
}