/**
 * @file 7458.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005
#define endl '\n'

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t f, laz;
        Node(void) { l = r = nullptr, f = laz = 0; }
    };

    Node* root;
    int n;

    void pushDown(Node* p) {
        if (!p->laz) return;
        if (p->l) p->l->f += p->laz, p->l->laz += p->laz;
        if (p->r) p->r->f += p->laz, p->r->laz += p->laz;
        p->laz = 0;
        return;
    }
    void pushUp(Node* p) {
        p->f = 0;
        if (p->l) p->f = max(p->f, p->l->f);
        if (p->r) p->f = max(p->f, p->r->f);
        return;
    }
    void update(Node*& p, int l, int r, int qp, int64_t v) {
        if (!p) p = new Node();
        if (l == r) return p->f = max(p->f, v), void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, v) : update(p->r, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void merge(Node*& p, Node* q, int l, int r, int64_t o0, int64_t o1, int64_t ov) {
        if (!p && !q) return;
        if (!p) return p = q, p->laz += o0, p->f += o0, void();
        if (!q) return p->laz += ov, p->f += ov, void();
        if (l == r) {
            f1 = max(f1, p->f + q->f);
            p->f = max(p->f + ov, o0 + q->f);
            return delete q;
        }
        pushDown(p), pushDown(q);
        int mid = (l + r) >> 1;
        merge(p->l, q->l, l, mid, o0, o1, ov), merge(p->r, q->r, mid + 1, r, o0, o1, ov);
        delete q;
        return pushUp(p);
    }
    void print(Node* p, int l, int r) {
        if (!p) return;
        cerr << '#' << l << ' ' << r << ' ' << p->f << endl;
        if (l == r) return;
        pushDown(p);
        int mid = (l + r) >> 1;
        print(p->l, l, mid), print(p->r, mid + 1, r);
        return;
    }

   public:
    int64_t f0, f1;

    SegmentTree(void) { root = nullptr, f0 = f1 = 0; }
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(root, 1, n, p, v); }
    void merge(SegmentTree* o) {
        int64_t v = max(o->f0, o->f1);
        f0 += v, f1 += v;
        merge(root, o->root, 1, n, f0 - v, f1 - v, v);
        return;
    }
    void print(void) { return print(root, 1, n); }
};

int read(void) {
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -f;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

SegmentTree* ST[maxn];

int c[maxn], w[maxn];
vector<vector<int>> graph;

void dfs(int p, int pre = -1) {
    ST[p]->update(c[p], w[p]);
    for (auto i : graph[p])
        if (i != pre) dfs(i, p), ST[p]->merge(ST[i]), delete ST[i], ST[i] = nullptr;
    return;
}

void solve(void) {
    int n = read();
    graph.clear(), graph.resize(n + 1);
    for (int i = 1; i <= n; i++) c[i] = read();
    for (int i = 1; i <= n; i++) w[i] = read();
    for (int i = 1, x, y; i < n; i++) x = read(), y = read(), graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) ST[i] = new SegmentTree(), ST[i]->resize(n);
    dfs(1);
    cout << max(ST[1]->f0, ST[1]->f1) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}
