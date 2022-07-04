/**
 * @file 2210-nlog^2n.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-04
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

#define maxn 105
#define maxv 100005

class SegmentTree {
   private:
    int vis[maxv << 1], n;

    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return vis[p] |= v, void();
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    int query(int p, int l, int r, int qp) {
        if (l == r) return vis[p];
        int mid = (l + r) >> 1;
        return (qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp)) | vis[p];
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int v) { return update(1, 0, n, l, r, v); }
    int query(int p) { return query(1, 0, n, p); }
} ST[2];

int f[maxv];

void solve(void) {
    int n, v = 0;
    cin >> n;
    for (int i = 1, x; i <= n; i++) cin >> x, v ^= f[x];
    cout << (v > 0) << ' ';
    return;
}

void upd(int l, int r, int v) { return ST[l & 1].update(l >> 1, min(r, 100000) >> 1, 1 << v); }

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1, F;
    cin >> _ >> F;
    ST[0].resize(50000), ST[1].resize(50000);
    for (int i = 1; i <= 100000; i++) {
        if (i + 1 < F)
            f[i + 1] = 0;
        else if (i + 1 <= 100000) {
            int ret = ST[(i + 1) & 1].query((i + 1) >> 1);
            f[i + 1] = 1;
            while (ret >> f[i + 1] & 1) f[i + 1]++;
        }
        for (int j = 2; i * j <= 100000; j++) {
            int x = i * j;
            if (j & 1)
                upd(x, x + j - 1, f[i]), upd(x + 1, x + j - 2, f[i + 1]);
            else
                upd(x + 1, x + j - 1, f[i] ^ f[i + 1]);
        }
    }
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
