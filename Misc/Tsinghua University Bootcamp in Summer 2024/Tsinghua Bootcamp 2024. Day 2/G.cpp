/**
 * @file G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

class LeftistTree {
   private:
    struct Node {
        Node *l, *r;
        int dist, val;
        Node(int v) { l = r = nullptr, dist = 0, val = v; }
    };

    Node *root;

    int getDist(Node *p) { return p ? p->dist : -1; }
    void merge(Node *&p, Node *t1, Node *t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->val > t2->val) swap(t1, t2);
        p = new Node(*t1), merge(p->r, t1->r, t2);
        if (getDist(p->l) < getDist(p->r)) swap(p->l, p->r);
        p->dist = getDist(p->r) + 1;
        return;
    }

   public:
    LeftistTree(void) { root = nullptr; }

    void push(int v) { return merge(root, root, new Node(v)); }
    void pop(void) {
        Node *p = root->l, *q = root->r;
        return merge(root, p, q);
    }
    void merge(LeftistTree *t) { return merge(root, root, t->root); }
    int top(void) { return root ? root->val : -1; }
};

LeftistTree *LFT[maxn];

void solve(void) {
    int n, lst = 0;
    cin >> n;
    LFT[0] = new LeftistTree();
    for (int i = 1; i <= n; i++) {
        int op, a, b;
        cin >> op >> a, LFT[i] = new LeftistTree(*LFT[(a + lst) % i]);
        if (op == 1)
            cin >> b, LFT[i]->push((b + 17 * lst) % int(1e9 + 1));
        else if (op == 2)
            cin >> b, LFT[i]->merge(LFT[(b + 13 * lst) % i]);

        int ans = LFT[i]->top();
        if (ans == -1)
            cout << "empty" << endl;
        else {
            cout << ans << endl, lst = (lst + ans) % 239017;
            if (op == 3) LFT[i]->pop();
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