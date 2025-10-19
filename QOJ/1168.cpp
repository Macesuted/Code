/**
 * @file 1168.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

class BaseSet {
   private:
    uint32_t base[32];

   public:
    BaseSet() { memset(base, 0, sizeof(base)); }

    void insert(uint32_t v) {
        for (int i = 29; ~i; i--) {
            if (!(v >> i & 1)) continue;
            if (base[i])
                v ^= base[i];
            else {
                base[i] = v;
                break;
            }
        }
        return;
    }

    uint32_t getMax(uint32_t v) {
        for (int i = 29; ~i; i--)
            if (!(v >> i & 1) && base[i]) v ^= base[i];
        return v;
    }

    uint32_t getMin(uint32_t v) {
        for (int i = 29; ~i; i--)
            if ((v >> i & 1) && base[i]) v ^= base[i];
        return v;
    }
} BS;

multiset<pii> graph[maxn];
tiii que[maxn];
uint32_t dep[maxn], ans[maxn], f[maxn], g[maxn];
bool vis[maxn];

void dfs(int p) {
    vis[p] = true;
    while (!graph[p].empty()) {
        auto [q, w] = *graph[p].begin();
        graph[p].erase(graph[p].begin());
        if (p != q) graph[q].erase(graph[q].find({p, w}));

        if (vis[q])
            BS.insert(w ^ dep[p] ^ dep[q]);
        else
            dep[q] = dep[p] ^ w, dfs(q);
    }

    return;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, graph[u].emplace(v, w), graph[v].emplace(u, w);

    dfs(1);

    for (int i = 1; i <= n; i++) f[i] = BS.getMax(dep[i]), g[i] = BS.getMin(dep[i]);

    for (int i = 1, l, r; i <= q; i++) cin >> l >> r, que[i] = {l, r, i};

    int B = sqrt(n);
    sort(que + 1, que + q + 1, [B](const tiii &a, const tiii &b) -> bool {
        int abel = get<0>(a) / B, bbel = get<0>(b) / B;
        if (abel != bbel) return abel < bbel;
        return (abel & 1) ^ (get<1>(a) < get<1>(b));
    });

    int L = 1, R = 0, cnt = 0;
    uint32_t gSum = 0, tot = 0;

    auto insert = [&](int p) -> void {
        if ((cnt++) & 1) tot ^= f[p];
        tot ^= gSum, gSum ^= g[p];
        return;
    };

    auto erase = [&](int p) -> void {
        gSum ^= g[p], tot ^= gSum;
        if ((--cnt) & 1) tot ^= f[p];
        return;
    };

    for (int i = 1; i <= q; i++) {
        auto [l, r, id] = que[i];
        while (L > l) insert(--L);
        while (R < r) insert(++R);
        while (L < l) erase(L++);
        while (R > r) erase(R--);
        ans[id] = tot;
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
