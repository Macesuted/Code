/**
 * @file 696681L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

using pll = pair<int64_t, int64_t>;

class SegmentTree {
   private:
    pll a[maxn << 2];
    int n;

    pll merge(const pll& a, const pll& b) { return {a.first + b.first + a.second * b.second, a.second + b.second}; }
    void build(int p, int l, int r, int v[]) {
        if (l == r) return a[p] = {0, v[l]}, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, v), build(p << 1 | 1, mid + 1, r, v);
        return a[p] = merge(a[p << 1], a[p << 1 | 1]), void();
    }
    pll query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return a[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int v[]) { return build(1, 1, n, v); }
    pll query(int l, int r) { return query(1, 1, n, l, r); }
};

int v[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> v[i];

    SegmentTree SGT;
    SGT.resize(n), SGT.build(v);

    while (q--) {
        int l, r, S;
        cin >> l >> r >> S;
        pll res = SGT.query(l, r);
        cout << (res.second > S ? -1 : res.first + res.second * (S - res.second)) << endl;
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
