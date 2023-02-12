/**
 * @file lot.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    int tree[maxn << 2], n;
    multiset<int> S[maxn];

    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r) { return l > r ? 0 : query(1, 1, n, l, r); }
} ST1, ST2;

int a[maxn], b[maxn], siz[maxn], f[maxn], ans[maxn], dfni[maxn], dfno[maxn];
pii r[maxn];
bool ban[maxn];
vector<int> graph[maxn], rec;

pii findRoot(int p, int s, int pre = -1) {
    pii ans = {INT_MAX, 0};
    int maxs = 0;
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre && !ban[i]) ans = min(ans, findRoot(i, s, p)), maxs = max(maxs, siz[i]), siz[p] += siz[i];
    return min(ans, pii{max(maxs, s - siz[p]), p});
}
int dfnt;
void dfs1(int p, int pre = -1) {
    dfni[p] = ++dfnt, rec.push_back(p), siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre && !ban[i]) dfs1(i, p), siz[p] += siz[i];
    dfno[p] = dfnt;
    return;
}
void dfs2(int p, bool op, int pre = -1) {
    ST1.update(a[p], op * f[p]);
    for (auto i : graph[p])
        if (i != pre && !ban[i]) dfs2(i, op, p);
    return;
}
void dfs3(int p, int pre = -1) {
    int v = ST1.query(1, b[p]) + 1;
    ans[p] = max(ans[p], v), ST1.update(a[p], v);
    for (auto i : graph[p])
        if (i != pre && !ban[i]) dfs3(i, p);
    ST1.update(a[p], 0);
    return;
}
void solve(int p) {
    ban[p] = true;
    dfnt = 0, dfs1(p);
    sort(rec.begin(), rec.end(), [&](int x, int y) { return a[x] < a[y]; });
    int t = 0;
    for (auto i : rec) {
        while (a[rec[t]] <= b[i]) ST2.update(dfni[rec[t]], f[rec[t]]), t++;
        f[i] = ST2.query(dfni[i], dfno[i]) + 1;
    }
    for (int i = 0; i < t; i++) ST2.update(dfni[rec[i]], 0);
    ans[p] = max(ans[p], f[p]), rec.clear();
    for (auto i : graph[p])
        if (!ban[i]) dfs2(i, true);
    for (auto i : graph[p])
        if (!ban[i]) {
            dfs2(i, false);
            int v = ST1.query(1, b[p]) + 1;
            ST1.update(a[p], v);
            dfs3(i);
            ST1.update(a[p], 0);
            dfs2(i, true);
        }
    for (auto i : graph[p])
        if (!ban[i]) dfs2(i, false);
    for (auto i : graph[p])
        if (!ban[i]) solve(findRoot(i, siz[i]).second);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], r[i] = {a[i], i};
    sort(r + 1, r + n + 1, greater<pii>());
    for (int i = 1, l = 0; i <= n; i++) {
        if (r[i].first != r[i - 1].first) l = i - 1;
        a[r[i].second] = i, b[r[i].second] = l;
    }
    ST1.resize(n), ST2.resize(n);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    solve(findRoot(1, n).second);
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("lot.in", "r", stdin), freopen("lot.out", "w", stdout);
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