/**
 * @file 105789F.cpp
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

#define maxn 200005

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        multiset<int> S;
        int ans;
        Node(void) { l = r = nullptr, ans = 0; }
    };

    Node *root;
    int n;

    void pushUp(Node *p) {
        return p->ans = max(p->S.empty() ? 0 : *p->S.rbegin(), min((p->l ? p->l->ans : 0), (p->r ? p->r->ans : 0))), void();
    }

    void insert(Node *&p, int l, int r, int ql, int qr, int v) {
        if (!p) p = new Node();
        if (ql <= l && r <= qr) return p->S.insert(v), pushUp(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p->l, l, mid, ql, qr, v);
        if (qr > mid) insert(p->r, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    void erase(Node *&p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return p->S.erase(p->S.find(v)), pushUp(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) erase(p->l, l, mid, ql, qr, v);
        if (qr > mid) erase(p->r, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int query(Node *p, int l, int r, int ql, int qr) {
        if (!p) return 0;
        if (ql <= l && r <= qr) return p->ans;
        int mid = (l + r) >> 1, ans = INT_MAX;
        if (ql <= mid) ans = min(ans, query(p->l, l, mid, ql, qr));
        if (qr > mid) ans = min(ans, query(p->r, mid + 1, r, ql, qr));
        return max(ans, (p->S.empty() ? 0 : *p->S.rbegin()));
    }

   public:
    SegmentTree(void) { root = nullptr, n = 1e9; }
    void insert(int l, int r, int v) { return insert(root, 1, n, l, r, v); }
    void erase(int l, int r, int v) { return erase(root, 1, n, l, r, v); }
    int query(int l, int r) { return query(root, 1, n, l, r); }
} SGT;

int cl[maxn], cr[maxn], cx[maxn];

void solve(void) {
    int n, index = 0;
    cin >> n;
    while (n--) {
        char op;
        cin >> op;
        if (op == '+') {
            int l, r, x;
            cin >> l >> r >> x, index++, cl[index] = l, cr[index] = r, cx[index] = x;
            SGT.insert(l, r - 1, x);
        } else if (op == '-') {
            int i;
            cin >> i;
            SGT.erase(cl[i], cr[i] - 1, cx[i]);
        } else {
            int l, r;
            cin >> l >> r;
            cout << SGT.query(l, r - 1) << endl;
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