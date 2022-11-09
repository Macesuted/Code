/**
 * @file 269.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 300005

vector<int> graph[maxn], tree[maxn], blk[maxn];
int64_t val[maxn];
int dfn[maxn], low[maxn], bel[maxn], indeg[maxn], topo[maxn];
stack<int> S;
priority_queue<int, vector<int>, less<int>> out;

int dfnt = 0, bcnt = 0;
void tarjan(int p) {
    dfn[p] = low[p] = ++dfnt, S.push(p);
    for (auto i : graph[p])
        if (!dfn[i])
            tarjan(i), low[p] = min(low[p], low[i]);
        else if (!bel[i])
            low[p] = min(low[p], dfn[i]);
    if (low[p] == dfn[p]) {
        bcnt++;
        while (S.top() != p) blk[bel[S.top()] = bcnt].push_back(S.top()), S.pop();
        blk[bel[S.top()] = bcnt].push_back(S.top()), S.pop();
    }
    return;
}

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1, x, y, w; i <= m; i++)
        cin >> x >> y >> w, graph[x].push_back(y), w = (k - w % k) % k, val[x] += w, val[y] -= w;
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (bel[i] != bel[j]) tree[bel[i]].push_back(bel[j]), indeg[bel[j]]++;
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= bcnt; i++)
        if (!indeg[i]) que.push(i);
    int cnt = 0;
    while (!que.empty()) {
        int p = topo[++cnt] = que.front();
        que.pop();
        for (auto i : tree[p])
            if (!--indeg[i]) que.push(i);
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += max((int64_t)0, val[i]);
    for (int i = 1; i <= bcnt; i++) {
        vector<int> buf;
        for (auto j : blk[topo[i]]) {
            while (val[j] > 0) buf.push_back(min((int64_t)k, val[j])), val[j] = max((int64_t)0, val[j] - k);
            while (val[j] < 0) out.push(-max((int64_t)0, val[j] + k)), val[j] = min((int64_t)0, val[j] + k);
        }
        for (auto v : buf)
            if (!out.empty() && out.top() + v > 0) ans -= out.top() + v, out.pop(), out.push(-v);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}