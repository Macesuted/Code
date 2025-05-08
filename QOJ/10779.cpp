/**
 * @file 10779.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 10005
#define maxm 1000005

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

class SegmentTree {
   private:
    struct Node {
        bool enable, all;
        int lc, ll, lr, rc, rl, rr, ans;

        friend Node operator+(const Node& a, const Node& b) {
            if (!a.enable) return b;
            if (!b.enable) return a;

            Node ans;
            ans.enable = true;
            ans.all = a.all && b.all && a.lc == b.lc;
            ans.lc = a.lc, ans.ll = a.ll, ans.lr = a.lr;
            ans.rc = b.rc, ans.rl = b.rl, ans.rr = b.rr;
            ans.ans = max(a.ans, b.ans);

            if (a.all && a.lc == b.lc) ans.lr = b.lr;
            if (b.all && a.rc == b.rc) ans.rl = a.rl;
            if (a.rc == b.lc) ans.ans = max(ans.ans, b.lr - a.rl);
            ans.ans = max({ans.ans, a.lr - a.ll, b.rr - b.rl});

            return ans;
        }
    };

    Node tree[maxn << 2];
    int n;

    void build(int p, int l, int r, tiii a[]) {
        if (l == r) {
            tree[p].enable = false, tree[p].all = true;
            tree[p].ll = tree[p].lr = tree[p].rl = tree[p].rr = get<0>(a[l]);
            tree[p].lc = tree[p].rc = get<1>(a[l]);
            tree[p].ans = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void set(int p, int l, int r, int qp, bool stat) {
        if (l == r) return tree[p].enable = stat, void();
        int mid = (l + r) >> 1;
        qp <= mid ? set(p << 1, l, mid, qp, stat) : set(p << 1 | 1, mid + 1, r, qp, stat);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(tiii a[]) { return build(1, 1, n, a); }
    void set(int p, bool stat) { return set(1, 1, n, p, stat); }
    int query(void) { return tree[1].ans; }
} SGT;

int rk[maxn], ans[maxm];
tiii val[maxn];
tiii ques[maxm];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> get<1>(val[i]);
    for (int i = 1; i <= n; i++) cin >> get<0>(val[i]), get<2>(val[i]) = i;

    sort(val + 1, val + n + 1);
    SGT.resize(n), SGT.build(val);

    for (int i = 1; i <= n; i++) rk[get<2>(val[i])] = i;

    int q;
    cin >> q;
    for (int i = 1, l, r; i <= q; i++) cin >> l >> r, ques[i] = {l, r, i};

    int B = 10;
    sort(ques + 1, ques + q + 1, [&](const tiii& x, const tiii& y) {
        return get<0>(x) / B == get<0>(y) / B ? ((get<0>(x) / B % 2 == 0) ^ (get<1>(x) < get<1>(y)))
                                              : get<0>(x) / B < get<0>(y) / B;
    });

    int l = 1, r = 0;
    for (int i = 1; i <= q; i++) {
        auto [ql, qr, id] = ques[i];
        while (l > ql) SGT.set(rk[--l], true);
        while (r < qr) SGT.set(rk[++r], true);
        while (l < ql) SGT.set(rk[l++], false);
        while (r > qr) SGT.set(rk[r--], false);
        ans[id] = SGT.query();
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
