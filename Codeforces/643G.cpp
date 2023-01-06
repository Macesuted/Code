/**
 * @file 643G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
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

#define maxn 150005

typedef pair<int, int> pii;

int k;

class SegmentTree {
   private:
    vector<pii> rec[maxn << 2];
    int laz[maxn << 2], n;

    void update(int p, int l, int r, int v) { return rec[p].clear(), rec[p].emplace_back(r - l + 1, v), laz[p] = v, void(); }
    vector<pii> merge(const vector<pii>& a, const vector<pii>& b) {
        vector<pii> c = a;
        for (auto i : b) {
            bool fnd = false;
            for (auto& j : c)
                if (i.second == j.second) j.first += i.first, fnd = true;
            if (!fnd) c.push_back(i);
        }
        while ((int)c.size() > k) {
            int minp = 0;
            for (int i = 1; i <= k; i++)
                if (c[i] < c[minp]) minp = i;
            int v = c[minp].first;
            for (int i = 0; i <= k; i++) c[i].first -= v;
            swap(c[minp], c.back()), c.pop_back();
        }
        return c;
    }
    void pushDown(int p, int l, int r) {
        if (!laz[p]) return;
        int mid = (l + r) >> 1;
        update(p << 1, l, mid, laz[p]), update(p << 1 | 1, mid + 1, r, laz[p]), laz[p] = 0;
        return;
    }
    void pushUp(int p) { return rec[p] = merge(rec[p << 1], rec[p << 1 | 1]), void(); }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return rec[p].emplace_back(1, a[l]), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return update(p, l, r, v);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    vector<pii> query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return rec[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void build(int _n, int a[]) { return build(1, 1, n = _n, a); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    vector<pii> query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int a[maxn];

void solve(void) {
    int n, m, p;
    cin >> n >> m >> p, k = 100 / p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ST.build(n, a);
    while (m--) {
        int op, l, r, v;
        cin >> op >> l >> r;
        if (op == 1)
            cin >> v, ST.update(l, r, v);
        else {
            auto ret = ST.query(l, r);
            cout << ret.size();
            for (auto i : ret) cout << ' ' << i.second;
            cout << endl;
        }
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