/**
 * @file 3290.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-06
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

#define maxn 250005

class SegmentTree {
   private:
    int tree[maxn << 2];
    int n;

    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return tree[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }
    int findPosL(int p, int l, int r, int qr, int v) {
        if (r <= qr) {
            if (tree[p] <= v) return 0;
            if (l == r) return l;
        }
        if (l == r) return 0;
        int mid = (l + r) >> 1, ret = (mid + 1 > qr ? 0 : findPosL(p << 1 | 1, mid + 1, r, qr, v));
        if (ret) return ret;
        return findPosL(p << 1, l, mid, qr, v);
    }
    int findPosR(int p, int l, int r, int ql, int v) {
        if (ql <= l) {
            if (tree[p] <= v) return 0;
            if (l == r) return l;
        }
        if (l == r) return 0;
        int mid = (l + r) >> 1, ret = (mid < ql ? 0 : findPosR(p << 1, l, mid, ql, v));
        if (ret) return ret;
        return findPosR(p << 1 | 1, mid + 1, r, ql, v);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
    int findPosL(int qr, int v) { return findPosL(1, 1, n, qr, v); }
    int findPosR(int ql, int v) { return findPosR(1, 1, n, ql, v); }
} ST;

int a[maxn], pos[15];

void solve(void) {
    int n, m, q;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (n - a[i] + 1 <= 10) pos[n - a[i] + 1] = i;
    }
    cin >> q;
    int rp = n + 1;
    ST.resize(n), ST.build(a);
    while (q--) {
        char op;
        cin >> op;
        if (op == 'E') {
            int p, v;
            cin >> p >> v, rp++;
            for (int i = 1; i < v; i++) ST.update(pos[i], a[pos[i]] = rp - i);
            int r = 9;
            for (int i = v; i < 10; i++)
                if (pos[i] == p) r = i - 1;
            for (int i = r; i >= v; i--) pos[i + 1] = pos[i];
            ST.update(pos[v] = p, a[p] = rp - v);
        } else {
            int p;
            cin >> p;
            if (p == m)
                cout << 0 << endl;
            else if (p < m) {
                if (m == n) {
                    cout << n - p << endl;
                    continue;
                }
                int pos = ST.findPosR(m + 1, ST.query(p, m - 1));
                cout << (!pos ? n - p : pos - 1 - p) << endl;
            } else {
                if (m == 1) {
                    cout << p - 1 << endl;
                    continue;
                }
                int pos = ST.findPosL(m - 1, ST.query(m + 1, p));
                cout << (!pos ? p - 1 : p - 1 - pos) << endl;
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