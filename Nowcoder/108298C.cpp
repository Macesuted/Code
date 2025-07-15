/**
 * @file 108298C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

using pll = pair<int64_t, int64_t>;

int64_t calc(const pll &f, int64_t x) { return f.first * x + f.second; }

class SegmentTree {
   private:
    struct Node {
        pll ln;
        int l, r;
        Node(void) : ln({0, 0}), l(-1), r(-1) {}
    };

    vector<Node> pool;

    int newNode(void) { return assert(pool.size() < pool.capacity()), pool.push_back(Node()), pool.size() - 1; }

    void update(int &pid, int64_t l, int64_t r, int64_t ql, int64_t qr, pll ln) {
        if (!~pid) pid = newNode();
        Node *p = &pool[pid];
        int64_t mid = (l + r) >> 1;
        if (ql <= l && r <= qr) {
            if (calc(ln, mid) > calc(p->ln, mid)) swap(ln, p->ln);
            if (calc(ln, l) > calc(p->ln, l)) update(p->l, l, mid, ql, qr, ln);
            if (calc(ln, r) > calc(p->ln, r)) update(p->r, mid + 1, r, ql, qr, ln);
            return;
        }
        if (ql <= mid) update(p->l, l, mid, ql, qr, ln);
        if (qr > mid) update(p->r, mid + 1, r, ql, qr, ln);
        return;
    }
    pll query(int pid, int64_t l, int64_t r, int64_t qp) {
        if (!~pid) return {0, 0};
        Node *p = &pool[pid];
        if (l == r) return p->ln;
        int64_t mid = (l + r) >> 1;
        pll ret = qp <= mid ? query(p->l, l, mid, qp) : query(p->r, mid + 1, r, qp);
        return calc(p->ln, qp) > calc(ret, qp) ? p->ln : ret;
    }

    int64_t xl, xr;
    int root;

    map<int64_t, int64_t> rec;

   public:
    SegmentTree(void) : xl(0), xr(0), root(-1) { pool.reserve(1.5e7); }

    void resize(int64_t l, int64_t r) { return xl = l, xr = r, void(); }
    void update(int64_t l, int64_t r, pll ln) {
        rec[l] = max(rec[l], calc(ln, l)), rec[r] = max(rec[r], calc(ln, r));
        return update(root, xl, xr, l, r, ln);
    }
    void build(void) {
        rec[0] = max(rec[0], (int64_t)0);
        for (auto p = rec.begin(); p != rec.end(); p++)
            while (next(p) != rec.end() && p->second >= next(p)->second) rec.erase(next(p));
        return;
    }
    int64_t query(int64_t qp) { return max(prev(rec.lower_bound(qp))->second, calc(query(root, xl, xr, qp), qp)); }
} SGT;

int64_t a[maxn], w[maxn];
bool vis[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) cin >> w[i];
    w[0] = w[n + 1] = 0;

    SGT.resize(0, 2e9);

    auto genLine = [&](int64_t x, int64_t v, int64_t k) -> pll { return {k, v - x * k}; };

    for (int t = 0; t < 2; t++) {
        map<int64_t, vector<int>> rec;
        for (int i = 1; i <= n; i++) rec[a[i]].push_back(i);
        for (auto up = rec.rbegin(); next(up) != rec.rend(); up++) {
            int64_t U = up->first, v = 0, dK = 0;
            for (int i = 1; i < n; i++) v += abs(min(a[i], U) - min(a[i + 1], U)) * w[i];

            pll ln = {0, v};
            for (int i = 1; i <= n; i++) vis[i] = false;
            for (auto dp = rec.begin(); dp->first != U; dp++) {
                int64_t D = dp->first, dD = next(dp)->first - D;
                for (auto d : dp->second) {
                    dK += w[d - 1] + w[d];
                    vis[d] = true;
                    if (vis[d - 1]) dK -= 2 * w[d - 1];
                    if (vis[d + 1]) dK -= 2 * w[d];
                }
                SGT.update(U - D - dD, U - D, ln = genLine(U - D, calc(ln, U - D), dK));
            }
        }
        for (int i = 1; i <= n; i++) a[i] = -a[i];
    }

    SGT.build();

    while (q--) {
        int64_t d;
        cin >> d;
        cout << SGT.query(d) << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
