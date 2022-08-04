/**
 * @file 2002.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

using namespace std;
#include <bits/stdc++.h>

bool mem1;

#define maxn 200005

class LinkCutTree {
   private:
    struct Node {
        Node *fa, *son[2];
        bool rev;
        int siz;
        Node(void) { fa = son[0] = son[1] = NULL, rev = false, siz = 1; }
    };

    Node tree[maxn];
    int n;

    bool isRoot(Node* p) { return p && (!p->fa || (p->fa->son[0] != p && p->fa->son[1] != p)); }
    bool get(Node* p) { return p == p->fa->son[1]; }
    int getSiz(Node* p) { return p ? p->siz : 0; }
    void rev(Node* p) { return p && (swap(p->son[0], p->son[1]), p->rev ^= true), void(); }
    void pushDown(Node* p) { return p && p->rev && (rev(p->son[0]), rev(p->son[1]), p->rev = false), void(); }
    void pushUp(Node* p) { return p && (p->siz = 1 + getSiz(p->son[0]) + getSiz(p->son[1])), void(); }
    void down(Node* p) {
        stack<Node*> cache;
        while (!isRoot(p)) cache.push(p), p = p->fa;
        pushDown(p);
        while (!cache.empty()) pushDown(cache.top()), cache.pop();
        return;
    }
    void rotate(Node* p) {
        Node *f = p->fa, *g = f->fa;
        bool d = get(p);
        g && !isRoot(f) && (g->son[get(f)] = p), p->fa = g;
        f->son[d] = p->son[!d], p->son[!d] && (p->son[!d]->fa = f);
        p->son[!d] = f, f->fa = p;
        return pushUp(f), pushUp(p), pushUp(g);
    }
    void splay(Node* p) {
        down(p);
        for (Node* f = p->fa; !isRoot(p); rotate(p), f = p->fa)
            if (!isRoot(f)) rotate(get(f) == get(p) ? f : p);
        return;
    }
    void access(Node* p) {
        for (Node* x = NULL; p; x = p, p = p->fa) splay(p), p->son[1] = x, pushUp(p);
        return;
    }
    void makeRoot(Node* p) { return access(p), splay(p), rev(p); }
    void link(Node* p, Node* fa) { return makeRoot(p), p->fa = fa, void(); }
    void cut(Node* p, Node* fa) {
        return makeRoot(p), access(fa), splay(fa), p->fa = fa->son[get(p)] = NULL, pushUp(fa);
    }

   public:
    void build(int n_, int fa[]) {
        n = n_;
        for (int i = 0; i < n; i++) tree[i].fa = &tree[fa[i]];
        return;
    }
    void link(int p, int fa) { return link(&tree[p], &tree[fa]); }
    void cut(int p, int fa) { return cut(&tree[p], &tree[fa]); }
    int query(int p) { return makeRoot(&tree[n]), access(&tree[p]), splay(&tree[p]), tree[p].siz; }
} LCT;

int fa[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0, x; i < n; i++) cin >> x, fa[i] = min(n, i + x);
    LCT.build(n, fa);
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p;
            cin >> p;
            cout << LCT.query(p) - 1 << endl;
        } else {
            int p, x;
            cin >> p >> x;
            LCT.cut(p, fa[p]), LCT.link(p, fa[p] = min(n, p + x));
        }
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
