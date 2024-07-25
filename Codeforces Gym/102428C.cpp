/**
 * @file 102428C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

class SegmentTree {
   private:
    struct Node {
        int vl, vr, delt;
    };

    Node tree[maxn << 2];
    int n;

    void pushUp(int p) {
        int pl = tree[p << 1 | 1].vl - tree[p << 1].delt, pr = tree[p << 1 | 1].vr - tree[p << 1].delt;
        tree[p].delt = tree[p << 1].delt + tree[p << 1 | 1].delt;
        if (tree[p << 1].vl > pr) return tree[p].vl = tree[p].vr = pr, void();
        if (tree[p << 1].vr < pl) return tree[p].vl = tree[p].vr = pl, void();
        tree[p].vl = max(tree[p << 1].vl, pl), tree[p].vr = min(tree[p << 1].vr, pr);
        return;
    }
    void build(int p, int l, int r, int vl, int vr, int a[]) {
        if (l == r) {
            if (a[l] > 0)
                a[l] = min(a[l], vr - vl);
            else
                a[l] = max(a[l], vl - vr);
            tree[p].vl = vl, tree[p].vr = vr, tree[p].delt = a[l];
            if (a[l] > 0)
                tree[p].vr -= a[l];
            else
                tree[p].vl -= a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, vl, vr, a), build(p << 1 | 1, mid + 1, r, vl, vr, a);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return min(max(v, tree[p].vl), tree[p].vr) + tree[p].delt;
        int mid = (l + r) >> 1;
        if (ql <= mid) v = query(p << 1, l, mid, ql, qr, v);
        if (qr > mid) v = query(p << 1 | 1, mid + 1, r, ql, qr, v);
        return v;
    }
    void print(int p, int l, int r) {
        cerr << "# " << p << ' ' << l << ' ' << r << endl;
        cerr << tree[p].vl << ' ' << tree[p].vr << ' ' << tree[p].delt << endl;
        if (l == r) return;
        int mid = (l + r) >> 1;
        print(p << 1, l, mid), print(p << 1 | 1, mid + 1, r);
        return;
    }

   public:
    void build(int n_, int vl, int vr, int a[]) { return build(1, 1, n = n_, vl, vr, a); }
    int query(int l, int r, int v) { return query(1, 1, n, l, r, v); }
    void print(void) { return print(1, 1, n); }
} ST;

int a[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n, vl, vr;
    cin >> n >> vl >> vr;
    for (int i = 1; i <= n; i++) cin >> a[i];

    ST.build(n, vl, vr, a);

    // ST.print();

    int q;
    cin >> q;
    while (q--) {
        int l, r, v;
        cin >> l >> r >> v;
        cout << ST.query(l, r, v) << endl;
    }

    return 0;
}