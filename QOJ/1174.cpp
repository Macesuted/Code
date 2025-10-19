/**
 * @file 1174.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int maxn = 1e5 + 5;

int version;
class LeftistHeap {
   private:
    struct Node {
        Node *l, *r;
        int64_t val, laz;
        int dist, ver;
        Node(int64_t v) { l = r = nullptr, dist = laz = 0, val = v, ver = version; }
    };

    Node *root;

    Node *newNode(Node *p) { return p->ver == version ? p : new Node(*p); }

    void pushDown(Node *&p) {
        if (!p || !p->laz) return;
        p = newNode(p);
        if (p->l) p->l = newNode(p->l), p->l->laz += p->laz, p->l->val += p->laz;
        if (p->r) p->r = newNode(p->r), p->r->laz += p->laz, p->r->val += p->laz;
        p->laz = 0;
        return;
    }

    int getDist(Node *p) { return p ? p->dist : -1; }
    void merge(Node *&p, Node *t1, Node *t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        pushDown(t1), pushDown(t2);
        if (t1->val > t2->val) swap(t1, t2);
        p = newNode(t1), merge(p->r, t1->r, t2);
        if (getDist(p->l) < getDist(p->r)) swap(p->l, p->r);
        p->dist = getDist(p->r) + 1;
        return;
    }

   public:
    LeftistHeap(void) { root = nullptr; }

    void add(int64_t v) {
        if (!root) return;
        root = newNode(root);
        root->laz += v, root->val += v;
        return;
    }

    void push(int64_t v) { return merge(root, root, new Node(v)); }
    void pop(void) {
        if (!root) return;
        Node *p = root->l, *q = root->r;
        return merge(root, p, q);
    }

    void merge(LeftistHeap *t) { return merge(root, root, t->root); }
    int64_t top(void) { return root ? root->val : -1; }
};

LeftistHeap *f[maxn];
int a[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    f[1] = new LeftistHeap();
    f[1]->push(a[1]);
    f[2] = new LeftistHeap();
    f[2]->push(a[2]), f[2]->push(a[1] + a[2]);

    for (int i = 3; i <= n; i++) {
        version = i;
        f[i] = new LeftistHeap();
        for (int j = max(1, i - 3); j < i; j++) f[i]->merge(f[j]);
        f[i]->add(a[i]);
    }
    LeftistHeap ans = *f[n];
    if (n > 1) ans.merge(f[n - 1]);

    while (k--) cout << ans.top() << endl, ans.pop();

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
