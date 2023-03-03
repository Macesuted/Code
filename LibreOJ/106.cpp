/**
 * @file 106.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 50005

mt19937 rnd(20080618);

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int rnk, siz, val;
        Node(int _val) { l = r = nullptr, rnk = rnd(), siz = 1, val = _val; }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void pushUp(Node* p) { return p->siz = getSiz(p->l) + getSiz(p->r) + 1, void(); }
    void split(Node* p, Node*& t1, Node*& t2, int v) {
        if (!p) return t1 = t2 = nullptr, void();
        if (p->val < v)
            t1 = p, split(p->r, t1->r, t2, v);
        else
            t2 = p, split(p->l, t1, t2->l, v);
        return pushUp(p);
    }
    void merge(Node*& p, Node* t1, Node* t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            p = t1, merge(p->r, t1->r, t2);
        else
            p = t2, merge(p->l, t1, t2->l);
        return pushUp(p);
    }

   public:
    FhqTreap(void) { root = nullptr; }
    void insert(int v) {
        Node* tr = nullptr;
        split(root, root, tr, v);
        return merge(root, root, new Node(v)), merge(root, root, tr);
    }
    void erase(int v) {
        Node *tp = nullptr, *tr = nullptr;
        split(root, root, tp, v), split(tp, tp, tr, v + 1);
        return delete tp, merge(root, root, tr);
    }
    int query(int l, int r) {
        Node *tp = nullptr, *tr = nullptr;
        split(root, root, tp, l), split(tp, tp, tr, r + 1);
        int ret = getSiz(tp);
        return merge(root, root, tp), merge(root, root, tr), ret;
    }
};
class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        FhqTreap FT;
        Node(void) { l = r = nullptr; }
    };

    Node* root;

    void update(Node*& p, int l, int r, int v, int w) {
        if (!p) p = new Node();
        w > 0 ? p->FT.insert(w) : p->FT.erase(-w);
        if (l == r) return;
        int mid = (l + r) >> 1;
        v <= mid ? update(p->l, l, mid, v, w) : update(p->r, mid + 1, r, v, w);
    }
    int query(Node*& p, int l, int r) { return p ? p->FT.query(l, r) : 0; }
    int query1(Node*& p, int l, int r, int v, int ql, int qr) {
        if (!p) return 0;
        if (v >= r) return query(p, ql, qr);
        int mid = (l + r) >> 1;
        return v <= mid ? query1(p->l, l, mid, v, ql, qr) : query(p->l, ql, qr) + query1(p->r, mid + 1, r, v, ql, qr);
    }
    int query2(Node*& p, int l, int r, int v, int ql, int qr) {
        if (l == r) return l;
        int mid = (l + r) >> 1, vl = query(p->l, ql, qr);
        return vl >= v ? query2(p->l, l, mid, v, ql, qr) : query2(p->r, mid + 1, r, v - vl, ql, qr);
    }
    int query4(Node*& p, int l, int r, int v, int ql, int qr) {
        if (!query(p, ql, qr)) return INT_MIN;
        if (l == r) return l;
        int mid = (l + r) >> 1, ret = INT_MIN;
        if (mid + 1 < v) ret = query4(p->r, mid + 1, r, v, ql, qr);
        return ret != INT_MIN ? ret : query4(p->l, l, mid, v, ql, qr);
    }
    int query5(Node*& p, int l, int r, int v, int ql, int qr) {
        if (!query(p, ql, qr)) return INT_MAX;
        if (l == r) return l;
        int mid = (l + r) >> 1, ret = INT_MAX;
        if (mid > v) ret = query5(p->l, l, mid, v, ql, qr);
        return ret != INT_MAX ? ret : query5(p->r, mid + 1, r, v, ql, qr);
    }

   public:
    SegmentTree(void) { root = nullptr; }
    void update(int p, int v) { return update(root, -1e8, +1e8, v, p); }
    int query1(int l, int r, int v) { return query1(root, -1e8, +1e8, v - 1, l, r) + 1; }
    int query2(int l, int r, int v) { return query2(root, -1e8, +1e8, v, l, r); }
    int query4(int l, int r, int v) { return query4(root, -1e8, +1e8, v, l, r); }
    int query5(int l, int r, int v) { return query5(root, -1e8, +1e8, v, l, r); }
} ST;

int a[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], ST.update(i, a[i]);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, x;
            cin >> l >> r >> x, cout << ST.query1(l, r, x) << endl;
        } else if (op == 2) {
            int l, r, k;
            cin >> l >> r >> k, cout << ST.query2(l, r, k) << endl;
        } else if (op == 3) {
            int p, x;
            cin >> p >> x, ST.update(-p, a[p]), ST.update(p, a[p] = x);
        } else if (op == 4) {
            int l, r, x;
            cin >> l >> r >> x, cout << ST.query4(l, r, x) << endl;
        } else {
            int l, r, x;
            cin >> l >> r >> x, cout << ST.query5(l, r, x) << endl;
        }
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