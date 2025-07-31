/**
 * @file 108303G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

class SegmentTree {
   private:
    int64_t a[maxn << 2], laz[maxn << 2];
    int n;

    void pushDown(int p) {
        if (!laz[p]) return;
        a[p << 1] += laz[p], laz[p << 1] += laz[p];
        a[p << 1 | 1] += laz[p], laz[p << 1 | 1] += laz[p];
        laz[p] = 0;
        return;
    }
    void pushUp(int p) { return a[p] = max(a[p << 1], a[p << 1 | 1]), void(); }

    void update(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return a[p] += v, laz[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return a[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int64_t v) { return update(1, 1, n, l, r, v); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r); }
} SGT;

void solve(void) {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s, s = ' ' + s;

    set<int> L, R;
    SGT.resize(n);
    for (int i = 1; i <= n; i++)
        if (s[i] == 'L')
            SGT.update(1, i, +1), L.insert(i);
        else
            SGT.update(i, n, +1), R.insert(i);

    while (q--) {
        int x;
        cin >> x;
        if (s[x] == 'L')
            SGT.update(1, x, -1), SGT.update(x, n, +1), s[x] = 'R', L.erase(x), R.insert(x);
        else
            SGT.update(x, n, -1), SGT.update(1, x, +1), s[x] = 'L', R.erase(x), L.insert(x);

        if (L.empty() || R.empty() || *R.begin() > *L.rbegin()) {
            cout << 0 << endl;
            continue;
        }

        cout << SGT.query(*R.begin(), *L.rbegin()) - 1 << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
