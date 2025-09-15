/**
 * @file 11375.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-13
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

#define maxn 100005

class SegmentTree {
   private:
    int vl[maxn << 2], vr[maxn << 2], minv[maxn << 2];
    bool chk[maxn << 2];
    int n;

    void pushUp(int p) {
        vl[p] = vl[p << 1], vr[p] = vr[p << 1 | 1], minv[p] = min(minv[p << 1], minv[p << 1 | 1]);
        chk[p] = chk[p << 1] && chk[p << 1 | 1] && vr[p << 1] < vl[p << 1 | 1] && minv[p] >= 1;
        return;
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return vl[p] = vr[p] = minv[p] = v, chk[p] = v >= 1, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int query(int p, int l, int r) {
        if (chk[p]) return l;
        if (l == r) return r + 1;
        int mid = (l + r) >> 1, ret = query(p << 1 | 1, mid + 1, r);
        if (ret > mid + 1 || vr[p << 1] > vl[p << 1 | 1]) return ret;
        return query(p << 1, l, mid);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(void) { return n - query(1, 1, n) + 2; }
} SGT;

int a[maxn], pos[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;

    pos[0] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;

    SGT.resize(n);
    for (int i = 1; i <= n; i++) SGT.update(i, pos[a[i] - 1]);

    cout << SGT.query() << endl;

    while (q--) {
        int x, y;
        cin >> x >> y;

        if (a[x] < n) SGT.update(pos[a[x] + 1], y);
        if (a[y] < n) SGT.update(pos[a[y] + 1], x);
        swap(a[x], a[y]), pos[a[x]] = x, pos[a[y]] = y;
        SGT.update(x, pos[a[x] - 1]), SGT.update(y, pos[a[y] - 1]);

        cout << SGT.query() << endl;
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