/**
 * @file 10119.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200'005

typedef pair<int64_t, int64_t> pll;
typedef tuple<int, int, int> tiii;

class SegmentTree1 {
   private:
    int64_t vmax[maxn << 2], laz[maxn << 2];
    int n;

    void pushDown(int p, int l, int r) {
        if (!laz[p]) return;
        int mid = (l + r) >> 1;
        vmax[p << 1] = vmax[p << 1 | 1] = laz[p];
        laz[p << 1] = laz[p << 1 | 1] = laz[p], laz[p] = 0;
        return;
    }
    void pushUp(int p) { return vmax[p] = max(vmax[p << 1], vmax[p << 1 | 1]), void(); }

    void update(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return laz[p] = vmax[p] = v, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return vmax[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int64_t v) { return update(1, 0, n, l, r, v); }
    int64_t query(int l, int r) { return query(1, 0, n, l, r); }
} ST;
class SegmentTree2 {
   private:
    int tree[maxn << 2], laz[maxn << 2], n;

    void pushUp(int p, int l, int r) { return tree[p] = (laz[p] ? r - l + 1 : tree[p << 1] + tree[p << 1 | 1]), void(); }

    void add(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            laz[p] += v;
            if (l == r)
                tree[p] = (laz[p] > 0);
            else
                pushUp(p, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p, l, r);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (laz[p]) return min(r, qr) - max(l, ql) + 1;
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void add(int l, int r, int v) { return add(1, 0, n, l, r, v); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
} GT;

unordered_map<int64_t, set<pll>> S[2];
map<int64_t, vector<tiii>> T;

void solve(void) {
    int n;
    cin >> n;

    S[1][0].emplace(0, 200'000);
    T[0].emplace_back(0, 200'000, +1), T[1].emplace_back(0, 200'000, -1);

    ST.resize(200'000);
    for (int i = 1; i <= n; i++) {
        int l, r, dh;
        cin >> l >> r >> dh;
        int64_t h = ST.query(l, r - 1);
        ST.update(l, r - 1, h + dh);
        S[0][l].emplace(h, h + dh), S[0][r].emplace(h, h + dh);
        S[1][h].emplace(l, r), S[1][h + dh].emplace(l, r);
        T[h].emplace_back(l, r, +1), T[h + 1].emplace_back(l, r, -1);
        T[h + dh].emplace_back(l, r, +1), T[h + dh + 1].emplace_back(l, r, -1);
        T[h].emplace_back(l, l, +1), T[h + dh + 1].emplace_back(l, l, -1);
        T[h].emplace_back(r, r, +1), T[h + dh + 1].emplace_back(r, r, -1);
    }

    int64_t ans = 1 - n;

    for (int t = 0; t < 2; t++)
        for (auto &[val, rec] : S[t])
            for (set<pll>::iterator p = rec.begin(), q; p != rec.end(); p = q) {
                q = next(p);
                int64_t mxr = p->second;
                while (q != rec.end() && q->first <= mxr) mxr = max(mxr, (q++)->second);
                ans += mxr - p->first;
            }

    GT.resize(200'000);
    for (auto p = T.begin(); p != T.end(); p++) {
        auto &[tim, rec] = *p;
        int64_t cont = (next(p) == T.end() ? 0 : next(p)->first - tim);
        for (auto [l, r, delt] : rec) GT.add(l, r, delt);
        ans -= cont * GT.query(0, 200'000);
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}