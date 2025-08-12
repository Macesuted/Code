/**
 * @file 1179-1003.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;

class SegmentTree {
   private:
    struct Seg {
        int vl, l, r, vr;

        Seg(void) { vl = vr = 0, l = 0, r = 1e6 + 1; }
    };

    vector<array<Seg, 2>> a;
    vector<int> cnt;
    const int n = 1e6;

    void merge(int &rl, int &rr, int ll, int lr) const {
        if (ll > rr) return rl = rr, void();
        if (lr < rl) return rr = rl, void();
        return rl = max(ll, rl), rr = min(lr, rr), void();
    }

    Seg merge(const array<Seg, 2> &lp, const Seg &rp) const {
        Seg ans = rp;

        int t = 0;
        if (ans.vl) {
            t = 1;
            int l = lp[1].vr, r = ans.vl;
            if (l > r) swap(l, r);
            merge(ans.l, ans.r, l, r);
        }

        merge(ans.l, ans.r, lp[t].l, lp[t].r);
        ans.vl = lp[t].vl;

        return ans;
    }

    void pushUp(int p) {
        cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
        if (!cnt[p << 1]) return a[p] = a[p << 1 | 1], void();
        if (!cnt[p << 1 | 1]) return a[p] = a[p << 1], void();

        a[p][0] = merge(a[p << 1], a[p << 1 | 1][0]);
        a[p][1] = merge(a[p << 1], a[p << 1 | 1][1]);

        return;
    }

    void build(int p, int l, int r) {
        if (l == r) return a[p][0] = a[p][1] = Seg(), cnt[p] = 0, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }

    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) return a[p][0].vl = v, a[p][1].vr = v, cnt[p] = 1, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void erase(int p, int l, int r, int qp) {
        if (l == r) return a[p][0] = a[p][1] = Seg(), cnt[p] = 0, void();
        int mid = (l + r) >> 1;
        qp <= mid ? erase(p << 1, l, mid, qp) : erase(p << 1 | 1, mid + 1, r, qp);
        return pushUp(p);
    }

   public:
    SegmentTree(void) { a.resize(n << 2), cnt.resize(n << 2); }
    void build(void) { return build(1, 1, n); }
    void insert(int p, int v) { return insert(1, 1, n, p, v); }
    void erase(int p) { return erase(1, 1, n, p); }
    int query(void) {
        Seg ans = a[1][0];
        assert(ans.vl);
        merge(ans.l, ans.r, ans.vl, ans.vl);
        assert(ans.l == ans.r);
        return ans.l;
    }
};

#define maxn 1000005
#define maxv 1000005

int p[maxn], a[maxn];
int id[maxv];

void solve(void) {
    int n, m;
    cin >> n >> m;

    SegmentTree SGT;
    SGT.build();

    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) cin >> a[i], id[a[i]] = i, SGT.insert(p[i], a[i]);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            SGT.erase(p[x]);
            cin >> p[x];
            SGT.insert(p[x], a[x]);
        } else
            cout << id[SGT.query()] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}