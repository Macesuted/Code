/**
 * @file 104.cpp
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
        Node(int val_) { l = r = NULL, val = val_, rnk = rand(), siz = 1; }
    };

    Node *root;

    int getSiz(Node *p) { return p ? p->siz : 0; }
    void pushUp(Node *p) { return p->siz = getSiz(p->l) + getSiz(p->r) + 1, void(); }
    void splitV(Node *p, Node *&t1, Node *&t2, int v) {
        if (!p) return t1 = t2 = NULL, void();
        if (p->val <= v)
            t1 = p, splitV(p->r, t1->r, t2, v);
        else
            t2 = p, splitV(p->l, t1, t2->l, v);
        return pushUp(p);
    }
    void splitS(Node *p, Node *&t1, Node *&t2, int s) {
        if (!p) return t1 = t2 = NULL, void();
        if (1 + getSiz(p->l) <= s)
            t1 = p, splitS(p->r, t1->r, t2, s - 1 - getSiz(p->l));
        else
            t2 = p, splitS(p->l, t1, t2->l, s);
        return pushUp(p);
    }
    void merge(Node *&p, Node *t1, Node *t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            p = t1, merge(p->r, t1->r, t2);
        else
            p = t2, merge(p->l, t1, t2->l);
        return pushUp(p);
    }

   public:
    FhqTreap(void) { root = NULL; }
    void insert(int x) {
        Node *tr = NULL;
        splitV(root, root, tr, x), merge(root, root, new Node(x)), merge(root, root, tr);
        return;
    }
    void erase(int x) {
        Node *tr = NULL, *tp = NULL;
        splitV(root, root, tr, x), splitS(root, root, tp, getSiz(root) - 1);
        if (tp && tp->val == x) delete tp;
        merge(root, root, tr);
        return;
    }
    int queryRnk(int x) {
        Node *tr = NULL;
        splitV(root, root, tr, x - 1);
        int ans = getSiz(root) + 1;
        merge(root, root, tr);
        return ans;
    }
    int getRnk(int x) {
        Node *tr = NULL, *tp = NULL;
        splitS(root, root, tr, x - 1), splitS(tr, tp, tr, 1);
        int ans = (tp ? tp->val : 0);
        merge(root, root, tp), merge(root, root, tr);
        return ans;
    }
    int pre(int x) {
        Node *tr = NULL, *tp = NULL;
        splitV(root, root, tr, x - 1), splitS(root, root, tp, getSiz(root) - 1);
        int ans = (tp ? tp->val : 0);
        merge(root, root, tp), merge(root, root, tr);
        return ans;
    }
    int suc(int x) {
        Node *tr = NULL, *tp = NULL;
        splitV(root, root, tr, x), splitS(tr, tp, tr, 1);
        int ans = (tp ? tp->val : 0);
        merge(root, root, tp), merge(root, root, tr);
        return ans;
    }
} FHQ;

void solve(void) {
    int n;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) FHQ.insert(x);
        if (op == 2) FHQ.erase(x);
        if (op == 3) cout << FHQ.queryRnk(x) << endl;
        if (op == 4) cout << FHQ.getRnk(x) << endl;
        if (op == 5) cout << FHQ.pre(x) << endl;
        if (op == 6) cout << FHQ.suc(x) << endl;
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