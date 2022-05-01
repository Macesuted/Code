/**
 * @file 454.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

class UnionHeap {
   private:
    struct Node {
        Node *l, *r;
        int v, id, dep;
        Node(int v_, int id_) { l = r = NULL, dep = 1, v = v_, id = id_; }
    };

    int getDep(Node* p) { return p ? p->dep : 0; }
    Node* merge(Node* p, Node* v) {
        if (!v) return p;
        if (!p) return v;
        if (v->v < p->v) swap(v, p);
        p->l = merge(p->l, v);
        if (!p->r || p->l->dep > p->r->dep) swap(p->l, p->r);
        p->dep = (p->l ? p->l->dep : 0) + 1;
        return p;
    }

   public:
    Node* root;

    UnionHeap(void) { root = NULL; }
    void insert(int v, int id) { return root = merge(root, new Node(v, id)), void(); }
    void merge(UnionHeap& o) { return root = merge(root = merge(root, o.root->l), o.root->r), void(); }
    pii top(void) { return root ? pii{root->v, root->id} : pii{-1, -1}; }
} heap[maxn];

int p[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) heap[i].root = NULL;
    for (int i = 1, l, r; i <= n; i++) cin >> l >> r, heap[l].insert(r, i);
    for (int i = 1; i <= n; i++) {
        pii ret = heap[i].top();
        if (ret == pii{-1, -1} || ret.first < i) return cout << "D" << endl, void();
        p[ret.second] = i, vis[i] = false;
        if (ret.first < n) heap[ret.first + 1].merge(heap[i]);
    }
    int cnt = n;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            cnt--;
            int x = i;
            while (!vis[x]) vis[x] = true, x = p[x];
        }
    cout << "YF"[cnt & 1] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("fiend.in", "r", stdin), freopen("fiend.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
