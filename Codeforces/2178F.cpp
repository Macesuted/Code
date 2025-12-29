/**
 * @file 2178F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005
#define mod 998244353

vector<vector<int>> graph;
int siz[maxn];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

void dfs(int p, int pre = -1) {
    siz[p] = 1;
    for (auto q : graph[p])
        if (q != pre) dfs(q, p), siz[p] += (siz[q] & 1) ? siz[q] : 0;
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    dfs(1);

    vector<int> S;
    for (int i = 2; i <= n; i++)
        if (!(siz[i] & 1)) S.push_back(siz[i]);

    if (S.empty()) return cout << 1 << endl, void();

    int64_t ans = 0, mul = 1;
    for (auto s : S) mul = mul * s % mod;
    mul = mul * mul % mod * siz[1] % mod;

    for (auto s : S) ans = (ans + mul * inv(s)) % mod;

    for (int i = 1; i < (int)S.size(); i++) ans = ans * i % mod;

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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
