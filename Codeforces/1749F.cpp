/**
 * @file 1749F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-20
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
#define maxlgn 22

class SegmentTree {
   private:
    int tree[maxn << 2];

    void pushDown(int p) { return tree[p << 1] += tree[p], tree[p << 1 | 1] += tree[p], tree[p] = 0, void(); }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return tree[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    int query(int p, int l, int r, int qp) {
        if (l == r) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    void update(int l, int r, int v) { return update(1, 1, maxn - 1, l, r, v); }
    int query(int p) { return query(1, 1, maxn - 1, p); }
} ST[maxlgn];

vector<int> graph[maxn];
int dfni[maxn], fa[maxn], dep[maxn], top[maxn], son[maxn], siz[maxn];

int dfnt = 0;
void dfs1(int p, int pre = 0) {
    fa[p] = pre, dep[p] = dep[pre] + 1, siz[p] = 1;
    for (auto i : graph[p])
        if (pre != i) {
            dfs1(i, p), siz[p] += siz[i];
            if (siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
void dfs2(int p, int _top) {
    top[p] = _top, dfni[p] = ++dfnt;
    if (son[p]) dfs2(son[p], _top);
    for (auto i : graph[p])
        if (i != fa[p] && i != son[p]) dfs2(i, i);
    return;
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1), dfs2(1, 1);
    int m;
    cin >> m;
    while (m--) {
        int op, x, y, k, d;
        cin >> op >> x;
        if (op == 1) {
            int ans = 0;
            for (int i = 0, p = x; i < maxlgn && p; i++, p = fa[p]) ans += ST[i].query(dfni[p]);
            cout << ans << endl;
        } else {
            cin >> y >> k >> d;
            int t = LCA(x, y);
            while (top[x] != top[t]) ST[d].update(dfni[top[x]], dfni[x], +k), x = fa[top[x]];
            if (x != t) ST[d].update(dfni[t] + 1, dfni[x], +k);
            while (top[y] != top[t]) ST[d].update(dfni[top[y]], dfni[y], +k), y = fa[top[y]];
            if (y != t) ST[d].update(dfni[t] + 1, dfni[y], +k);
            for (int i = d, p = t; ~i; i--) {
                ST[i].update(dfni[p], dfni[p], +k);
                if (fa[p] && i) ST[i - 1].update(dfni[p], dfni[p], +k), p = fa[p];
            }
        }
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