/**
 * @file 1707D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-17
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

#define maxn 2005

int n, mod;

vector<int> graph[maxn];
int64_t f[maxn][maxn], g[maxn][maxn], v[maxn], lef[maxn], rig[maxn], ans[maxn], binom[maxn][maxn];

void dfs(int p, int pre = 0) {
    vector<int> G;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p), G.push_back(i), v[i] = 1;
    int tn = G.size();
    for (int t = 1; t < n; t++) {
        int64_t mul = 1;
        for (auto i : G) mul = mul * g[i][t - (pre == 0)] % mod;
        f[p][t] = (f[p][t] + mul) % mod;
        if (G.empty() || !pre) continue;
        for (auto i : G) f[p][t] = (f[p][t] + f[i][t] * v[i]) % mod;
        if (G.size() > 1) {
            lef[G[0]] = g[G[0]][t], rig[G[tn - 1]] = g[G[tn - 1]][t];
            for (int i = 1; i < tn; i++) lef[G[i]] = lef[G[i - 1]] * g[G[i]][t] % mod;
            for (int i = tn - 2; ~i; i--) rig[G[i]] = rig[G[i + 1]] * g[G[i]][t] % mod;
            v[G[0]] = (v[G[0]] + rig[G[1]]) % mod, v[G[tn - 1]] = (v[G[tn - 1]] + lef[G[tn - 2]]) % mod;
            for (int i = 1; i < tn - 1; i++) v[G[i]] = (v[G[i]] + lef[G[i - 1]] * rig[G[i + 1]]) % mod;
        } else
            v[G[0]] = (v[G[0]] + 1) % mod;
    }
    f[p][0] = g[p][0] = 1;
    for (int i = 1; i < n; i++) g[p][i] = (g[p][i - 1] + f[p][i]) % mod;
    return;
}

void solve(void) {
    cin >> n >> mod;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 0; i < maxn; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }
    dfs(1);
    for (int i = 1; i < n; i++) {
        ans[i] = f[1][i];
        for (int j = 1; j < i; j++) ans[i] = (ans[i] + mod - binom[i][j] * ans[j] % mod) % mod;
    }
    for (int i = 1; i < n; i++) cout << ans[i] << ' ';
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