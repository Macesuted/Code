/**
 * @file 1051G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
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
        int64_t sum, ans;
        int val, siz, rnk;
        Node(int val_) { l = r = nullptr, sum = ans = val = val_, siz = 1, rnk = rand(); }
    };

    Node* root;

    void pushUp(Node* p) {
        p->sum = p->ans = p->siz = 0;
        if (p->l) p->sum += p->l->sum, p->ans += p->l->ans, p->siz += p->l->siz;
        p->sum += p->val, p->ans += 1LL * p->val * p->siz + p->val, p->siz++;
        if (p->r) p->sum += p->r->sum, p->ans += 1LL * p->r->sum * p->siz + p->r->ans, p->siz += p->r->siz;
        return;
    }
    void split(Node* p, Node*& t1, Node*& t2, int v) {
        if (!p) return t1 = t2 = nullptr, void();
        if (p->val >= v)
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
    void mergeTo(Node* p, FhqTreap* o) {
        if (!p) return;
        o->insert(p->val), mergeTo(p->l, o), mergeTo(p->r, o);
        return delete p;
    }

   public:
    FhqTreap(void) { root = nullptr; }
    void insert(int v) {
        Node* tr = nullptr;
        return split(root, root, tr, v), merge(root, root, new Node(v)), merge(root, root, tr);
    }
    void mergeTo(FhqTreap* o) { return mergeTo(root, o); }
    int getSiz(void) { return root ? root->siz : 0; }
    int64_t getSum(void) { return root ? root->sum : 0; }
    int64_t getAns(void) { return root ? root->ans : 0; }
};

#define maxn 200005

set<tuple<int, int, FhqTreap*>> S;

void solve(void) {
    int n;
    cin >> n;
    int64_t ori = 0, ans = 0;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y, ori += 1LL * (x + 1) * y;
        auto p = S.lower_bound({x + 1, 0, nullptr});
        auto BST = new FhqTreap();
        BST->insert(y);
        auto v = make_tuple(x, x, BST);
        if (p != S.begin() && x <= get<1>(*--p) + 1)
            v = *p, S.erase(p), ans -= 1LL * get<0>(v) * get<2>(v)->getSum() + get<2>(v)->getAns(), BST->mergeTo(get<2>(v)),
            get<1>(v)++;
        p = S.lower_bound({get<1>(v) + 1, 0, nullptr});
        if (p != S.end() && get<0>(*p) == get<1>(v) + 1) {
            auto u = *p;
            S.erase(p), ans -= 1LL * get<0>(u) * get<2>(u)->getSum() + get<2>(u)->getAns();
            if (get<2>(v)->getSiz() < get<2>(u)->getSiz()) swap(v, u);
            get<2>(u)->mergeTo(get<2>(v)), get<0>(v) = min(get<0>(v), get<0>(u)), get<1>(v) = max(get<1>(v), get<1>(u));
        }
        S.insert(v), ans += 1LL * get<0>(v) * get<2>(v)->getSum() + get<2>(v)->getAns();
        cout << ans - ori << endl;
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