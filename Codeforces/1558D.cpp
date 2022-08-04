/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T &t) {
    register T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 200005
#define mod 998244353

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int size, rank, val, sum;
        bool clear;
        Node(void) { l = r = NULL, size = 1, rank = rand(), sum = val = 0, clear = false; }
    };

    Node *nil, *root;

    Node *ensure(Node *p) { return p == NULL ? nil : p; }
    void markClear(Node *p) {
        if (p == NULL) return;
        p->clear = true, p->sum = p->val = 0;
        return;
    }
    void pushUp(Node *p) {
        Node *l = ensure(p->l), *r = ensure(p->r);
        p->size = 1 + l->size + r->size;
        p->sum = p->val + l->sum + r->sum;
        return;
    }
    void pushDown(Node *p) {
        if (p == NULL || !p->clear) return;
        p->clear = false, markClear(p->l), markClear(p->r);
        return;
    }
    void split(Node *root, Node *&tree1, Node *&tree2, int size) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        pushDown(root);
        if (1 + ensure(root->l)->size <= size)
            tree1 = root, split(root->r, tree1->r, tree2, size - 1 - ensure(root->l)->size);
        else
            tree2 = root, split(root->l, tree1, tree2->l, size);
        return pushUp(root);
    }
    void merge(Node *&root, Node *tree1, Node *tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if (tree1->rank < tree2->rank)
            pushDown(root = tree1), merge(root->r, tree1->r, tree2);
        else
            pushDown(root = tree2), merge(root->l, tree1, tree2->l);
        return pushUp(root);
    }
    void destroy(Node *p) {
        if (p == NULL) return;
        destroy(p->l), destroy(p->r);
        delete p;
        return;
    }

   public:
    FhqTreap(void) { nil = new Node, nil->size = 0, root = NULL; }
    void resize(int n) {
        destroy(root);
        while (n--) {
            Node *p = new Node;
            merge(root, root, p);
        }
        return;
    }
    void clear(void) { return markClear(root); }
    void insert(int l) {
        Node *p = new Node(), *treeR = NULL;
        p->val = true, pushUp(p);
        split(root, root, treeR, l);
        if (l) {
            Node *treeM = NULL;
            split(root, root, treeM, root->size - 1);
            treeM->val = false, pushUp(treeM);
            merge(root, root, treeM);
        }
        merge(root, root, p), merge(root, root, treeR);
        return;
    }
    void erase(int l) {
        Node *p = NULL, *treeR = NULL;
        split(root, root, treeR, l), split(treeR, p, treeR, 1);
        delete p;
        merge(root, root, treeR);
        return;
    }
    int query(void) { return root->sum; }
};

FhqTreap treap;

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

long long fac[maxn << 1], ifac[maxn << 1];

long long C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int main() {
    fac[0] = ifac[0] = 1;
    for (register int i = 1; i < (maxn << 1); i++) fac[i] = fac[i - 1] * i % mod;
    ifac[(maxn << 1) - 1] = Pow(fac[(maxn << 1) - 1], mod - 2);
    for (register int i = (maxn << 1) - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    srand(114514);
    int _ = read<int>();
    treap.resize(2e5);
    while (_--) {
        int n = read<int>(), m = read<int>();
        treap.clear();
        for (register int i = 1; i <= m; i++) {
            int x = read<int>(), y = read<int>();
            treap.erase(x - 1), treap.insert(y - 1);
        }
        int cnt = treap.query();
        write(C(2 * n - cnt - 1, n)), putch('\n');
    }
    return 0;
}