/**
 * @file 14431.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-04
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

#define maxn 300005

class UnionSet {
   private:
    int fa[maxn];

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

   public:
    void resize(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
        return;
    }
    void merge(int p, int q) { return fa[getfa(p)] = getfa(q), void(); }
    bool isSame(int p, int q) { return getfa(p) == getfa(q); }
};

int64_t ans = 0;

class SegmentTree {
   private:
    UnionSet US;

    vector<int> a[maxn << 2];
    bool merged[maxn << 2];
    int n;

    void insert(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return a[p].push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }

    void merge(int p, int l, int r, int qp, int v, int blk = 0) {
        if (!merged[p]) {
            for (size_t i = 1; i < a[p].size(); i++)
                if (!US.isSame(a[p][0], a[p][i])) ans += v, US.merge(a[p][0], a[p][i]);
            merged[p] = true;
        }
        if (!a[p].empty()) {
            if (blk && !US.isSame(blk, a[p][0])) ans += v, US.merge(blk, a[p][0]);
            blk = a[p][0];
        }
        if (l == r) return;
        int mid = (l + r) >> 1;
        return qp <= mid ? merge(p << 1, l, mid, qp, v, blk) : merge(p << 1 | 1, mid + 1, r, qp, v, blk);
    }

   public:
    void resize(int _n, int m) { return n = _n, US.resize(m); }
    void insert(int l, int r, int v) { return l <= r ? insert(1, 1, n, l, r, v) : void(); }
    void merge(int p, int v) { return merge(1, 1, n, p, v); }
} SGT;

int p[maxn], tp[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i], tp[p[i]] = i;
    tp[n] = n + 1;

    SGT.resize(n + 1, m);
    for (int i = 1, l, r; i <= m; i++) cin >> l >> r, SGT.insert(1, l - 1, i), SGT.insert(r + 1, n + 1, i);

    for (int i = 0; i <= n; i++) SGT.merge(tp[i], i);

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
