/**
 * @file 115023L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-30
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

#define maxn 200005

using tlll = tuple<int64_t, int64_t, int64_t>;

int64_t pow2(int x) { return x < 30 ? (1 << x) : 1e9; }

tlll operator+(const tlll& a, const tlll& b) {
    auto [val, rest, len] = a;
    tlll ans = b;

    if (val >= get<1>(ans)) {
        get<0>(ans)++, val -= get<1>(ans), get<1>(ans) = pow2(get<2>(ans));
        get<0>(ans) += val / get<1>(ans), val %= get<1>(ans);
    }
    get<1>(ans) -= val;
    get<1>(ans) = min(rest + (get<1>(ans) - 1) * pow2(len), int64_t(1e9));
    get<2>(ans) += len;

    return ans;
}

class SegmentTree {
   private:
    tlll a[maxn << 2];
    int n;

    void build(int p, int l, int r, int v[]) {
        if (l == r) return a[p] = {v[l] / 2 + v[l] % 2, v[l] % 2 + 1, 1}, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, v), build(p << 1 | 1, mid + 1, r, v);
        return a[p] = a[p << 1] + a[p << 1 | 1], void();
    }
    tlll query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return a[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int v[]) { return build(1, 1, n, v); }
    tlll query(int l, int r) { return query(1, 1, n, l, r); }
} SGT;

int a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    SGT.resize(n), SGT.build(a);

    while (q--) {
        int x, y;
        cin >> x >> y, y = n - y + 1;

        int p = upper_bound(a + 1, a + n + 1, x) - a;

        if (y < p) {
            cout << 0 << endl;
            continue;
        }

        tlll ret = SGT.query(p, y);
        ret = tlll{x, 1, 0} + ret;
        cout << get<0>(ret) - x << endl;
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