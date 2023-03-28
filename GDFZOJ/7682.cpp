/**
 * @file 7682.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-27
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

#define maxn 100005
#define maxlgn 20

class SegmentTree {
   private:
    int64_t tree[maxn << 2], laz[maxn << 2];
    int n;

    void upd(int p, int s, int64_t v) { return tree[p] += s * v, laz[p] += v, void(); }
    void pushDown(int p, int l, int r) {
        if (!laz[p]) return;
        int mid = (l + r) >> 1;
        upd(p << 1, mid - l + 1, laz[p]), upd(p << 1 | 1, r - mid, laz[p]), laz[p] = 0;
        return;
    }
    void pushUp(int p) { return tree[p] = tree[p << 1] + tree[p << 1 | 1], void(); }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return upd(p, r - l + 1, v);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t getSum(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return getSum(p << 1, l, mid, ql, qr);
        if (ql > mid) return getSum(p << 1 | 1, mid + 1, r, ql, qr);
        return getSum(p << 1, l, mid, ql, qr) + getSum(p << 1 | 1, mid + 1, r, ql, qr);
    }
    int query(int p, int l, int r, int64_t lim) {
        if (l == r) return l;
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        return tree[p << 1] * 2 <= lim ? query(p << 1 | 1, mid + 1, r, lim - tree[p << 1] * 2) : query(p << 1, l, mid, lim);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    int64_t getSum(int l, int r) { return getSum(1, 1, n, l, r); }
    int query(int64_t lim) { return query(1, 1, n, lim); }
} ST;

vector<int> graph[maxn];
int fa[maxn][maxlgn], dep[maxn], top[maxn], siz[maxn], son[maxn], id[maxn], dfni[maxn], dfno[maxn];

void dfs1(int p, int pre = 0) {
    dep[p] = dep[fa[p][0] = pre] + (siz[p] = 1);
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p])
        if (i != pre) {
            dfs1(i, p), siz[p] += siz[i];
            if (siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int top_) {
    top[p] = top_;
    id[dfni[p] = ++dfnt] = p;
    if (son[p]) dfs2(son[p], top_);
    for (auto i : graph[p])
        if (i != fa[p][0] && i != son[p]) dfs2(i, i);
    return dfno[p] = dfnt, void();
}

void solve(void) {
    int n, q;
    cin >> n, ST.resize(n);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1), dfs2(1, 1);
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, z;
            cin >> x >> z;
            ST.update(dfni[x], dfno[x], z);
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ST.update(dfni[top[x]], dfni[x], z), x = fa[top[x]][0];
            }
            if (dep[x] < dep[y]) swap(x, y);
            ST.update(dfni[y], dfni[x], z);
        }
        int64_t sum = ST.getSum(1, n);
        int p = id[ST.query(sum)];
        if (2 * ST.getSum(dfni[p], dfno[p]) > sum) {
            cout << p << endl;
            continue;
        }
        for (int i = maxlgn - 1; ~i; i--)
            if (fa[p][i] && 2 * ST.getSum(dfni[fa[p][i]], dfno[fa[p][i]]) <= sum) p = fa[p][i];
        cout << fa[p][0] << endl;
    }
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