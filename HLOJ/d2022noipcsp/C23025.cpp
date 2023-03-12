/**
 * @file C23025.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-10
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

#define maxn 100005
#define mod 998244353

typedef pair<int, int> pii;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int Mod(int x, int p = mod) { return x >= p ? x - p : x; }
int sqr(int64_t x) { return x * x % mod; }

class SegmentTree {
   private:
    int n, m, sum[maxn << 2][25], pt[maxn << 2], laz[maxn << 2];
    bool mk[maxn << 2];

    void upd(int p, int v) { return pt[p] = Mod(pt[p] + v, m), laz[p] = Mod(laz[p] + v, m), void(); }
    void pushDown(int p) { return upd(p << 1, laz[p]), upd(p << 1 | 1, laz[p]), laz[p] = 0, void(); }
    void pushUp(int p) {
        for (int i = pt[p] = 0, pl = pt[p << 1], pr = pt[p << 1 | 1]; i < m; i++, pl = Mod(pl + 1, m), pr = Mod(pr + 1, m))
            sum[p][i] = Mod(sum[p << 1][pl] + sum[p << 1 | 1][pr]);
        return mk[p] = mk[p << 1] | mk[p << 1 | 1], void();
    }
    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) {
            sum[p][pt[p] = 0] = v;
            for (int i = 1; i < m; i++) sum[p][i] = sqr(sum[p][i - 1]);
            mk[p] = (sqr(sum[p][m - 1]) != sum[p][0]);
            return;
        }
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr && !mk[p]) return upd(p, 1);
        if (l == r) {
            sum[p][0] = sum[p][Mod(pt[p] + 1, m)], pt[p] = 0;
            for (int i = 1; i < m; i++) sum[p][i] = sqr(sum[p][i - 1]);
            mk[p] = (sqr(sum[p][m - 1]) != sum[p][0]);
            return;
        }
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[p][pt[p]];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return Mod(query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n, int _m) { return n = _n, m = _m, void(); }
    void insert(int p, int v) { return insert(1, 1, n, p, v); }
    void update(int l, int r) { return update(1, 1, n, l, r); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int n, m, a[maxn], to[maxn];

void solve(void) {
    cin >> n >> m;
    ST.resize(n, 24);
    for (int i = 1, p; i <= n; i++) {
        cin >> a[i], p = a[i] = Inv(a[i]);
        queue<int> que;
        set<int> vis;
        while (!vis.count(p)) vis.insert(p), que.push(p), p = sqr(p);
        while (que.front() != p) que.pop();
        to[i] = p, ST.insert(i, a[i]);
    }
    for (int i = 1, op, l, r; i <= m; i++) {
        cin >> op >> l >> r;
        if (!op)
            ST.update(l, r);
        else
            cout << ST.query(l, r) << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("snow.in", "r", stdin), freopen("snow.out", "w", stdout);
#endif
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