/**
 * @file 3148.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-31
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

class Frac {
   private:
    int64_t x, y;

   public:
    Frac(int64_t x_ = 0, int64_t y_ = 1) { x = x_, y = y_, sim(); }
    Frac operator+(const Frac& o) const { return Frac(this->x * o.y + o.x * this->y, this->y * o.y); }
    void sim(void) {
        int64_t g = __gcd(x, y);
        return x /= g, y /= g, void();
    }
    void print(void) { return cout << x << '/' << y << endl, void(); }
};

class SegmentTree {
   private:
    struct Node {
        int64_t cnt0, cnt1, cnt01, cnt10, cnt11, cnt011, cnt110;
        int laz;
        Node(void) { cnt0 = cnt1 = cnt01 = cnt10 = cnt11 = cnt011 = cnt110 = 0, laz = -1; }
    };

    Node tree[maxn << 2];
    int n;

    void set0(int p, int l, int r) {
        return tree[p].cnt0 = r - l + 1,
               tree[p].cnt1 = tree[p].cnt01 = tree[p].cnt10 = tree[p].cnt11 = tree[p].cnt011 = tree[p].cnt110 = 0,
               tree[p].laz = 0, void();
    }
    void set1(int p, int l, int r) {
        return tree[p].cnt1 = r - l + 1, tree[p].cnt11 = int64_t(r - l + 1) * (r - l) / 2,
               tree[p].cnt0 = tree[p].cnt01 = tree[p].cnt10 = tree[p].cnt011 = tree[p].cnt110 = 0, tree[p].laz = 1,
               void();
    }
    void pushDown(int p, int l, int r) {
        if (!~tree[p].laz) return;
        int mid = (l + r) >> 1;
        tree[p].laz == 0 ? (set0(p << 1, l, mid), set0(p << 1 | 1, mid + 1, r))
                         : (set1(p << 1, l, mid), set1(p << 1 | 1, mid + 1, r));
        return tree[p].laz = -1, void();
    }
    void pushUp(int p) {
        tree[p].cnt0 = tree[p << 1].cnt0 + tree[p << 1 | 1].cnt0;
        tree[p].cnt1 = tree[p << 1].cnt1 + tree[p << 1 | 1].cnt1;
        tree[p].cnt01 = tree[p << 1].cnt01 + tree[p << 1].cnt0 * tree[p << 1 | 1].cnt1 + tree[p << 1 | 1].cnt01;
        tree[p].cnt10 = tree[p << 1].cnt10 + tree[p << 1].cnt1 * tree[p << 1 | 1].cnt0 + tree[p << 1 | 1].cnt10;
        tree[p].cnt11 = tree[p << 1].cnt11 + tree[p << 1].cnt1 * tree[p << 1 | 1].cnt1 + tree[p << 1 | 1].cnt11;
        tree[p].cnt011 = tree[p << 1].cnt011 + tree[p << 1].cnt01 * tree[p << 1 | 1].cnt1 +
                         tree[p << 1].cnt0 * tree[p << 1 | 1].cnt11 + tree[p << 1 | 1].cnt011;
        tree[p].cnt110 = tree[p << 1].cnt110 + tree[p << 1].cnt11 * tree[p << 1 | 1].cnt0 +
                         tree[p << 1].cnt1 * tree[p << 1 | 1].cnt10 + tree[p << 1 | 1].cnt110;
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) return (l & 1) ? tree[p].cnt1++ : tree[p].cnt0++, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return v == 0 ? set0(p, l, r) : set1(p, l, r);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    Node query(void) { return tree[1]; }
} ST;

void solve(void) {
    int64_t n, m, t;
    cin >> n >> m, t = n / 2;
    if (n & 1)
        Frac(7 * t * t + t, 12).print(), Frac(54 * t * t * t + 55 * t * t - 29 * t, 360).print();
    else
        Frac(7 * t * t - t, 12).print(), Frac(54 * t * t * t + 13 * t * t + 23 * t, 360).print();
    ST.resize(n), ST.build();
    while (m--) {
        int l, r, v;
        cin >> l >> r >> v, ST.update(l, r, v);
        auto ret = ST.query();
        (Frac(ret.cnt0 * (ret.cnt0 - 1) / 2, 2) + Frac(ret.cnt01 + ret.cnt10 + ret.cnt011 + ret.cnt110, ret.cnt1 + 1))
            .print();
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