/**
 * @file 5459.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

class SegmentTree {
   private:
    int lim[maxn << 2], ans[maxn << 2], n;

    void pushUp(int p, int l, int r) { return ans[p] = (lim[p] ? 0 : (l == r ? 1 : ans[p << 1] + ans[p << 1 | 1])), void(); }

    void build(int p, int l, int r) {
        if (l == r) return lim[p] = 0, ans[p] = 1, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p, l, r);
    }
    void update(int p, int l, int r, int ql, int qr, int delt) {
        if (ql <= l && r <= qr) return lim[p] += delt, pushUp(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, delt);
        if (mid < qr) update(p << 1 | 1, mid + 1, r, ql, qr, delt);
        return pushUp(p, l, r);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (lim[p]) return 0;
        if (ql <= l && r <= qr) return ans[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int l, int r, int delt) { return update(1, 1, n, l, r, delt); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};

SegmentTree SGT;
int a[maxn];
vector<int> pos[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k, SGT.resize(n), SGT.build();
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]].push_back(i);

    for (int i = 1; i <= 1e6; i++) {
        pos[i].push_back(n + 1);
        if (k < (int)pos[i].size()) SGT.update(pos[i][k - 1], pos[i][k] - 1, +1);
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += SGT.query(i, n);
        int p = lower_bound(pos[a[i]].begin(), pos[a[i]].end(), i) - pos[a[i]].begin();
        if (p + k < (int)pos[a[i]].size()) SGT.update(pos[a[i]][p + k - 1], pos[a[i]][p + k] - 1, -1);
        if (p + k + 1 < (int)pos[a[i]].size()) SGT.update(pos[a[i]][p + k], pos[a[i]][p + k + 1] - 1, +1);
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
