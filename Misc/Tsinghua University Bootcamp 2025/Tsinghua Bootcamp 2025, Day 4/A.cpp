/**
 * @file A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005

class SegmentTree {
   private:
    vector<int64_t> a, lef, rig;
    int n;

    void pushUp(int p) {
        a[p] = a[p << 1] + a[p << 1 | 1];
        lef[p] = max(lef[p << 1], a[p << 1] + lef[p << 1 | 1]);
        rig[p] = max(rig[p << 1] + a[p << 1 | 1], rig[p << 1 | 1]);
        return;
    }

    void upd(int p, int l, int r, int qp, int64_t v) {
        if (l == r) return a[p] = v, lef[p] = rig[p] = max((int64_t)0, v), void();
        int mid = (l + r) >> 1;
        qp <= mid ? upd(p << 1, l, mid, qp, v) : upd(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return a.resize((n = _n) << 2), lef.resize(n << 2), rig.resize(n << 2); }
    void upd(int p, int64_t v) { return upd(1, 1, n, p, v); }
    int64_t query(void) { return max(lef[1], rig[1]); }
};

int64_t a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];

    SegmentTree SGT;
    SGT.resize(n);
    for (int i = 1; i <= n; i++) SGT.upd(i, a[i] -= sum / n);

    while (q--) {
        int64_t u, v, x;
        cin >> u >> v >> x;
        SGT.upd(u, a[u] -= x), SGT.upd(v, a[v] += x);
        cout << SGT.query() << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}