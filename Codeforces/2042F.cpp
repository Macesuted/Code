/**
 * @file 2042F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-02
 *
 * @copyright Copyright (c) 2024
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
    struct Node {
        int64_t l0, r0, rl0, v1, l1, r1, v2, lazl, lazr;

        Node(void) = default;
        Node(int64_t vl, int64_t vr) { l0 = vl, r0 = vr, v1 = vl + vr, rl0 = l1 = r1 = v2 = -1e18, lazl = lazr = 0; }

        friend Node operator+(const Node& a, const Node& b) {
            Node ans;
            ans.l0 = max(a.l0, b.l0);
            ans.r0 = max(a.r0, b.r0);
            ans.rl0 = max({a.rl0, b.rl0, a.r0 + b.l0});
            ans.v1 = max({a.v1, b.v1, a.l0 + b.r0});
            ans.l1 = max({a.l1, b.l1, a.v1 + b.l0, a.l0 + b.rl0});
            ans.r1 = max({a.r1, b.r1, a.r0 + b.v1, a.rl0 + b.r0});
            ans.v2 = max({a.v2, b.v2, a.l0 + b.r1, a.v1 + b.v1, a.l1 + b.r0});
            ans.lazl = ans.lazr = 0;
            return ans;
        }
    };

    Node tree[maxn << 2];
    int n;

    void updateAl(int p, int64_t delt) {
        tree[p].lazl += delt;
        if (tree[p].l0 != -1e18) tree[p].l0 += delt;
        if (tree[p].rl0 != -1e18) tree[p].rl0 += delt;
        if (tree[p].v1 != -1e18) tree[p].v1 += delt;
        if (tree[p].l1 != -1e18) tree[p].l1 += 2 * delt;
        if (tree[p].r1 != -1e18) tree[p].r1 += delt;
        if (tree[p].v2 != -1e18) tree[p].v2 += 2 * delt;
        return;
    }
    void updateAr(int p, int64_t delt) {
        tree[p].lazr += delt;
        if (tree[p].r0 != -1e18) tree[p].r0 += delt;
        if (tree[p].rl0 != -1e18) tree[p].rl0 += delt;
        if (tree[p].v1 != -1e18) tree[p].v1 += delt;
        if (tree[p].l1 != -1e18) tree[p].l1 += delt;
        if (tree[p].r1 != -1e18) tree[p].r1 += 2 * delt;
        if (tree[p].v2 != -1e18) tree[p].v2 += 2 * delt;
        return;
    }
    void pushDown(int p) {
        if (tree[p].lazl) updateAl(p << 1, tree[p].lazl), updateAl(p << 1 | 1, tree[p].lazl), tree[p].lazl = 0;
        if (tree[p].lazr) updateAr(p << 1, tree[p].lazr), updateAr(p << 1 | 1, tree[p].lazr), tree[p].lazr = 0;
        return;
    }
    void build(int p, int l, int r, int64_t a[], int64_t b[]) {
        if (l == r) return tree[p] = Node(b[l] - a[l - 1], b[l] + a[l]), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a, b), build(p << 1 | 1, mid + 1, r, a, b);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void updateAl(int p, int l, int r, int ql, int qr, int64_t delt) {
        if (ql <= l && r <= qr) return updateAl(p, delt);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) updateAl(p << 1, l, mid, ql, qr, delt);
        if (qr > mid) updateAl(p << 1 | 1, mid + 1, r, ql, qr, delt);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void updateAr(int p, int l, int r, int ql, int qr, int64_t delt) {
        if (ql <= l && r <= qr) return updateAr(p, delt);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) updateAr(p << 1, l, mid, ql, qr, delt);
        if (qr > mid) updateAr(p << 1 | 1, mid + 1, r, ql, qr, delt);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void updateB(int p, int l, int r, int qp, int64_t delt) {
        if (l == r) return tree[p].l0 += delt, tree[p].v1 += 2 * delt, tree[p].r0 += delt, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? updateB(p << 1, l, mid, qp, delt) : updateB(p << 1 | 1, mid + 1, r, qp, delt);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int64_t a[], int64_t b[]) { return build(1, 1, n, a, b); }
    void updateA(int p, int64_t delt) {
        if (p < n) updateAl(1, 1, n, p + 1, n, -delt);
        updateAr(1, 1, n, p, n, delt);
        return;
    }
    void updateB(int p, int64_t delt) { return updateB(1, 1, n, p, delt); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r).v2; }
} SGT;

int64_t a[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;
    SGT.resize(n);
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
    for (int i = 1; i <= n; i++) cin >> b[i];
    SGT.build(a, b);
    for (int i = n; i; i--) a[i] -= a[i - 1];

    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p, x;
            cin >> p >> x;
            SGT.updateA(p, x - a[p]), a[p] = x;
        } else if (op == 2) {
            int p, x;
            cin >> p >> x;
            SGT.updateB(p, x - b[p]), b[p] = x;
        } else {
            int l, r;
            cin >> l >> r;
            cout << SGT.query(l, r) << endl;
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