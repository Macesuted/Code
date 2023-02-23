/**
 * @file 545.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int l[maxn], r[maxn];

class SegmentTree {
   private:
    int val[maxn << 2], laz[maxn << 2], n;

    void pushDown(int p) {
        if (!laz[p]) return;
        val[p << 1] += laz[p], val[p << 1 | 1] += laz[p], laz[p << 1] += laz[p], laz[p << 1 | 1] += laz[p], laz[p] = 0;
        return;
    }
    void pushUp(int p) { return val[p] = min(val[p << 1], val[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return val[p] += v, laz[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int qr) {
        if (qr >= r) return val[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, qr);
        return min(query(p << 1, l, mid, qr), query(p << 1 | 1, mid + 1, r, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int v) { return l > r ? void() : update(1, 1, n, l, r, v); }
    int query(int r) { return r < 1 ? 1e8 : query(1, 1, n, r); }
} ST;

void solve(void) {
    int n, m;
    cin >> n >> m, ST.resize(n);
    for (int i = 1; i <= n; i++) l[i] = r[i] = i;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        if (x > y) swap(x, y);
        l[y] = min(l[y], x), r[x] = max(r[x], y);
    }
    for (int i = 2, j = 1; i <= n; i++) {
        while (j < i && r[j] <= i) j++;
        ST.update(1, l[i] - 1, 1), ST.update(i, i, ST.query(j - 1));
    }
    cout << ST.query(n) << endl;
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