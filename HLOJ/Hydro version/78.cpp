/**
 * @file 78.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-11
 *
 * @copyright Copyright (c) 2022
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

int mod;

map<int, int> graph[maxn];
vector<int> tree[maxn << 1];
int dfn[maxn], low[maxn], way[maxn << 1];
int64_t sum[maxn << 1], f[maxn << 1];

int dfnt = 0, tn;
stack<int> S;
void tarjan(int p) {
    dfn[p] = low[p] = ++dfnt, S.push(p);
    for (auto i : graph[p])
        if (!dfn[i.first]) {
            tarjan(i.first), low[p] = min(low[p], low[i.first]);
            if (low[i.first] == dfn[p]) {
                tree[p].push_back(++tn), way[tn] = 2;
                if (S.top() == i.first) sum[tn] -= i.second, way[tn] = 1;
                int last = p;
                while (S.top() != i.first)
                    tree[tn].push_back(S.top()), sum[tn] += graph[S.top()][last], last = S.top(), S.pop();
                tree[tn].push_back(S.top()), sum[tn] += graph[S.top()][last] + graph[p][S.top()], S.pop();
            }
        } else
            low[p] = min(low[p], dfn[i.first]);
    return;
}
void dfs1(int p) {
    for (auto i : tree[p]) dfs1(i), f[p] = (f[p] + f[i] * way[i]) % mod;
    return;
}
int64_t dfs2(int p, int pre = -1) {
    int64_t ans = 0;
    if (sum[p]) {
        int64_t fp = (f[p] + mod - f[pre]) % mod, tot = f[pre] * fp % mod;
        for (auto i : tree[p]) fp = (fp + mod - f[i]), tot = (tot + f[i] * fp) % mod;
        ans = tot * sum[p] % mod;
    }
    for (auto i : tree[p]) {
        f[p] = (f[p] + mod - f[i] * way[i] % mod) % mod, f[i] = (f[i] + f[p] * way[p]) % mod;
        ans = (ans + dfs2(i, p)) % mod;
        f[i] = (f[i] + mod - f[p] * way[p] % mod) % mod, f[p] = (f[p] + f[i] * way[i]) % mod;
    }
    return ans;
}

void solve(void) {
    int n, m;
    cin >> n >> m >> mod;
    for (int i = 1, x, y, c; i <= m; i++) cin >> x >> y >> c, graph[x][y] = graph[y][x] = c;
    tn = n, tarjan(1);
    for (int i = 1; i <= n; i++) way[i] = f[i] = 1;
    dfs1(1);
    cout << dfs2(1) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
#endif
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