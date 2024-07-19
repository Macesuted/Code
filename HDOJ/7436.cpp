/**
 * @file 7436.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 600005

typedef pair<int, int> pii;

class UnionSet {
   private:
    vector<pii> log;

    int n, fa[maxn], siz[maxn];
    int64_t val[maxn];

    int getfa(int p) { return p == fa[p] ? p : getfa(fa[p]); }

   public:
    void resize(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1, val[i] = 0;
    }
    void merge(int x, int y) {
        x = getfa(x), y = getfa(y);
        if (x == y) return log.emplace_back(-1, -1), void();
        if (siz[x] > siz[y]) swap(x, y);
        fa[x] = y, siz[y] += siz[x], val[x] -= val[y];
        log.emplace_back(x, y);
        return;
    }
    void back(void) {
        auto [x, y] = log.back();
        log.pop_back();
        if (x == y) return;
        fa[x] = x, siz[y] -= siz[x], val[x] += val[y];
        return;
    }
    void add(int p, int v) { return val[getfa(p)] += v, void(); }
    int64_t query(void) {
        int64_t ans = 0;
        for (int i = 1; i <= n; i++) ans ^= val[i];
        return ans;
    }
} US;

class SegmentTree {
   private:
    vector<pii> tree[maxn << 2];
    int n;

    void insert(int p, int l, int r, int ql, int qr, pii v) {
        if (ql <= l && r <= qr) return tree[p].push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    void solve(int p, int l, int r) {
        for (auto [x, y] : tree[p]) US.merge(x, y);
        if (l == r)
            US.add(1, l);
        else {
            int mid = (l + r) >> 1;
            solve(p << 1, l, mid), solve(p << 1 | 1, mid + 1, r);
        }
        for (int i = tree[p].size(); i; i--) US.back();
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int l, int r, pii v) { return insert(1, 1, n, l, r, v); }
    void solve(void) { return solve(1, 1, n); }
} ST;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    US.resize(n), ST.resize(n);
    for (int i = 1, x, y, l, r; i <= m; i++) {
        cin >> x >> y >> l >> r;
        ST.insert(l, r, {x, y});
    }
    ST.solve();
    cout << US.query() << endl;
    return 0;
}