/**
 * @file 7463.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005
#define endl '\n'

typedef pair<int64_t, int64_t> pll;

class SegmentTree {
   private:
    int64_t vl[maxn << 2], vr[maxn << 2];
    int n;

    void pushUp(int p) { return vl[p] = min(vl[p << 1], vl[p << 1 | 1]), vr[p] = max(vr[p << 1], vr[p << 1 | 1]), void(); }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return vl[p] = vr[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return vl[p] += v, vr[p] += v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    pll query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return {vl[p], vr[p]};
        int mid = (l + r) >> 1;
        int64_t vl = INT64_MAX, vr = INT64_MIN;
        if (ql <= mid) {
            auto [x, y] = query(p << 1, l, mid, ql, qr);
            vl = min(vl, x), vr = max(vr, y);
        }
        if (qr > mid) {
            auto [x, y] = query(p << 1 | 1, mid + 1, r, ql, qr);
            vl = min(vl, x), vr = max(vr, y);
        }
        return {vl, vr};
    }
    int findPos(int p, int l, int r, int ql, int qr) {
        if (vl[p] >= 0) return -1;
        if (l == r) return (vl[p] < 0 ? l : -1);
        int mid = (l + r) >> 1;
        if (qr <= mid) return findPos(p << 1, l, mid, ql, qr);
        if (ql > mid) return findPos(p << 1 | 1, mid + 1, r, ql, qr);
        int x = findPos(p << 1, l, mid, ql, qr);
        if (x != -1) return x;
        return findPos(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    pll query(int l, int r) { return query(1, 1, n, l, r); }
    int findPos(int l, int r) { return findPos(1, 1, n, l, r); }
} ST;

int a[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i; i--) a[i] = a[i] - a[i - 1];

    ST.resize(n + 1), ST.build(a);

    int q;
    cin >> q;

    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int x;
            cin >> x;
            ST.update(l, +x), ST.update(r + 1, -x);
        } else if (op == 2) {
            if (l == r) {
                cout << 1 << endl;
                continue;
            }
            pll ret = ST.query(l + 1, r);
            cout << (ret.first == 0 && ret.second == 0) << endl;
        } else if (op == 3) {
            if (l == r) {
                cout << 1 << endl;
                continue;
            }
            pll ret = ST.query(l + 1, r);
            cout << (ret.first > 0) << endl;
        } else if (op == 4) {
            if (l == r) {
                cout << 1 << endl;
                continue;
            }
            pll ret = ST.query(l + 1, r);
            cout << (ret.second < 0) << endl;
        } else {
            int p = ST.findPos(l + 2, r);
            if (p == -1) {
                cout << 0 << endl;
                continue;
            }
            pll ret1 = ST.query(l + 1, p - 1), ret2 = ST.query(p, r);
            cout << (ret1.first > 0 && ret2.second < 0) << endl;
        }
    }

    return 0;
}
