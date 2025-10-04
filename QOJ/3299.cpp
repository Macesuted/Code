/**
 * @file 3299.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 250005

class SegmentTree {
   private:
    int64_t minVal[maxn << 2], delt[maxn << 2];
    int n;

    void pushUp(int p) { return minVal[p] = min(minVal[p << 1], minVal[p << 1 | 1]), void(); }
    void pushDown(int p) {
        if (!delt[p]) return;
        minVal[p << 1] += delt[p], minVal[p << 1 | 1] += delt[p];
        delt[p << 1] += delt[p], delt[p << 1 | 1] += delt[p];
        delt[p] = 0;
        return;
    }
    void build(int p, int l, int r, int64_t a[]) {
        delt[p] = 0;
        if (l == r) return minVal[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return delt[p] += v, minVal[p] += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int64_t a[]) { return build(1, 1, n, a); }
    void update(int l, int r, int64_t v) {
        if (l > r) return;
        return update(1, 1, n, l, r, v);
    }
    bool chk(void) { return minVal[1] >= 0; }
} SGT;

int a[maxn], sa[maxn], b[maxn], cnt[maxn << 1];
int64_t f[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++, sa[i] = a[i];

    sort(sa + 1, sa + n + 1, greater<int>());
    for (int i = maxn - 1; i; i--) cnt[i - 1] += cnt[i];

    for (int i = 1; i <= m; i++) cin >> b[i], f[1]++, f[b[i] + 1]--;

    int64_t delt = 0;
    f[0] = 0;
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] + (delt += f[i]) - sa[i];

    SGT.resize(n), SGT.build(f);

    int q;
    cin >> q;
    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            SGT.update(++cnt[++a[x]], n, -1);
        else if (op == 2)
            SGT.update(cnt[a[x]--]--, n, +1);
        else if (op == 3)
            SGT.update(++b[x], n, +1);
        else
            SGT.update(b[x]--, n, -1);
        cout << SGT.chk() << endl;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}