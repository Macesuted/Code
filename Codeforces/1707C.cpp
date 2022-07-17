/**
 * @file 1707C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-16
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

int fa[maxn], dfni[maxn], dfno[maxn], f[maxn], dep[maxn], g[20][maxn];

vector<int> graph[maxn];
vector<pii> edges;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

int dfnt = 0;
void dfs1(int p, int pre = 0) {
    dfni[p] = ++dfnt;
    dep[p] = dep[pre] + 1;
    g[0][p] = pre;
    for (int i = 1; i < 20; i++) g[i][p] = g[i - 1][g[i - 1][p]];
    for (auto i : graph[p])
        if (i != pre) dfs1(i, p);
    dfno[p] = dfnt;
    return;
}
int jmp(int x, int y) {
    for (int i = 19; ~i; i--)
        if (dep[g[i][y]] > dep[x]) y = g[i][y];
    return y;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        if (getfa(x) == getfa(y))
            edges.emplace_back(x, y);
        else
            graph[x].push_back(y), graph[y].push_back(x), fa[getfa(x)] = getfa(y);
    }
    dfs1(1);
    for (auto i : edges) {
        int x = i.first, y = i.second;
        if (dfni[x] > dfni[y]) swap(x, y);
        if (dfni[y] <= dfno[x]) {
            int t = jmp(x, y);
            f[dfni[t]]++, f[dfni[y]]--, f[dfno[y] + 1]++, f[dfno[t] + 1]--;
        } else
            f[1]++, f[dfni[x]]--, f[dfno[x] + 1]++, f[dfni[y]]--, f[dfno[y] + 1]++;
    }
    for (int i = 1; i <= n; i++) f[i] += f[i - 1];
    for (int i = 1; i <= n; i++) cout << (f[dfni[i]] == 0);
    cout << endl;
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