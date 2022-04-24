/**
 * @file 4923.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

class Splay {
   private:
    struct Node {
        Node *fa, *son[2];
        int64_t val;
        int cnt, lazy, siz;
        Node(int64_t val_, int cnt_ = 1) { fa = son[0] = son[1] = NULL, val = val_, lazy = 0, siz = cnt = cnt_; }
    };

    Node* root;
    vector<pii> cache;

    bool get(Node* p) { return p->fa->son[1] == p; }
    int getSiz(Node* p) { return p ? p->siz : 0; }
    void newNode(Node* f, bool w, int64_t v, int cnt_ = 1) { return f->son[w] = new Node(v, cnt_), f->son[w]->fa = f, void(); }
    void upd(Node* p, int v) { return p && (p->val += v, p->lazy += v), void(); }
    void pushDown(Node* p) { return p && (upd(p->son[0], p->lazy), upd(p->son[1], p->lazy), (p->lazy = 0)), void(); }
    void pushUp(Node* p) { return p && (p->siz = p->cnt + getSiz(p->son[0]) + getSiz(p->son[1])), void(); }
    void rotate(Node* p) {
        Node *f = p->fa, *g = f->fa;
        bool d = get(p);
        g && (g->son[get(f)] = p), p->fa = g;
        f->son[d] = p->son[!d], p->son[!d] && (p->son[!d]->fa = f);
        p->son[!d] = f, f->fa = p;
        return pushUp(f), pushUp(p), pushUp(g);
    }
    void down(Node* p) {
        stack<Node*> cache;
        while (p) cache.push(p), p = p->fa;
        while (!cache.empty()) pushDown(cache.top()), cache.pop();
        return;
    }
    Node* splay(Node* p, Node* tar = NULL) {
        down(p);
        for (Node* f = p->fa; f != tar; rotate(p), f = p->fa)
            if (f->fa != tar) rotate(get(p) == get(f) ? f : p);
        if (!tar) root = p;
        return p;
    }
    Node* splayV(int v, Node* tar = NULL) {
        Node* x = root;
        pushDown(root);
        for (Node* p = root; p; pushDown(p))
            if (p->val >= v)
                x = p, p = p->son[0];
            else
                p = p->son[1];
        return splay(x, tar);
    }
    Node* splayS(int s, Node* tar = NULL) {
        Node* p = root;
        pushDown(p);
        while (s <= getSiz(p->son[0]) || s > p->cnt + getSiz(p->son[0]))
            p = (s <= getSiz(p->son[0]) ? p->son[0] : (s -= p->cnt + getSiz(p->son[0]), p->son[1])), pushDown(p);
        return splay(p, tar);
    }
    void splayRange(int vl, int vr) {
        return splayS(getSiz(splayV(vl)->son[0])), root->son[1] && splayV(vr + 1, root), pushDown(root->son[1]);
    }
    void dfs(Node* p, int k) {
        if (!p) return;
        pushDown(p);
        cache.push_back({p->val - k, p->cnt});
        dfs(p->son[0], k), dfs(p->son[1], k);
        delete p;
        return;
    }

   public:
    Splay(void) { root = new Node(INT64_MAX), newNode(root, 0, INT64_MIN); }
    int getKTh(int k) { return splayS(k + 1)->val; }
    void insert(int v, int cnt = 1) {
        splayRange(v, v);
        root->son[1]->son[0] ? void(root->son[1]->son[0]->cnt += cnt) : newNode(root->son[1], 0, v, cnt);
        pushUp(root->son[1]->son[0]), pushUp(root->son[0]), pushUp(root);
        return;
    }
    void op(int k) {
        splayRange(k + 1, 2 * k), dfs(root->son[1]->son[0], k), root->son[1]->son[0] = NULL, upd(root->son[1], -k);
        for (auto i : cache) insert(i.first, i.second);
        cache.clear();
        return pushUp(root->son[1]), pushUp(root);
    }
} SPT;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, SPT.insert(x);
    while (m--) {
        int op, k;
        cin >> op >> k;
        if (op == 1)
            cout << SPT.getKTh(k) << endl;
        else
            SPT.op(k);
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
