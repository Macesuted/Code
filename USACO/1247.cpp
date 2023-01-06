/**
 * @file 1247.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-17
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

#define maxn 100005

typedef pair<int, int> pii;

vector<vector<int>> graph;
int deg[maxn], op[maxn], v[maxn], fa[maxn], siz[maxn];
bool avai[maxn];
set<pii> S;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
void merge(int x, int y) {
    int fx = getfa(x), fy = getfa(y);
    if (fx == fy) return;
    siz[fx] += siz[fy], fa[fy] = fx;
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m, graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x), deg[x]++, deg[y]++;
    for (int i = 1; i <= n; i++) S.emplace(deg[i], i), avai[i] = true, siz[i] = 1, fa[i] = i;
    for (int i = 1; i <= n; i++) {
        tie(v[i], op[i]) = *S.begin();
        S.erase(S.begin()), avai[op[i]] = false;
        for (auto i : graph[op[i]])
            if (avai[i]) S.erase({deg[i], i}), S.insert({--deg[i], i});
    }
    int64_t ans = 0;
    int maxs = 1;
    for (int i = n; i; i--) {
        avai[op[i]] = true;
        for (auto j : graph[op[i]])
            if (avai[j]) merge(op[i], j);
        ans = max(ans, int64_t(maxs = max(maxs, siz[getfa(op[i])])) * v[i]);
    }
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