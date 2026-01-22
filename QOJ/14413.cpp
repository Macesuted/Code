/**
 * @file 14413.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

using tlll = tuple<int64_t, int64_t, int64_t>;

class SegmentTree {
   private:
    tlll a[maxn << 2];
    int n;

    tlll merge(tlll a, tlll b) {
        int64_t g = gcd(get<2>(a), get<2>(b));

        vector<int64_t> vals = {get<0>(a), get<1>(a), get<0>(b), get<1>(b)};
        sort(vals.begin(), vals.end(), greater<int64_t>());
        vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

        while (vals.size() > 2) g = gcd(g, vals.back()), vals.pop_back();

        return {vals[0], vals[1], g};
    }

    void build(int p, int l, int r, int64_t v[]) {
        if (l == r) return a[p] = {v[l], 0, 0}, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, v), build(p << 1 | 1, mid + 1, r, v);
        return a[p] = merge(a[p << 1], a[p << 1 | 1]), void();
    }
    tlll query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return a[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int64_t v[]) { return build(1, 1, n, v); }
    int64_t query(int l, int r) {
        auto [x, y, g] = query(1, 1, n, l, r);
        return y ? max(x + gcd(y, g), y + gcd(x, g)) : 2 * x;
    }
} SGT;

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    SGT.resize(n), SGT.build(a);

    int q;
    cin >> q;
    for (int i = 1, l, r; i <= q; i++) cin >> l >> r, cout << SGT.query(l, r) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
