/**
 * @file 6240.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-14
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

#define maxn 405
#define mod 998244353

vector<int> graph[maxn], tree[maxn << 1];
stack<int> S;
int n, tn, dfn[maxn], low[maxn], loc[maxn << 1][maxn], f[maxn << 1][maxn], dfnt = 0;
int64_t inv[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }
int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

void tarjan(int p) {
    dfn[p] = low[p] = ++dfnt, S.push(p);
    for (auto i : graph[p])
        if (!dfn[i]) {
            tarjan(i), low[p] = min(low[p], low[i]);
            if (low[i] == dfn[p]) {
                tree[p].push_back(++tn), tree[tn].push_back(p), loc[tn][p] = tree[tn].size();
                while (S.top() != i)
                    tree[S.top()].push_back(tn), tree[tn].push_back(S.top()), loc[tn][S.top()] = tree[tn].size(), S.pop();
                tree[i].push_back(tn), tree[tn].push_back(i), loc[tn][i] = tree[tn].size(), S.pop();
            }
        } else
            low[p] = min(low[p], dfn[i]);
    return;
}
void dfs(int p, int fa = -1) {
    if (p <= n) f[p][1] = 1;
    for (auto i : tree[p]) {
        if (i == fa) continue;
        dfs(i, p);
        if (p <= n)
            for (int j = 0; j <= n; j++) f[p][j] = Mod(f[p][j] + f[i][j]);
        else {
            int d1 = abs(loc[p][fa] - loc[p][i]), d2 = (int)tree[p].size() - d1, d3 = (int)tree[p].size() - 1;
            for (int j = 1; j + d1 <= n; j++) f[p][j + d1] = Mod(f[p][j + d1] + f[i][j]);
            for (int j = 1; j + d2 <= n; j++) f[p][j + d2] = Mod(f[p][j + d2] + f[i][j]);
            for (int j = 1; j + d3 <= n; j++) f[p][j + d3] = Mod(f[p][j + d3] + mod - f[i][j]);
        }
    }
    return;
}

void solve(void) {
    int m;
    cin >> n >> m, tn = n;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    tarjan(1);
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(f, 0, sizeof(f)), dfs(i);
        for (int j = 1; j <= n; j++) ans = (ans + f[i][j] * inv[j]) % mod;
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

    inv[0] = 1;
    for (int i = 1; i < maxn; i++) inv[i] = Inv(i);

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}