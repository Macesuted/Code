/**
 * @file H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

int64_t a[maxn], f[maxn], siz[maxn];
vector<int> graph[maxn];

int64_t ans = INT64_MAX;

void dfs1(int p, int pre = -1) {
    siz[p] = a[p], f[p] = 0;
    vector<int64_t> rec;
    for (auto q : graph[p]) {
        if (q == pre) continue;
        dfs1(q, p), f[p] += f[q];
        rec.push_back(siz[q]);
    }
    sort(rec.begin(), rec.end());
    for (auto x : rec) f[p] += siz[p] += x;
    return;
}
void dfs2(int p, int pre = -1) {
    siz[p] = a[p], f[p] = 0;
    vector<int64_t> rec;
    for (auto q : graph[p]) rec.push_back(siz[q]), f[p] += f[q];
    sort(rec.begin(), rec.end());
    vector<int64_t> sum = rec;
    sum[0] += a[p];
    for (size_t i = 1; i < sum.size(); i++) sum[i] += sum[i - 1];
    siz[p] = sum.back();
    for (auto x : sum) f[p] += x;

    ans = min(ans, f[p]);

    for (auto q : graph[p]) {
        if (q == pre) continue;

        int it = lower_bound(rec.begin(), rec.end(), siz[q]) - rec.begin();
        int64_t of = f[p], osiz = siz[p];

        f[p] -= sum[it] + rec[it] * (rec.size() - it - 1) + f[q];
        siz[p] -= siz[q];

        dfs2(q, p);

        siz[p] = osiz;
        f[p] = of;
    }

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    dfs1(1);
    dfs2(1);

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
