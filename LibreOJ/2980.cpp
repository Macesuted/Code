/**
 * @file 2980.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 250005
#define mod 998244353

int Mod(int x) { return x >= mod ? x - mod : x; }

class SegmentTree {
   private:
    struct Node {
        int64_t sum[3], d[3][4];  // d[0] * A + d[1] * B + d[2] * C + d[3] * len
        Node(void) { memset(sum, 0, sizeof(sum)), memset(d, 0, sizeof(d)), d[0][0] = d[1][1] = d[2][2] = 1; }
        Node operator+(const Node& o) const {
            Node ret;
            ret.sum[0] = Mod(sum[0] + o.sum[0]), ret.sum[1] = Mod(sum[1] + o.sum[1]),
            ret.sum[2] = Mod(sum[2] + o.sum[2]);
            return ret;
        }
    };

    Node tree[maxn << 2];
    int n;

    void plus(int64_t a[], int64_t b[], int64_t v) {
        a[0] = (a[0] + b[0] * v) % mod, a[1] = (a[1] + b[1] * v) % mod;
        a[2] = (a[2] + b[2] * v) % mod, a[3] = (a[3] + b[3] * v) % mod;
        return;
    }
    void plus(int p, int a, int b) {
        return tree[p].sum[a] = Mod(tree[p].sum[a] + tree[p].sum[b]), plus(tree[p].d[a], tree[p].d[b], 1);
    }
    void opA(int p, int len, int64_t v) {
        return tree[p].sum[0] = (tree[p].sum[0] + len * v) % mod, tree[p].d[0][3] = Mod(tree[p].d[0][3] + v), void();
    }
    void opB(int p, int64_t v) {
        return tree[p].sum[1] = tree[p].sum[1] * v % mod, plus(tree[p].d[1], tree[p].d[1], v - 1);
    }
    void opC(int p, int len, int64_t v) {
        tree[p].sum[2] = len * v % mod, tree[p].d[2][0] = tree[p].d[2][1] = tree[p].d[2][2] = 0, tree[p].d[2][3] = v;
        return;
    }
    void update(int p, int len, int64_t d[3][4]) {
        Node old = tree[p];
        memset(tree[p].d, 0, sizeof(tree[p].d));
        for (int i = 0; i < 3; i++) {
            tree[p].sum[i] = (tree[p].d[i][3] = d[i][3]) * len % mod;
            for (int j = 0; j < 3; j++)
                if (d[i][j])
                    tree[p].sum[i] = (tree[p].sum[i] + old.sum[j] * d[i][j]) % mod,
                    plus(tree[p].d[i], old.d[j], d[i][j]);
        }
        return;
    }
    void pushDown(int p, int l, int r) {
        int mid = (l + r) >> 1;
        update(p << 1, mid - l + 1, tree[p].d), update(p << 1 | 1, r - mid, tree[p].d);
        memset(tree[p].d, 0, sizeof(tree[p].d)), tree[p].d[0][0] = tree[p].d[1][1] = tree[p].d[2][2] = 1;
        return;
    }
    void pushUp(int p) { return tree[p] = tree[p << 1] + tree[p << 1 | 1], void(); }
    void build(int p, int l, int r, int a[], int b[], int c[]) {
        if (l == r) return tree[p].sum[0] = a[l], tree[p].sum[1] = b[l], tree[p].sum[2] = c[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a, b, c), build(p << 1 | 1, mid + 1, r, a, b, c);
        return pushUp(p);
    }
    void plus(int p, int l, int r, int ql, int qr, int a, int b) {
        if (ql <= l && r <= qr) return plus(p, a, b), void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) plus(p << 1, l, mid, ql, qr, a, b);
        if (qr > mid) plus(p << 1 | 1, mid + 1, r, ql, qr, a, b);
        return pushUp(p);
    }
    void opA(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return opA(p, r - l + 1, v);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) opA(p << 1, l, mid, ql, qr, v);
        if (qr > mid) opA(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    void opB(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return opB(p, v);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) opB(p << 1, l, mid, ql, qr, v);
        if (qr > mid) opB(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    void opC(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return opC(p, r - l + 1, v);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) opC(p << 1, l, mid, ql, qr, v);
        if (qr > mid) opC(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[], int b[], int c[]) { return build(1, 1, n, a, b, c); }
    void op1(int l, int r) { return plus(1, 1, n, l, r, 0, 1); }
    void op2(int l, int r) { return plus(1, 1, n, l, r, 1, 2); }
    void op3(int l, int r) { return plus(1, 1, n, l, r, 2, 0); }
    void op4(int l, int r, int v) { return opA(1, 1, n, l, r, v); }
    void op5(int l, int r, int v) { return opB(1, 1, n, l, r, v); }
    void op6(int l, int r, int v) { return opC(1, 1, n, l, r, v); }
    Node op7(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int a[maxn], b[maxn], c[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    ST.resize(n), ST.build(a, b, c);
    int q;
    cin >> q;
    while (q--) {
        int op, l, r, v;
        cin >> op >> l >> r;
        if (op == 1)
            ST.op1(l, r);
        else if (op == 2)
            ST.op2(l, r);
        else if (op == 3)
            ST.op3(l, r);
        else if (op == 4)
            cin >> v, ST.op4(l, r, v);
        else if (op == 5)
            cin >> v, ST.op5(l, r, v);
        else if (op == 6)
            cin >> v, ST.op6(l, r, v);
        else {
            auto ret = ST.op7(l, r);
            cout << ret.sum[0] << ' ' << ret.sum[1] << ' ' << ret.sum[2] << '\n';
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