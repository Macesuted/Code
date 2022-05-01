/**
 * @file 105.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int val, rnk, siz;
        bool rev;
        Node(int val_) { l = r = NULL, val = val_, rnk = rand(), siz = 1, rev = false; }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void rev(Node* p) { return p && (swap(p->l, p->r), p->rev ^= true), void(); }
    void pushDown(Node* p) { return p && p->rev && (rev(p->l), rev(p->r), p->rev = false), void(); }
    void pushUp(Node* p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void split(Node* p, Node*& t1, Node*& t2, int s) {
        if (!p) return t1 = t2 = NULL, void();
        pushDown(p);
        if (1 + getSiz(p->l) <= s)
            t1 = p, split(p->r, t1->r, t2, s - 1 - getSiz(p->l));
        else
            t2 = p, split(p->l, t1, t2->l, s);
        return pushUp(p);
    }
    void merge(Node*& p, Node* t1, Node* t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            pushDown(p = t1), merge(p->r, t1->r, t2);
        else
            pushDown(p = t2), merge(p->l, t1, t2->l);
        return pushUp(p);
    }
    void print(Node* p) {
        if (!p) return;
        pushDown(p);
        print(p->l), cout << p->val << ' ', print(p->r);
        return;
    }

   public:
    FhqTreap(void) { root = NULL; }
    void build(int n) {
        for (int i = 1; i <= n; i++) merge(root, root, new Node(i));
        return;
    }
    void reverse(int l, int r) {
        Node *tc = NULL, *tr = NULL;
        split(root, root, tr, r), split(root, root, tc, l - 1);
        rev(tc);
        merge(root, root, tc), merge(root, root, tr);
        return;
    }
    void print(void) { return print(root), cout << endl, void(); }
} FHQ;

void solve(void) {
    int n, m;
    cin >> n >> m;
    FHQ.build(n);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        FHQ.reverse(l, r);
    }
    FHQ.print();
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