/**
 * @file 14140.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define mod 998244353
#define maxn 200005

using pll = pair<int64_t, int64_t>;

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        pll val;
        Node(void) { l = r = nullptr, val = {1, 0}; }
    };

    vector<Node *> roots;

    pll merge(const pll &a, const pll &b) { return {a.first * b.first % mod, a.second + b.second}; }
    void pushUp(Node *p) {
        return p->val = (p->l && p->r) ? merge(p->l->val, p->r->val) : p->l ? p->l->val : p->r->val, void();
    }
    void insert(Node *&p, int l, int r, int qp) {
        p = new Node(p ? *p : Node());
        if (l == r) return p->val = merge(p->val, {qp, qp - 1}), void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp) : insert(p->r, mid + 1, r, qp);
        return pushUp(p);
    }
    pll query(Node *p, int l, int r, int ql, int qr) {
        if (!p) return {1, 0};
        if (ql <= l && r <= qr) return p->val;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return merge(query(p->l, l, mid, ql, qr), query(p->r, mid + 1, r, ql, qr));
    }

   public:
    void build(int n, int a[]) {
        roots.resize(n + 1);
        for (int i = 1; i <= n; i++) insert(roots[i] = roots[i - 1], 1, mod - 1, a[i]);
        return;
    }
    pll query(int l, int r, int vl, int vr) {
        pll retl = query(roots[l - 1], 1, mod - 1, vl, vr), retr = query(roots[r], 1, mod - 1, vl, vr);
        return {retr.first * inv(retl.first) % mod, retr.second - retl.second};
    }
} SGT;

int a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> a[i];
    SGT.build(n, a);

    while (q--) {
        int l, r;
        int64_t k;
        cin >> l >> r >> k;

        int vl = 0, vr = mod;
        while (vl + 1 < vr) {
            int mid = (vl + vr) >> 1;
            (SGT.query(l, r, 1, mid).second <= k ? vl : vr) = mid;
        }

        if (vl == mod - 1) {
            cout << 1 << endl;
            continue;
        }

        k -= SGT.query(l, r, 1, vl).second;
        int64_t cnt = SGT.query(l, r, vr, vr).second / (vr - 1) - (k / (vr - 1) + 1), rest = vr - k % (vr - 1);
        assert(cnt >= 0);
        cout << SGT.query(l, r, vr + 1, mod - 1).first * qpow(vr, cnt) % mod * rest % mod << endl;
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