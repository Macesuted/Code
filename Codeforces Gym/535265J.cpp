/**
 * @file 535265J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

typedef pair<int, int64_t> pii;

class SegmentTree {
   private:
    struct Node {
        int limL, limR, delta;
        int64_t dist;
    };

    Node tree[maxn << 2];
    int n, xL, xR;

    void build(int p, int l, int r, int a[]) {
        if (l == r) {
            tree[p].limL = xL, tree[p].limR = xR;
            if (a[l] > 0) a[l] = min(a[l], xR - xL);
            if (a[l] < 0) a[l] = max(a[l], xL - xR);
            tree[p].delta = a[l], tree[p].dist = abs(a[l]);
            if (a[l] > 0) tree[p].limR -= a[l];
            if (a[l] < 0) tree[p].limL -= a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        tree[p] = tree[p << 1];
        int pl = tree[p].limL + tree[p].delta, pr = tree[p].limR + tree[p].delta;
        tree[p].delta += tree[p << 1 | 1].delta, tree[p].dist += tree[p << 1 | 1].dist;
        if (pl > tree[p << 1 | 1].limR)
            return tree[p].limR = tree[p].limL, tree[p].delta += tree[p << 1 | 1].limR - pl,
                   tree[p].dist -= (pl - tree[p << 1 | 1].limR), void();
        if (pr < tree[p << 1 | 1].limL)
            return tree[p].limL = tree[p].limR, tree[p].delta += tree[p << 1 | 1].limL - pr,
                   tree[p].dist -= (tree[p << 1 | 1].limL - pr), void();
        if (tree[p << 1 | 1].limL > pl) tree[p].limL += tree[p << 1 | 1].limL - pl;
        if (tree[p << 1 | 1].limR < pr) tree[p].limR -= pr - tree[p << 1 | 1].limR;
        return;
    }
    pii query(int p, int l, int r, int ql, int qr, int qv) {
        if (ql <= l && r <= qr) {
            if (qv < tree[p].limL) return {tree[p].limL + tree[p].delta, tree[p].dist - (tree[p].limL - qv)};
            if (qv > tree[p].limR) return {tree[p].limR + tree[p].delta, tree[p].dist - (qv - tree[p].limR)};
            return {qv + tree[p].delta, tree[p].dist};
        }
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr, qv);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr, qv);
        pii ret1 = query(p << 1, l, mid, ql, qr, qv), ret2 = query(p << 1 | 1, mid + 1, r, ql, qr, ret1.first);
        return {ret2.first, ret1.second + ret2.second};
    }

    void print(int p, int l, int r) {
        cerr << '[' << l << ',' << r << ']' << endl;
        cerr << tree[p].limL << ' ' << tree[p].limR << ' ' << tree[p].delta << ' ' << tree[p].dist << endl;
        if (l == r) return;
        int mid = (l + r) >> 1;
        print(p << 1, l, mid), print(p << 1 | 1, mid + 1, r);
        return;
    }

   public:
    void buildd(int n_, int xL_, int xR_, int a[]) { return xL = xL_, xR = xR_, build(1, 1, n = n_, a); }
    pii query(int l, int r, int v) { return query(1, 1, n, l, r, v); }

    void print(void) { return print(1, 1, n); }
} ST[2];

int delt[2][maxn];

int main() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= k; i++) {
        char c;
        int v;
        cin >> c >> v;
        if (c == 'L') delt[0][i] = -v;
        if (c == 'R') delt[0][i] = +v;
        if (c == 'U') delt[1][i] = +v;
        if (c == 'D') delt[1][i] = -v;
    }
    ST[0].buildd(k, 0, n, delt[0]), ST[1].buildd(k, 0, m, delt[1]);
    while (q--) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        pii ret1 = ST[0].query(l, r, x), ret2 = ST[1].query(l, r, y);
        cout << ret1.first << ' ' << ret2.first << ' ' << ret1.second + ret2.second << endl;
    }
    return 0;
}