/**
 * @file game.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-29
 *
 * @copyright Copyright (c) 2022
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define maxlgn 20

int a[maxn], b[maxn], r1l[maxn], r1s[maxn], r2l[maxn], r2s[maxn], r0[maxn], cl[maxn], cs[maxn];

class SegmentTree {
   private:
    int maxv[maxn << 2], n;

    void pushUp(int p) {
        return maxv[p] = max(maxv[p << 1], maxv[p << 1 | 1]), void();
    }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return maxv[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return maxv[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} R1L, R1S, R2L, R2S, R0, CL, CS;

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) r1l[i] = r1s[i] = r2l[i] = r2s[i] = r0[i] = INT_MIN;
    for (int i = 1; i <= m; i++) cl[i] = cs[i] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 0) r1l[i] = a[i], r1s[i] = -a[i];
        if (a[i] == 0) r0[i] = 1;
        if (a[i] < 0) r2l[i] = a[i], r2s[i] = -a[i];
    }
    for (int i = 1; i <= m; i++) cin >> b[i], cl[i] = b[i], cs[i] = -b[i];
    R1L.resize(n), R1L.build(r1l);
    R1S.resize(n), R1S.build(r1s);
    R2L.resize(n), R2L.build(r2l);
    R2S.resize(n), R2S.build(r2s);
    R0.resize(n), R0.build(r0);
    CL.resize(m), CL.build(cl);
    CS.resize(m), CS.build(cs);
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        int64_t ans = INT64_MIN, lB = -CS.query(l2, r2), rB = CL.query(l2, r2);
        if (R0.query(l1, r1) == 1) ans = max(ans, (int64_t)0);
        if (R1L.query(l1, r1) != INT_MIN) {
            if (lB > 0)
                ans = max(ans, lB * R1L.query(l1, r1));
            else
                ans = max(ans, lB * -R1S.query(l1, r1));
        }
        if (R2L.query(l1, r1) != INT_MIN) {
            if (rB > 0)
                ans = max(ans, rB * R2L.query(l1, r1));
            else
                ans = max(ans, rB * -R2S.query(l1, r1));
        }
        cout << ans << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
   freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}