/**
 * @file 100.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-01
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

#define maxn 200005
#define mod 998244353

typedef pair<int, int> pii;

class SegmentTree {
   private:
    pii maxv[maxn << 2], minv[maxn << 2];
    int n;

    void pushUp(int p) {
        return maxv[p] = max(maxv[p << 1], maxv[p << 1 | 1]), minv[p] = min(minv[p << 1], minv[p << 1 | 1]), void();
    }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return maxv[p] = minv[p] = {a[l], l}, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    pii query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return minv[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return min(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }
    pii queryMax(int p, int l, int r, int qr, int v) {
        if (l == r) return maxv[p];
        int mid = (l + r) >> 1;
        pii ret = {0, 0};
        if (qr > mid && maxv[p << 1 | 1].first > v) ret = queryMax(p << 1 | 1, mid + 1, r, qr, v);
        if (ret.first) return ret;
        if (maxv[p << 1].first <= v) return {0, 0};
        return queryMax(p << 1, l, mid, qr, v);
    }
    pii queryMin(int p, int l, int r, int qr, int v) {
        if (l == r) return minv[p];
        int mid = (l + r) >> 1;
        pii ret = {0, 0};
        if (qr > mid && minv[p << 1 | 1].first < v) ret = queryMin(p << 1 | 1, mid + 1, r, qr, v);
        if (ret.first) return ret;
        if (minv[p << 1].first >= v) return {0, 0};
        return queryMin(p << 1, l, mid, qr, v);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    int query(int l, int r) { return query(1, 1, n, l, r).second; }
    int queryMax(int r, int v) { return queryMax(1, 1, n, r, v).second; }
    int queryMin(int r, int v) { return queryMin(1, 1, n, r, v).second; }
} ST;

int a[maxn], f[maxn], g[maxn];

int getSum(int l, int r) { return (g[r] + mod - g[l - 1]) % mod; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ST.resize(n), ST.build(a);
    f[0] = f[1] = g[0] = 1, g[1] = 2;
    for (int i = 2; i <= n; i++) {
        int x = ST.queryMin(i, a[i]);
        if (!x)
            f[i] = g[i - 1];
        else {
            int y = ST.queryMax(x, a[i]);
            f[i] = getSum(x, i - 1);
            if (y) {
                int z = ST.query(y, x);
                f[i] = ((int64_t)f[i] + f[z] + mod - getSum(y, z - 1)) % mod;
            }
        }
        g[i] = (g[i - 1] + f[i]) % mod;
    }
    cout << f[n] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("bai.in", "r", stdin), freopen("bai.out", "w", stdout);
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