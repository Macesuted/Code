/**
 * @file 213.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-22
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

#define maxn 200005

int n, k, E, w[maxn], a[maxn], b[maxn], rig[maxn];

void insert(vector<int64_t> &f, int v, int w) {
    for (int i = k; i >= v; i--) f[i] = max(f[i], f[i - v] + w);
    return;
}

bool check(vector<int64_t> f, int l, int m, int r, int qp) {
    for (int i = l; i <= r; i++) insert(f, (i < m || i > qp) ? a[i] : b[i], w[i]);
    int64_t sum = 0;
    for (int i = 1; i <= k; i++) sum += f[i];
    return sum <= (int64_t)E * k;
}

void dfs(int l, int r, int ql, int qr, vector<int64_t> f) {
    if (l > r) return;
    auto g = f;
    int qm = (ql + qr) / 2, pl = l, pr = min(qm, r);
    for (int i = max(pr + 1, ql); i <= qr; i++) insert(f, i > qm ? a[i] : b[i], w[i]);
    pl--, pr++;
    while (pl + 1 < pr) {
        int pm = (pl + pr) / 2;
        if (check(f, max(pl, l), pm, min({pr, qm, r}), qm)) {
            for (int i = max(pl, l); i < pm; i++) insert(f, a[i], w[i]);
            pl = pm;
        } else {
            for (int i = pm + 1; i <= min({r, qm, pr}); i++) insert(f, b[i], w[i]);
            pr = pm;
        }
    }
    if (ql == qr) {
        for (int i = l; i <= pl; i++) rig[i] = ql;
        return;
    }
    f = g;
    for (int i = pl + 1; i <= min(r, ql - 1); i++) insert(f, b[i], w[i]);
    for (int i = qm + 1; i <= qr; i++) insert(f, a[i], w[i]);
    for (int i = l; i <= pl; i++) insert(g, a[i], w[i]);
    for (int i = max(r + 1, ql); i <= qm; i++) insert(g, b[i], w[i]);
    return dfs(l, pl, ql, qm, f), dfs(pl + 1, r, qm + 1, qr, g);
}

void solve(void) {
    cin >> n >> k >> E;
    for (int i = 1; i <= n; i++) cin >> w[i] >> a[i] >> b[i], rig[i] = n + 1;
    dfs(1, n, 1, n, vector<int64_t>(k + 1, 0));
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += n - rig[i] + 1;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("trad.in", "r", stdin), freopen("trad.out", "w", stdout);
#endif
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