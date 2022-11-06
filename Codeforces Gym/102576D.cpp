/**
 * @file 102576D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 3005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    int tree[maxn << 3], laz[maxn << 3], n;
    bool cls[maxn << 3];

    void clear(int p) { return tree[p] = laz[p] = 0, cls[p] = true, void(); }
    void upd(int p, int v) { return tree[p] += v, laz[p] += v, void(); }
    void pushDown(int p) {
        if (cls[p]) clear(p << 1), clear(p << 1 | 1), cls[p] = false;
        if (laz[p]) upd(p << 1, laz[p]), upd(p << 1 | 1, laz[p]), laz[p] = 0;
        return;
    }
    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return upd(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void clear(void) { return clear(1); }
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int t[maxn];
pii a[maxn], b[maxn];
tiii c[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second, t[2 * i - 1] = a[i].first, t[2 * i] = a[i].second;
    sort(t + 1, t + 2 * n + 1);
    int tn = unique(t + 1, t + 2 * n + 1) - t - 1;
    for (int i = 1; i <= n; i++)
        a[i].first = lower_bound(t + 1, t + tn + 1, a[i].first) - t,
        a[i].second = lower_bound(t + 1, t + tn + 1, a[i].second) - t;
    int R = tn, ans = 0;
    ST.resize(R + 1);
    for (int p = 1; p <= n; p++) {
        int l = 1, r = (a[p].second - a[p].first + R) % R + 1;
        for (int i = 1; i <= n; i++) b[i] = {(a[i].first - a[p].first + R) % R + 1, (a[i].second - a[p].first + R) % R + 1};
        auto in = [](int l, int r, int c) { return l <= c && c <= r; };
        int m = 0, cnt = 0;
        for (int i = 1; i <= n; i++) {
            int ql = b[i].first, qr = b[i].second;
            if (ql > qr) ql -= R;
            bool cl = in(ql, qr, l) || in(ql + R, qr + R, l), cr = in(ql, qr, r) || in(ql + R, qr + R, r);
            if (cl && cr) cnt++;
            if (cl && !cr) c[++m] = {b[i].first == 1 ? R + 1 : b[i].first, 0, b[i].second};
            if (!cl && cr) c[++m] = {b[i].second, 1, b[i].first};
        }
        sort(c + 1, c + m + 1), ST.clear();
        for (int i = 1; i <= m; i++) {
            int y = get<2>(c[i]);
            if (!get<1>(c[i]))
                ST.update(1, y, 1);
            else
                ST.update(y, ST.query(1, y)), ST.update(y, R, 1);
        }
        ans = max(ans, cnt + ST.query(1, R));
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}