/**
 * @file 10867.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 250005

class SegmentTree {
   private:
    int a[maxn << 2], n;

    void pushDown(int p) {
        if (!a[p]) return;
        a[p << 1] = max(a[p << 1], a[p]), a[p << 1 | 1] = max(a[p << 1 | 1], a[p]);
        a[p] = 0;
        return;
    }
    void insert(int p, int l, int r, int qp) {
        if (l == r) return a[p] = 0, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        return qp <= mid ? insert(p << 1, l, mid, qp) : insert(p << 1 | 1, mid + 1, r, qp);
    }
    int erase(int p, int l, int r, int qp) {
        if (l == r) return a[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        return qp <= mid ? erase(p << 1, l, mid, qp) : erase(p << 1 | 1, mid + 1, r, qp);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return a[p] = max(a[p], v), void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int p) { return insert(1, 1, n, p); }
    int erase(int p) { return erase(1, 1, n, p); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
} SGT;

int a[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], siz[maxn], dfni[maxn], ans[maxn];
vector<int> t1[maxn], t2[maxn];

void dfs1(int p, int pre = 0) {
    siz[p] = 1, fa[p] = pre;
    for (auto q : t2[p])
        if (q != pre) {
            dep[q] = dep[p] + 1, dfs1(q, p), siz[p] += siz[q];
            if (!son[p] || siz[q] > siz[son[p]]) son[p] = q;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int t) {
    dfni[p] = ++dfnt, top[p] = t;
    if (son[p]) dfs2(son[p], t);
    for (auto q : t2[p])
        if (q != son[p] && q != fa[p]) dfs2(q, q);
    return;
}
void dfs3(int p, int pre = 0) {
    SGT.insert(dfni[p]);

    int x = p;
    while (top[x] != 1) SGT.update(dfni[top[x]], dfni[x], a[p]), x = fa[top[x]];
    SGT.update(1, dfni[x], a[p]);

    for (auto q : t1[p])
        if (q != pre) dfs3(q, p);

    ans[p] = SGT.erase(dfni[p]);

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, t1[x].push_back(y), t1[y].push_back(x);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, t2[x].push_back(y), t2[y].push_back(x);

    dfs1(1);
    dfs2(1, 1);

    SGT.resize(n);

    dfs3(1);

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}