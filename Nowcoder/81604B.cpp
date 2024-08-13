/**
 * @file 81604B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 200005
#define mod 998244353

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

class SegmentTree {
   private:
    int laz[maxn << 2];
    int64_t sum[maxn << 2];
    int n;

    void pushUp(int p) {
        sum[p] = 0;
        if (!laz[p << 1]) sum[p] = Mod(sum[p] + sum[p << 1]);
        if (!laz[p << 1 | 1]) sum[p] = Mod(sum[p] + sum[p << 1 | 1]);
        return;
    }
    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) return sum[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return laz[p] += v, void();
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int p, int v) { return insert(1, 1, n, p, v); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    int64_t query(void) { return sum[1]; }
} ST;

int a[maxn], s[15], f[maxn];
vector<int> rec[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], rec[i].push_back(0);
    for (int i = 1; i <= m; i++) cin >> s[i];
    ST.resize(n), f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int p = (int)rec[a[i]].size() - 1 - s[j];
            if (p >= 0) ST.update(rec[a[i]][p] + 1, rec[a[i]][p + 1], -1);
        }
        rec[a[i]].push_back(i);
        for (int j = 1; j <= m; j++) {
            int p = (int)rec[a[i]].size() - 1 - s[j];
            if (p >= 0) ST.update(rec[a[i]][p] + 1, rec[a[i]][p + 1], +1);
        }
        ST.insert(i, f[i - 1]);
        f[i] = ST.query();
    }
    cout << f[n] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}