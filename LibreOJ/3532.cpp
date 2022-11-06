/**
 * @file 3532.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-28
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

#define maxn 100005

class LinkCutTree {
   private:
    struct Node {
        Node *son[2], *fa;
        int siz, col, lefCol, rigCol, laz, sum;
        bool rev;
        Node(void) { son[0] = son[1] = fa = nullptr, col = lefCol = rigCol = laz = sum = 0, rev = false; }
    };

    vector<Node> a;
    int timc;

    bool isRig(Node* p) { return p->fa->son[1] == p; }
    bool isRoot(Node* p) { return !p->fa || (p->fa->son[0] != p && p->fa->son[1] != p); }
    int getSiz(Node* p) { return p ? p->siz : 0; }
    int getLefCol(Node* p) { return p ? p->lefCol : -1; }
    int getRigCol(Node* p) { return p ? p->rigCol : -1; }
    int getSum(Node* p) { return p ? p->sum : 0; }
    void rev(Node* p) { return p ? p->rev ^= true, swap(p->lefCol, p->rigCol), swap(p->son[0], p->son[1]) : void(); }
    void mark(Node* p, int v) { return p ? p->col = p->lefCol = p->rigCol = p->laz = v, p->sum = p->siz - 1, void() : void(); }
    void pushDown(Node* p) {
        if (p->laz) mark(p->son[0], p->laz), mark(p->son[1], p->laz), p->laz = 0;
        if (p->rev) rev(p->son[0]), rev(p->son[1]), p->rev = false;
        return;
    }
    void pushUp(Node* p) {
        if (!p) return;
        p->siz = 1 + getSiz(p->son[0]) + getSiz(p->son[1]);
        p->lefCol = (p->son[0] ? p->son[0]->lefCol : p->col), p->rigCol = (p->son[1] ? p->son[1]->rigCol : p->col);
        p->sum = getSum(p->son[0]) + (getRigCol(p->son[0]) == p->col) + (p->col == getLefCol(p->son[1])) + getSum(p->son[1]);
        return;
    }
    void rotate(Node* p) {
        Node *f = p->fa, *g = f->fa;
        bool d = isRig(p);
        if (!isRoot(f)) f->fa->son[isRig(f)] = p;
        if (p->son[!d]) p->son[!d]->fa = f;
        f->son[d] = p->son[!d], p->son[!d] = f, p->fa = g, f->fa = p;
        return pushUp(f), pushUp(p), pushUp(p->fa);
    }
    void down(Node* p) {
        stack<Node*> S;
        while (!isRoot(p)) S.push(p), p = p->fa;
        S.push(p);
        while (!S.empty()) pushDown(S.top()), S.pop();
        return;
    }
    void splay(Node* p) {
        down(p);
        for (Node* f = p->fa; !isRoot(p); rotate(p), f = p->fa)
            if (!isRoot(f)) rotate(isRig(f) == isRig(p) ? f : p);
        return;
    }
    int access(Node* p) {
        Node* x = nullptr;
        for (; p; x = p, p = p->fa) splay(p), p->son[1] = x, pushUp(p);
        return splay(x), x->sum;
    }
    void makeRoot(Node* p) { return access(p), splay(p), rev(p); }
    void markChain(Node* p) { return access(p), splay(p), mark(p, ++timc); }

   public:
    void clear(void) { return a.clear(), void(); }
    void build(int n, int fa[]) {
        a.resize((timc = n) + 1);
        for (int i = 1; i <= n; i++) a[i].col = i, a[i].fa = (fa[i] ? &a[fa[i]] : nullptr);
        return;
    }
    int access(int p) { return access(&a[p]); }
    void makeRoot(int p) { return makeRoot(&a[p]); }
    void markChain(int p) { return markChain(&a[p]); }
} LCT;

int fa[maxn];
vector<vector<int>> graph;

void dfs(int p, int pre = 0) {
    fa[p] = pre;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs(1);
    LCT.build(n, fa);
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) LCT.makeRoot(x), LCT.markChain(y);
        if (op == 2) LCT.makeRoot(x), cout << LCT.access(y) << endl;
    }
    graph.clear(), LCT.clear();
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("edge.in", "r", stdin), freopen("edge.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}