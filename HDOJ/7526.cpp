/**
 * @file 7526.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const uint32_t U = ((uint32_t)1 << 31) - 1;

class Trie {
   private:
    struct Node {
        Node* son[2];
        uint32_t same, T, S1, S2;
        Node(void) { son[0] = son[1] = nullptr, same = T = S1 = S2 = 0; }
    };

    Node* root;

    void update(Node* p, uint32_t T, uint32_t S1, uint32_t S2) {
        if (T == 0 && S1 == 0 && S2 == 0) return;
        p->S1 = ((p->S1 ^ S2) & (p->T ^ (p->T & T))) | (S1 & T);
        p->T |= T;
        p->S2 = (p->S2 ^ S2) & (U ^ p->T);
        return;
    }
    void pushDown(Node* p, int d) {
        if (p->T == 0 && p->S1 == 0 && p->S2 == 0) return;
        if (p->S2 >> d & 1) swap(p->son[0], p->son[1]);
        if (p->T >> d & 1) {
            int b = p->S1 >> d & 1;
            if (!p->son[b]) swap(p->son[b], p->son[!b]);
            if (p->son[b] && p->son[!b]) merge(p->son[b], p->son[!b], d - 1);
        }
        if (p->son[0]) update(p->son[0], p->T, p->S1, p->S2);
        if (p->son[1]) update(p->son[1], p->T, p->S1, p->S2);
        p->T = p->S1 = p->S2 = 0;
        return;
    }
    void pushUp(Node* p, int d) {
        p->same = 0;
        if (p->son[0] && p->son[1]) p->same |= 1 << d;
        if (p->son[0]) p->same |= p->son[0]->same;
        if (p->son[1]) p->same |= p->son[1]->same;
        return;
    }
    void merge(Node*& p, Node*& q, int d) {
        if (!p) return p = q, void();
        if (!q) return;
        if (d == -1) return delete q, q = nullptr, void();
        pushDown(p, d), pushDown(q, d);
        merge(p->son[0], q->son[0], d - 1), merge(p->son[1], q->son[1], d - 1);
        delete q, q = nullptr;
        return pushUp(p, d);
    }
    void insert(Node*& p, int d, uint32_t v) {
        if (!p) p = new Node();
        if (d == -1) return;
        pushDown(p, d);
        insert(p->son[v >> d & 1], d - 1, v);
        return pushUp(p, d);
    }
    uint32_t query(Node*& p, int d, uint32_t v) {
        if (d == -1) return 0;
        pushDown(p, d);
        int b = v >> d & 1;
        if (p->son[!b]) return uint32_t(1) << d | query(p->son[!b], d - 1, v);
        return query(p->son[b], d - 1, v);
    }
    void destroy(Node* p) {
        if (!p) return;
        destroy(p->son[0]), destroy(p->son[1]);
        delete p;
        return;
    }

   public:
    Trie(void) { root = nullptr; }
    ~Trie(void) { destroy(root); }
    void insert(uint32_t v) { return insert(root, 30, v); }
    void updateOr(uint32_t v) { return update(root, v, v, 0); }
    void updateAnd(uint32_t v) { return update(root, U ^ v, 0, 0); }
    void updateXor(uint32_t v) { return update(root, 0, 0, v); }
    uint32_t query(uint32_t v) { return query(root, 30, v); }
};

void solve(void) {
    int n, m;
    cin >> n >> m;
    Trie Tr;
    for (int i = 1, v; i <= n; i++) cin >> v, Tr.insert(v);
    while (m--) {
        int op, a;
        cin >> op >> a;
        if (op == 1)
            Tr.insert(a);
        else if (op == 2)
            Tr.updateOr(a);
        else if (op == 3)
            Tr.updateAnd(a);
        else if (op == 4)
            Tr.updateXor(a);
        else
            cout << Tr.query(a) << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}