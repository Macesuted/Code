/**
 * @file 2174.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define maxv 1000000005

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int sum;
        Node(void) { l = r = NULL, sum = 0; }
    };

    vector<Node *> roots;

    void pushUp(Node *p) { return p && (p->sum = (p->l ? p->l->sum : 0) + (p->r ? p->r->sum : 0)), void(); }
    void insert(Node *&p, int l, int r, int qp) {
        if (!p) p = new Node();
        Node o = *p;
        p = new Node(), *p = o;
        if (l == r) return p->sum += l, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp) : insert(p->r, mid + 1, r, qp);
        return pushUp(p);
    }
    int query(Node *p, int l, int r, int ql, int qr) {
        if (!p) return 0;
        if (ql <= l && r <= qr) return p->sum;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return query(p->l, l, mid, ql, qr) + query(p->r, mid + 1, r, ql, qr);
    }

   public:
    SegmentTree(void) { roots.push_back(NULL); }
    void insert(int v) { return roots.push_back(roots.back()), insert(roots.back(), 1, maxv, v), void(); }
    int query(int v, int l, int r) { return query(roots[v], 1, maxv, l, r); }
};

int a[maxn], t[maxn];
SegmentTree ST;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], ST.insert(a[i]);
    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        int lst = 0, ans = 0;
        while (lst <= ans) {
            int ret = ST.query(r, lst + 1, ans + 1) - ST.query(l - 1, lst + 1, ans + 1);
            lst = ans + 1, ans += ret;
        }
        cout << ans + 1 << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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