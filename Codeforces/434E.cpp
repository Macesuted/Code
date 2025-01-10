/**
 * @file 434E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/extc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int64_t mod, base, tgt;

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int64_t a[maxn], f[maxn], g[maxn], pwb[maxn], ipwb[maxn];
bool vis[maxn];
int siz[maxn];
vector<int> graph[maxn];

__gnu_pbds::gp_hash_table<int, int> F, G;

void getSiz(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre && !vis[i]) getSiz(i, p), siz[p] += siz[i];
    return;
}
pii getRoot(int p, int tot, int pre = -1) {
    int maxs = tot - siz[p];
    pii ans = {INT_MAX, 0};
    for (auto i : graph[p])
        if (i != pre && !vis[i]) ans = min(ans, getRoot(i, tot, p)), maxs = max(maxs, siz[i]);
    return min(ans, {maxs, p});
}

void update(int p, int op, int64_t v1 = 0, int64_t v2 = 0, int l1 = 0, int l2 = 0, int pre = -1) {
    l1++, v1 = (v1 * base + a[p]) % mod;
    l2++, v2 = (v2 + a[p] * pwb[l2 - 1]) % mod;

    F[(tgt + mod - v1) * ipwb[l1] % mod] += op, G[v2] += op;

    for (auto i : graph[p])
        if (i != pre && !vis[i]) update(i, op, v1, v2, l1, l2, p);

    return;
}
void calc(int p, int64_t v1 = 0, int64_t v2 = 0, int l1 = 0, int l2 = 0, int pre = -1) {
    l1++, v1 = (v1 + a[p] * pwb[l1 - 1]) % mod;
    l2++, v2 = (v2 * base + a[p]) % mod;

    int64_t q1 = v1, q2 = (tgt + mod - v2) * ipwb[l2] % mod;
    if (F.find(q1) != F.end()) f[p] += F[q1];
    if (G.find(q2) != G.end()) g[p] += G[q2];

    for (auto i : graph[p])
        if (i != pre && !vis[i]) calc(i, v1, v2, l1, l2, p);

    return;
}

void dfs(int p) {
    getSiz(p), p = getRoot(p, siz[p]).second;
    vis[p] = true;

    update(p, +1);
    f[p] += F[0], g[p] += G[tgt];

    for (auto i : graph[p])
        if (!vis[i]) {
            update(i, -1, a[p], a[p], 1, 1);
            calc(i);
            update(i, +1, a[p], a[p], 1, 1);
        }

    F.clear(), G.clear();

    for (auto i : graph[p])
        if (!vis[i]) dfs(i);

    return;
}

void solve(void) {
    int n;
    cin >> n >> mod >> base >> tgt;

    pwb[0] = ipwb[0] = 1, ipwb[1] = inv(base);
    for (int i = 1; i <= n; i++) pwb[i] = pwb[i - 1] * base % mod, ipwb[i] = ipwb[i - 1] * ipwb[1] % mod;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    dfs(1);

    int64_t ans = (int64_t)n * n * n;
    for (int i = 1; i <= n; i++) ans -= f[i] * 3 * n;
    for (int i = 1; i <= n; i++) ans += f[i] * f[i] + f[i] * g[i] + g[i] * g[i];

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