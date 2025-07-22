/**
 * @file 101808L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
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

class SegmentTree {
   private:
    vector<int64_t> sum, ans, laz;
    int n;

    void pushDown(int p) {
        if (!laz[p]) return;
        ans[p << 1] += sum[p << 1] * laz[p], ans[p << 1 | 1] += sum[p << 1 | 1] * laz[p];
        laz[p << 1] += laz[p], laz[p << 1 | 1] += laz[p], laz[p] = 0;
        return;
    }

    void build(int p, int l, int r, int a[]) {
        if (l == r) return sum[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return sum[p] = sum[p << 1] + sum[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return ans[p] += sum[p], laz[p]++, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        return ans[p] = ans[p << 1] + ans[p << 1 | 1], void();
    }
    int64_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return ans[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void build(int _n, int a[]) {
        n = _n;
        sum.resize(n << 2), ans.resize(n << 2), laz.resize(n << 2);
        return build(1, 1, n, a);
    }
    void update(int l, int r) { return update(1, 1, n, l, r); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r); }
};

int v[maxn], a[maxn], fa[maxn], son[maxn], siz[maxn], dep[maxn], dfni[maxn], top[maxn];
vector<vector<int>> graph;

void dfs1(int p) {
    siz[p] = 1, son[p] = 0, dep[p] = dep[fa[p]] + 1;
    for (auto q : graph[p]) {
        dfs1(q), siz[p] += siz[q];
        if (!son[p] || siz[q] > siz[son[p]]) son[p] = q;
    }
    v[p] -= v[fa[p]];
    return;
}
int dfnt;
void dfs2(int p, int t) {
    dfni[p] = ++dfnt;
    top[p] = t;
    if (son[p]) dfs2(son[p], t);
    for (auto q : graph[p])
        if (q != son[p]) dfs2(q, q);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    v[0] = 0;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i <= n; i++) cin >> fa[i], graph[fa[i]].push_back(i);

    dfs1(1), dfnt = 0, dfs2(1, 1);

    for (int i = 1; i <= n; i++) a[dfni[i]] = v[i];
    SegmentTree SGT;
    SGT.build(n, a);

    for (int i = 1; i <= n; i++) {
        int64_t ans = 0;
        int p = i;
        while (p) ans += SGT.query(dfni[top[p]], dfni[p]), SGT.update(dfni[top[p]], dfni[p]), p = fa[top[p]];
        if (i > 1) cout << ans << ' ';
    }
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}