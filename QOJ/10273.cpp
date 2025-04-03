/**
 * @file 10273.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 200005

int pre[maxn];

class SegmentTree {
   private:
    vector<int> tree;
    int n;

    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }

    void build(int p, int l, int r, int s[]) {
        if (l == r) return tree[p] = s[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, s), build(p << 1 | 1, mid + 1, r, s);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, tree.resize(n << 2); }
    void build(int s[]) { return build(1, 1, n, s); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};

void solve(void) {
    int n, q;
    string s;
    cin >> n >> q >> s;

    set<int> S;
    S.insert(n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i - 1] == 'A' ? +1 : -1);
        if (s[i - 1] == 'A') S.insert(i);
    }

    SegmentTree SGT;
    SGT.resize(n), SGT.build(pre);

    while (q--) {
        int l, r;
        cin >> l >> r;

        if (pre[r] - pre[l - 1] > 0) {
            cout << 0 << endl;
            continue;
        }

        int p = *S.lower_bound(l);
        if (p > r) {
            cout << -1 << endl;
            continue;
        }

        int mv = SGT.query(p, r);
        int c0 = max(0, pre[l - 1] - mv + 1);
        int rest = pre[l - 1] - pre[r] + 1 - c0;
        int c1 = rest / 2 + rest % 2;

        cout << c0 + c1 << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
