/**
 * @file 105789G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-20
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

using pll = pair<int64_t, int64_t>;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t minv, maxv, laz;
        Node(void) { l = r = nullptr, minv = maxv = 0, laz = -1; }
    };

    Node *root;
    int64_t n;

    pll merge(const pll &a, const pll &b) { return {min(a.first, b.first), max(a.second, b.second)}; }

    void pushDown(Node *p) {
        if (!p->l) p->l = new Node();
        if (!p->r) p->r = new Node();
        if (p->laz == -1) return;
        p->l->minv = p->l->maxv = p->l->laz = p->laz;
        p->r->minv = p->r->maxv = p->r->laz = p->laz;
        p->laz = -1;
        return;
    }
    void pushUp(Node *p) {
        p->minv = INT64_MAX, p->maxv = INT64_MIN;
        if (p->l) p->minv = min(p->minv, p->l->minv), p->maxv = max(p->maxv, p->l->maxv);
        if (p->r) p->minv = min(p->minv, p->r->minv), p->maxv = max(p->maxv, p->r->maxv);
        return;
    }
    void update(Node *&p, int64_t l, int64_t r, int64_t ql, int64_t qr, int64_t v) {
        if (!p) p = new Node();
        if (ql <= l && r <= qr) return p->minv = p->maxv = p->laz = v, void();
        pushDown(p);
        int64_t mid = (l + r) >> 1;
        if (ql <= mid) update(p->l, l, mid, ql, qr, v);
        if (qr > mid) update(p->r, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    pll query(Node *p, int64_t l, int64_t r, int64_t ql, int64_t qr) {
        if (!p) return {0, 0};
        if (ql <= l && r <= qr) return {p->minv, p->maxv};
        pushDown(p);
        int64_t mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return merge(query(p->l, l, mid, ql, qr), query(p->r, mid + 1, r, ql, qr));
    }

   public:
    SegmentTree(void) { root = nullptr, n = 1e18 + 1e9 + 5; }
    void update(int64_t l, int64_t r, int64_t v) { return update(root, 1, n, l, r, v); }
    pll query(int64_t l, int64_t r) { return query(root, 1, n, l, r); }
} SGT;

void solve(void) {
    int n;
    cin >> n;
    while (n--) {
        char op;
        int64_t len, pos;
        cin >> op >> len >> pos;
        if (op == '|') {
            int64_t low = SGT.query(pos, pos).first;
            SGT.update(pos, pos, low + len);
            cout << 'S';
        } else {
            auto [low, high] = SGT.query(pos, pos + len - 1);
            if (low != high)
                cout << 'U';
            else
                cout << 'S', SGT.update(pos, pos + len - 1, low + 1);
        }
    }
    cout << endl;
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