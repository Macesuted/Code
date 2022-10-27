/**
 * @file 104.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-27
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

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int v, siz, rnk;
        Node(int _v) { l = r = nullptr, v = _v, siz = 1, rnk = rand(); }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void pushUp(Node* p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void splitV(Node* p, Node*& t1, Node*& t2, int v) {
        if (!p) return t1 = t2 = nullptr, void();
        if (p->v <= v)
            t1 = p, splitV(p->r, t1->r, t2, v);
        else
            t2 = p, splitV(p->l, t1, t2->l, v);
        return pushUp(p);
    }
    void splitS(Node* p, Node*& t1, Node*& t2, int s) {
        if (!p) return t1 = t2 = nullptr, void();
        if (1 + getSiz(p->l) <= s)
            t1 = p, splitS(p->r, t1->r, t2, s - 1 - getSiz(p->l));
        else
            t2 = p, splitS(p->l, t1, t2->l, s);
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
        Node* tl = nullptr;
        splitV(root, tl, root, v);
        return merge(tl, tl, new Node(v)), merge(root, tl, root);
    }
    void erase(int v) {
        Node *tl = nullptr, *tp = nullptr;
        splitV(root, tl, root, v), splitS(tl, tl, tp, getSiz(tl) - 1);
        delete tp;
        return merge(root, tl, root);
    }
    int getRank(int v) {
        Node* tl = nullptr;
        splitV(root, tl, root, v - 1);
        int ans = getSiz(tl) + 1;
        return merge(root, tl, root), ans;
    }
    int findRank(int v) {
        Node *tl = nullptr, *tp = nullptr;
        splitS(root, tl, root, v - 1), splitS(root, tp, root, 1);
        return merge(tl, tl, tp), merge(root, tl, root), tp->v;
    }
    int pre(int v) {
        Node *tl = nullptr, *tp = nullptr;
        splitV(root, tl, root, v - 1), splitS(tl, tl, tp, getSiz(tl) - 1);
        return merge(tl, tl, tp), merge(root, tl, root), tp->v;
    }
    int nex(int v) {
        Node *tr = nullptr, *tp = nullptr;
        splitV(root, root, tr, v), splitS(tr, tp, tr, 1);
        return merge(tr, tp, tr), merge(root, root, tr), tp->v;
    }
} FT;

void solve(void) {
    int n;
    cin >> n;
    while (n--) {
        int op, v;
        cin >> op >> v;
        if (op == 1)
            FT.insert(v);
        else if (op == 2)
            FT.erase(v);
        else if (op == 3)
            cout << FT.getRank(v) << endl;
        else if (op == 4)
            cout << FT.findRank(v) << endl;
        else if (op == 5)
            cout << FT.pre(v) << endl;
        else
            cout << FT.nex(v) << endl;
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