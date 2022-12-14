/**
 * @file 3898.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#ifndef LOCAL
#define endl '\n'
#endif

#define maxn 500005
#define maxm 1000005
#define mod 1000000007
#define inv2 500000004

vector<int> graph[maxn], ngraph[maxn];
int dfn[maxn], low[maxn], bel[maxn], nsiz[maxn];
int64_t pow2[maxm], f[maxn];

stack<int> S;
int dfnt = 0, bcnt = 0;
void tarjan(int p, int pre = -1) {
    dfn[p] = low[p] = ++dfnt, S.push(p);
    for (auto i : graph[p]) {
        if (i == pre) continue;
        if (dfn[i])
            low[p] = min(low[p], dfn[i]);
        else
            tarjan(i, p), low[p] = min(low[p], low[i]);
    }
    if (dfn[p] == low[p]) {
        bcnt++;
        while (S.top() != p) nsiz[bel[S.top()] = bcnt]++, S.pop();
        nsiz[bel[S.top()] = bcnt]++, S.pop();
    }
    return;
}
int64_t ans = 0;
void dfs(int p, int pre = -1) {
    f[p] = 1;
    for (auto i : ngraph[p])
        if (i != pre) dfs(i, p), f[p] = f[p] * (1 + f[i] * inv2 % mod) % mod;
    ans = (ans + f[p] * pow2[nsiz[p]] - 1) % mod;
    for (auto i : ngraph[p])
        if (i != pre) ans = (ans + mod - f[i] * inv2 % mod) % mod;
    f[p] = (f[p] * pow2[nsiz[p]] - 1) % mod;
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    tarjan(1);
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (bel[i] != bel[j]) ngraph[bel[i]].push_back(bel[j]);
    dfs(1);
    cout << ans * pow2[m] % mod << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef LOCAL
    freopen("barrack.in", "r", stdin), freopen("barrack.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "MEMORY: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pow2[0] = 1;
    for (int i = 1; i < maxm; i++) pow2[i] = pow2[i - 1] * 2 % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "TIME: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
