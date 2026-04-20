/**
 * @file 2219C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

vector<vector<int>> graph;
string s;
bool mark[maxn], vis[maxn];
double f[maxn], g[maxn];

bool dfs1(int p, int pre = -1) {
    mark[p] = vis[p] = (s[p] == '1');
    for (auto q : graph[p])
        if (q != pre) mark[p] |= dfs1(q, p);
    return mark[p];
}

void dfs2(int p, int pre = -1) {
    vis[p] = true, f[p] = g[p] = 0;

    double sum = 0;
    vector<double> rec;

    for (auto q : graph[p])
        if (mark[q] && q != pre) {
            if (!vis[q])
                dfs2(q, p), sum += g[q], rec.push_back(f[q] - g[q]);
            else
                rec.push_back(0);
        }

    sort(rec.begin(), rec.end());

    f[p] = numeric_limits<double>::max(), g[p] = sum + graph[p].size();
    for (size_t i = 0; i < rec.size(); i++) {
        sum += rec[i];
        f[p] = min(f[p], sum + 1. * graph[p].size() / (i + 1));
        g[p] = min(g[p], sum + 1. * graph[p].size() / (i + 2));
    }

    return;
}

void solve(void) {
    int n;
    cin >> n >> s, s = ' ' + s;

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    int root = 1;
    while (s[root] == '0') root++;

    dfs1(root);

    double ans = 0;

    for (int i = 1; i <= n; i++) {
        if (!mark[i] || vis[i]) continue;
        dfs2(i);
        ans += f[i];
    }

    for (int i = 1; i <= n; i++)
        if (!mark[i]) ans += graph[i].size();

    cout << fixed << setprecision(20) << ans << endl;

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
