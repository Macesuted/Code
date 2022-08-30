/**
 * @file major.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

typedef pair<int, int> pii;

pii merge(pii a, pii b) {
    return a.second == b.second ? pii{a.first + b.first, a.second}
                                : pii{abs(a.first - b.first), a.first > b.first ? a.second : b.second};
}

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        pii ans;
        Node(void) { l = r = nullptr, ans = {0, 1}; }
    };

    Node* roots[maxn * 2];

    void pushUp(Node* p) {
        if (!p->l) return p->ans = p->r->ans, void();
        if (!p->r) return p->ans = p->l->ans, void();
        return p->ans = ::merge(p->l->ans, p->r->ans), void();
    }
    void add(Node*& p, int l, int r, int qp, int v) {
        if (!p) p = new Node();
        if (l == r) return p->ans = {p->ans.first + v, l}, void();
        int mid = (l + r) >> 1;
        qp <= mid ? add(p->l, l, mid, qp, v) : add(p->r, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void merge(Node*& p, Node* o, int l, int r) {
        if (!p) return p = o, void();
        if (!o) return;
        if (l == r) return p->ans.first += o->ans.first, delete o;
        int mid = (l + r) >> 1;
        merge(p->l, o->l, l, mid), merge(p->r, o->r, mid + 1, r);
        return delete o, pushUp(p);
    }
    int query(Node* p, int l, int r, int qp) {
        if (!p) return 0;
        if (l == r) return p->ans.first;
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p->l, l, mid, qp) : query(p->r, mid + 1, r, qp);
    }

   public:
    SegmentTree(void) { memset(roots, 0, sizeof(roots)); }
    void add(int v, int p, int cnt) { return add(roots[v], 1, 1e6, p, cnt); }
    void merge(int v1, int v2, int p) {
        return roots[p] = roots[v1], merge(roots[p], roots[v2], 1, 1e6), roots[v1] = roots[v2] = nullptr, void();
    }
    int query(int v, int p) { return query(roots[v], 1, 1e6, p); }
    pii maj(int v) { return roots[v] ? roots[v]->ans : pii{0, 1}; }
} ST;

list<int>* a[maxn * 2];
int cac[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1, s, v; i <= n; i++) {
        cin >> s, a[i] = new list<int>();
        while (s--) cin >> v, a[i]->push_back(v), ST.add(i, v, 1);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            a[x]->push_back(y), ST.add(x, y, 1);
        } else if (op == 2) {
            int x, y;
            cin >> x, y = a[x]->back();
            a[x]->pop_back(), ST.add(x, y, -1);
        } else if (op == 3) {
            int s;
            cin >> s;
            pii ama = {0, 1};
            for (int i = 1; i <= s; i++) cin >> cac[i], ama = merge(ama, ST.maj(cac[i]));
            int v = ama.second, cnt = 0, tot = 0;
            for (int i = 1; i <= s; i++) cnt += ST.query(cac[i], v), tot += a[cac[i]]->size();
            cout << (cnt * 2 > tot ? v : -1) << endl;
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            ST.merge(x, y, z);
            if (a[x]->size() < a[y]->size()) {
                a[z] = a[y];
                for (auto i = a[x]->rbegin(); i != a[x]->rend(); i++) a[z]->push_front(*i);
                a[x]->clear();
            } else {
                a[z] = a[x];
                for (auto i = a[y]->begin(); i != a[y]->end(); i++) a[z]->push_back(*i);
                a[y]->clear();
            }
        }
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("major.in", "r", stdin), freopen("major.out", "w", stdout);
#endif
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