/**
 * @file 12721.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

class SegmentTree1 {
   private:
    struct Node {
        int sum[2], ans, lazy, len;
        bool col;
        Node operator+(const Node& o) const {
            Node ret;
            bool r = len & 1;
            ret.sum[0] = sum[0] + o.sum[r], ret.sum[1] = sum[1] + o.sum[!r];
            ret.ans = ans + o.ans, ret.lazy = -1, ret.len = len + o.len;
            return ret;
        }
    };

    Node tree[maxn << 2];
    int n;

    void upd(int p, bool v) { return tree[p].lazy = tree[p].col = v, tree[p].ans = tree[p].sum[v], void(); }
    void pushDown(int p) {
        if (!~tree[p].lazy) return;
        upd(p << 1, tree[p].lazy), upd(p << 1 | 1, tree[p].lazy ^ (tree[p << 1].len & 1)), tree[p].lazy = -1;
        return;
    }
    void build(int p, int l, int r, int a[]) {
        if (l == r)
            return tree[p].sum[0] = 0, tree[p].sum[1] = a[l], tree[p].ans = 0, tree[p].lazy = -1, tree[p].len = 1,
                   void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int ql, int qr, bool v) {
        if (ql == l && r == qr) return upd(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid)
            update(p << 1, l, mid, ql, qr, v);
        else if (ql > mid)
            update(p << 1 | 1, mid + 1, r, ql, qr, v);
        else
            update(p << 1, l, mid, ql, mid, v), update(p << 1 | 1, mid + 1, r, mid + 1, qr, v ^ ((mid - ql + 1) & 1));
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].ans = v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql == l && r == qr) return tree[p].ans;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, mid) + query(p << 1 | 1, mid + 1, r, mid + 1, qr);
    }
    bool getCol(int p, int l, int r, int qp) {
        if (l == r) return tree[p].col;
        int mid = (l + r) >> 1;
        return qp <= mid ? getCol(p << 1, l, mid, qp) : getCol(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    void update(int l, int r, bool v) { return update(1, 1, n, l, r, v); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
    bool getCol(int p) { return getCol(1, 1, n, p); }
} ST1, ST2;

vector<int> graph[maxn];
int fa[maxn], top[maxn], siz[maxn], son[maxn], dfni[maxn], dfno[maxn], a[maxn], dif[maxn];

void dfs1(int p) {
    siz[p] = 1;
    for (auto i : graph[p]) {
        dfs1(i), siz[p] += siz[i];
        if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
    }
    return;
}
int dfnt = 0;
void dfs2(int p, int top_) {
    dfni[p] = ++dfnt, top[p] = top_;
    if (son[p]) dfs2(son[p], top_);
    for (auto i : graph[p])
        if (i != son[p]) dfs2(i, i);
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> fa[i], graph[fa[i]].push_back(i);
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++) a[i] = 1;
    ST1.resize(n), ST1.build(a);
    for (int i = 1; i <= n; i++) a[dfni[i]] = (int)graph[i].size() - 1;
    ST2.resize(n), ST2.build(a);
    int q;
    cin >> q;
    while (q--) {
        int op, p;
        cin >> op >> p;
        if (op == 1) {
            bool v = true;
            if (!graph[p].empty()) ST1.update(dfni[p], 1), ST2.update(dfni[p], a[dfni[p]]);
            while (p) {
                if (p != top[p]) {
                    v ^= (dfni[p] - dfni[top[p]] - 1) & 1;
                    ST1.update(dfni[top[p]], dfni[p] - 1, v), ST2.update(dfni[top[p]], dfni[p] - 1, !v);
                    v ^= true, p = top[p];
                }
                if (fa[p]) {
                    if (v)
                        ST1.update(dfni[fa[p]], 0), ST2.update(dfni[fa[p]], dfni[fa[p]], false),
                            ST2.update(dfni[fa[p]], 1);
                    if (!v)
                        ST1.update(dfni[fa[p]], 1), ST2.update(dfni[fa[p]], dfni[fa[p]], true),
                            ST2.update(dfni[fa[p]], a[dfni[fa[p]]] - 1);
                    dif[fa[p]] = p;
                }
                v ^= true, p = fa[p];
            }
        } else if (op == 2) {
            int ans = 0;
            while (p) {
                if (p != top[p]) ans += ST1.query(dfni[top[p]], dfni[p] - 1);
                p = top[p];
                if (fa[p]) {
                    int ret = ST2.query(dfni[fa[p]], dfni[fa[p]]);
                    bool c = ST2.getCol(dfni[fa[p]]);
                    ans += ((ret == 1 && !c && dif[fa[p]] == p) ||
                            (ret == a[dfni[fa[p]]] - 1 && c && dif[fa[p]] && dif[fa[p]] != p) || ret == a[dfni[fa[p]]]);
                }
                p = fa[p];
            }
            cout << ans << endl;
        } else
            cout << ST1.query(dfni[p], dfno[p]) + ST2.query(dfni[p], dfno[p]) << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("chain.in", "r", stdin), freopen("chain.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
