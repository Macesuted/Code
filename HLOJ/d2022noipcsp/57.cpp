/**
 * @file 57.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
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

#define maxn 100005
#define mod 95542721

int Mod(int x) { return x >= mod ? x - mod : x; }

class SegmentTree {
   private:
    int tree[maxn << 2][48], laz[maxn << 2], n;

    void upd(int p, int v) {
        laz[p] = (laz[p] + v) % 48;
        for (int i = 0; i < 48; i++) tree[0][i] = tree[p][i];
        for (int i = 0; i < 48; i++) tree[p][i] = tree[0][(i + v) % 48];
        return;
    }
    void pushDown(int p) {
        if (!laz[p]) return;
        return upd(p << 1, laz[p]), upd(p << 1 | 1, laz[p]), laz[p] = 0, void();
    }
    void pushUp(int p) {
        for (int i = 0; i < 48; i++) tree[p][i] = Mod(tree[p << 1][i] + tree[p << 1 | 1][i]);
        return;
    }
    void build(int p, int l, int r, int a[]) {
        if (l == r) {
            tree[p][0] = a[l];
            for (int i = 1; i < 48; i++) tree[p][i] = (int64_t)tree[p][i - 1] * tree[p][i - 1] % mod * tree[p][i - 1] % mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return upd(p, 1);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p][0];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return Mod(query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void build(int _n, int a[]) { return build(1, 1, n = _n, a); }
    void update(int l, int r) { return update(1, 1, n, l, r); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int a[maxn];

void solve(void) {
    int n, label, q;
    cin >> n >> label;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ST.build(n, a);
    cin >> q;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
            cout << ST.query(l, r) << endl;
        else
            ST.update(l, r);
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("cube.in", "r", stdin), freopen("cube.out", "w", stdout);
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