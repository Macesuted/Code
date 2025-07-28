/**
 * @file 6183.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

#define maxn 1000005
#define maxc 55

struct Node {
    int l, r, minv;
    Node(void) { l = r = 0, minv = 1e9; }
} a[10000005];
int pcnt = 1;
int newNode(void) { return a[pcnt] = Node(), pcnt++; }

class SegmentTree {
   private:
    int root;

    void pushUp(int p) {
        a[p].minv = 1e9;
        if (a[p].l) a[p].minv = min(a[p].minv, a[a[p].l].minv);
        if (a[p].r) a[p].minv = min(a[p].minv, a[a[p].r].minv);
        return;
    }

    void update(int &p, int l, int r, int x, int y) {
        if (!p) p = newNode();
        if (l == r) return a[p].minv = min(a[p].minv, y), void();
        int mid = (l + r) >> 1;
        x <= mid ? update(a[p].l, l, mid, x, y) : update(a[p].r, mid + 1, r, x, y);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (!p) return 1e9;
        if (ql <= l && r <= qr) return a[p].minv;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(a[p].l, l, mid, ql, qr);
        if (ql > mid) return query(a[p].r, mid + 1, r, ql, qr);
        return min(query(a[p].l, l, mid, ql, qr), query(a[p].r, mid + 1, r, ql, qr));
    }

   public:
    void reset(void) { root = newNode(); }
    void update(int x, int y) { return update(root, 1, 1e6, y, x); }
    bool query(int x, int yl, int yr) { return query(root, 1, 1e6, yl, yr) <= x; }
} SGT[maxc];

void solve(void) {
    int op;
    while (cin >> op) {
        if (op == 0) {
            pcnt = 1;
            for (int c = 0; c <= 50; c++) SGT[c].reset();
        } else if (op == 1) {
            int x, y, c;
            cin >> x >> y >> c;
            SGT[c].update(x, y);
        } else if (op == 2) {
            int x, yl, yr;
            cin >> x >> yl >> yr;
            int ans = 0;
            for (int c = 0; c <= 50; c++) ans += SGT[c].query(x, yl, yr);
            cout << ans << endl;
        } else
            return;
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