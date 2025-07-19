/**
 * @file 1172-1002.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

namespace FastIO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Ir = Ibuf, *Il = Ibuf;
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
int read(void) {
    int x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
}  // namespace FastIO
using FastIO::read;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t lim, delt;
        int a, b;
        Node(void) : l(nullptr), r(nullptr), lim(0), delt(0) {}
    };

    vector<Node*> root;
    int n;

    void pushUp(Node* p) {
        p->lim = max(p->l->lim, p->r->lim - p->l->delt), p->delt = p->l->delt + p->r->delt;
        return;
    }

    void build(Node*& p, int l, int r, int a[], int b[]) {
        if (!p) p = new Node();
        if (l == r) return p->a = a[l], p->b = b[l], p->delt = p->a - p->b, p->lim = -p->delt, void();
        int mid = (l + r) >> 1;
        build(p->l, l, mid, a, b), build(p->r, mid + 1, r, a, b);
        return pushUp(p);
    }
    void update(Node*& p, int l, int r, int qp, int a, int b) {
        p = new Node(*p);
        if (l == r) {
            if (~a) p->a = a;
            if (~b) p->b = b;
            p->delt = p->a - p->b, p->lim = -p->delt;
            return;
        }
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, a, b) : update(p->r, mid + 1, r, qp, a, b);
        return pushUp(p);
    }
    int getA(Node* p, int l, int r, int qp) {
        if (l == r) return p->a;
        int mid = (l + r) >> 1;
        return qp <= mid ? getA(p->l, l, mid, qp) : getA(p->r, mid + 1, r, qp);
    }
    void query(Node* p, int l, int r, int ql, int qr, int64_t& v) {
        if (ql <= l && r <= qr) return v = max(v, p->lim) + p->delt, void();
        int mid = (l + r) >> 1;
        if (ql <= mid) query(p->l, l, mid, ql, qr, v);
        if (qr > mid) query(p->r, mid + 1, r, ql, qr, v);
        return;
    }

   public:
    SegmentTree(void) { root.push_back(nullptr); }
    void build(int _n, int a[], int b[]) { return build(root[0], 1, n = _n, a, b); }
    void newVer(int v) { return root.push_back(root[v]); }
    void update(int v, int p, int a, int b) { return update(root[v], 1, n, p, a, b); }
    int getA(int v, int p) { return getA(root[v], 1, n, p); }
    int64_t query(int v, int l, int r, int64_t val) { return query(root[v], 1, n, l, r, val), val; }
};

#define maxn 200005

int a[maxn], b[maxn];
int64_t tot[maxn];

void solve(void) {
    int n = read(), m = read();
    tot[0] = 0;
    for (int i = 1; i <= n; i++) a[i] = read(), tot[0] += a[i];
    for (int i = 1; i <= n; i++) b[i] = read();

    SegmentTree SGT;
    SGT.build(n, a, b);

    for (int t = 1; t <= m; t++) {
        int op = read();
        if (op == 1) {
            int x = read(), y = read();
            SGT.newVer(t - 1), tot[t] = tot[t - 1] - SGT.getA(t, x) + y;
            SGT.update(t, x, y, -1);
        } else if (op == 2) {
            int x = read(), y = read();
            SGT.newVer(t - 1), tot[t] = tot[t - 1];
            SGT.update(t, x, -1, y);
        } else if (op == 3) {
            int x = read();
            SGT.newVer(x), tot[t] = tot[x];
        } else {
            SGT.newVer(t - 1), tot[t] = tot[t - 1];
            size_t k = read();
            vector<int> pos(k + 2);
            pos[0] = 0, pos[k + 1] = n + 1;
            for (size_t i = 1; i <= k; i++) pos[i] = read();

            int64_t v = 0;
            for (size_t i = 0; i <= k; i++) {
                if (pos[i + 1] - pos[i] > 1) v = SGT.query(t, pos[i] + 1, pos[i + 1] - 1, v);
                if (i < k) v += SGT.getA(t, pos[i + 1]), v >>= 1;
            }
            cout << tot[t] - v << endl;
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}
