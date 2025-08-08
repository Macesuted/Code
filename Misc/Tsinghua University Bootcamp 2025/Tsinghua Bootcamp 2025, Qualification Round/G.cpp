/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-06-29
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

using pii = pair<int, int>;

int pa[maxn], pb[maxn], qa[maxn], qb[maxn];

class SegmentTree {
   private:
    int64_t val[maxn << 2], laz[maxn << 2];
    int n;

    void pushDown(int p) {
        if (!laz[p]) return;
        val[p << 1] += laz[p], laz[p << 1] += laz[p];
        val[p << 1 | 1] += laz[p], laz[p << 1 | 1] += laz[p];
        laz[p] = 0;
        return;
    }
    void pushUp(int p) { return val[p] = min(val[p << 1], val[p << 1 | 1]), void(); }

    void update(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return val[p] += v, laz[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return val[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return min(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int64_t v) { return update(1, 1, n, l, r, v); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r); }
} SGT;

void solve(void) {
    int n, m, q;
    int64_t U, D;
    cin >> n >> U >> D >> m;

    vector<int> vals(1, -1);
    for (int i = 1; i <= m; i++) cin >> pa[i] >> pb[i], vals.push_back(pa[i]), vals.push_back(pb[i]);
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> qa[i] >> qb[i], vals.push_back(qa[i]), vals.push_back(qb[i]);
    sort(vals.begin(), vals.end()), vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    unordered_map<int, int> mp;
    for (size_t i = 0; i < vals.size(); i++) mp[vals[i]] = i;

    SGT.resize(vals.size() - 1);
    for (size_t i = 1; i < vals.size(); i++) SGT.update(i, i, -vals[i] * D);

    set<pii> S;
    S.emplace(-1, -1), S.emplace(n + 1, n + 1);
    int top = 0;

    auto update = [&](pii p, int d) -> void {
        auto [l, r] = p;
        return SGT.update(mp[l] + 1, vals.size() - 1, d * (r - l) * (U + D));
    };
    auto insert = [&](int from, int to) -> void {
        top = max({top, from, to});
        if (from <= to) return;

        int l = to, r = from;
        auto p = --S.lower_bound({l, l});
        if (p->second >= l) l = p->first, r = max(r, p->second), update(*p, -1), S.erase(p);
        p = S.lower_bound({l, l});
        while (p->second <= r) update(*p, -1), p = S.erase(p);
        if (p->first <= r) r = p->second, update(*p, -1), S.erase(p);
        S.emplace(l, r), update({l, r}, +1);

        return;
    };

    for (int i = 1; i <= m; i++) insert(pa[i], pb[i]);
    cout << top * (U + D) + SGT.query(1, mp[top]) << endl;
    for (int i = 1; i <= q; i++) insert(qa[i], qb[i]), cout << top * (U + D) + SGT.query(1, mp[top]) << endl;

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