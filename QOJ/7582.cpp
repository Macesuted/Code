/**
 * @file 7582.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 2005

using pii = pair<int, int>;

class SegmentTree {
   private:
    struct Node {
        int64_t ans, sum, pl, pr;

        Node(void) { ans = sum = pl = pr = 0; }
        Node operator+(const Node &o) const {
            Node ret;
            ret.ans = max({ans, o.ans, pr + o.pl});
            ret.sum = sum + o.sum;
            ret.pl = max(pl, sum + o.pl);
            ret.pr = max(pr + o.sum, o.pr);
            return ret;
        }
    };

    vector<Node> a;
    int n;

    void add(int p, int l, int r, int qp, int v) {
        if (l == r) {
            a[p].sum += v;
            a[p].ans = a[p].pl = a[p].pr = max((int64_t)0, a[p].sum);
            return;
        }
        int mid = (l + r) >> 1;
        qp <= mid ? add(p << 1, l, mid, qp, v) : add(p << 1 | 1, mid + 1, r, qp, v);
        return a[p] = a[p << 1] + a[p << 1 | 1], void();
    }

   public:
    void resize(int _n) { return a.resize((n = _n) << 2); }
    void add(int p, int v) { return add(1, 1, n, p, v); }
    int64_t qry(void) { return a[1].ans; }
};

void solve(void) {
    int n;
    cin >> n;

    map<int, vector<pii>> a;
    vector<int> ys;
    for (int i = 1, x, y, w; i <= n; i++) cin >> x >> y >> w, a[x].emplace_back(y, w), ys.push_back(y);

    sort(ys.begin(), ys.end());
    ys.resize(unique(ys.begin(), ys.end()) - ys.begin());
    for (auto &[x, vec] : a)
        for (auto &[y, w] : vec) y = lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;

    int64_t ans = 0;
    for (auto l = a.begin(); l != a.end(); l++) {
        SegmentTree SGT;
        SGT.resize(n);
        for (auto r = l; r != a.end(); r++) {
            for (auto [y, w] : r->second) SGT.add(y, w);
            ans = max(ans, SGT.qry());
        }
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
