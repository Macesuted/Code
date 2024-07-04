/**
 * @file 1919F1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

int64_t a[maxn], b[maxn], c[maxn];

class SegmentTree {
   private:
    int n;
    int64_t f[maxn << 2][2][2];

    void pushUp(int p, int mid) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                f[p][i][j] = min({f[p << 1][i][0] + f[p << 1 | 1][0][j], f[p << 1][i][0] + f[p << 1 | 1][1][j] + c[mid],
                                  f[p << 1][i][1] + f[p << 1 | 1][0][j], f[p << 1][i][1] + f[p << 1 | 1][1][j]});
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) return f[p][0][0] = b[l], f[p][1][1] = a[l], f[p][0][1] = f[p][1][0] = 1e18, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p, mid);
    }
    void update(int p, int l, int r, int qp) {
        if (l == r) return f[p][0][0] = b[l], f[p][1][1] = a[l], f[p][0][1] = f[p][1][0] = 1e18, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp) : update(p << 1 | 1, mid + 1, r, qp);
        return pushUp(p, mid);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int p) { return update(1, 1, n, p); }
    int64_t query(void) { return min({f[1][0][0], f[1][0][1], f[1][1][0], f[1][1][1]}); }
} ST;

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i < n; i++) cin >> c[i];
    ST.resize(n), ST.build();
    while (q--) {
        int p;
        cin >> p >> a[p] >> b[p] >> c[p], ST.update(p);
        cout << ST.query() << endl;
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