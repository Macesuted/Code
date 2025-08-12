/**
 * @file 1179-1006.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

class SegmentTree {
   private:
    vector<array<array<int64_t, 4>, 4>> a;
    int n;

    void pushUp(int p, int l, int r) {
        int mid = (l + r) >> 1;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) a[p][i][j] = 0;
        for (int ll = 0; ll < 4; ll++)
            for (int lr = 0; lr < 4; lr++)
                for (int rl = 0; rl < 4 - lr; rl++)
                    for (int rr = 0; rr < 4; rr++) {
                        int pl = ll, pr = rr;
                        if (ll == mid - l + 1) pl += rl;
                        if (rr == r - mid) pr += lr;
                        if (pl < 4 && pr < 4) a[p][pl][pr] = max(a[p][pl][pr], a[p << 1][ll][lr] + a[p << 1 | 1][rl][rr]);
                    }
        return;
    }

    void build(int p, int l, int r, int v[]) {
        if (l == r) {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++) a[p][i][j] = 0;
            a[p][1][1] = v[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, v), build(p << 1 | 1, mid + 1, r, v);
        return pushUp(p, l, r);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return a[p][1][1] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p, l, r);
    }

   public:
    void resize(int _n) { return a.resize((n = _n) << 2); }
    void build(int a[]) { return build(1, 1, n, a); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int64_t query(void) {
        int64_t ans = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4 - i; j++) ans = max(ans, a[1][i][j]);
        return ans;
    }
};

#define maxn 200005

int a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegmentTree SGT;
    SGT.resize(n), SGT.build(a);

    cout << SGT.query() << endl;

    while (q--) {
        int p, v;
        cin >> p >> v;
        SGT.update(p, v);
        cout << SGT.query() << endl;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}