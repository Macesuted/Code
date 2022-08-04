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
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
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
inline void write(const T& t) {
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

template <typename T>
class FhqTreap {
   private:
    struct Node {
        T val;
        int rank, size;
        Node *l, *r;
        bool rev;
        Node(int rnk = 0, T v = 0) { rank = rnk, size = 1, l = r = NULL, val = v, rev = false; }
    };
    static const long long kMul = 0x9ddfea08eb382d69ULL;
    long long Seed = 1145141919810;

    Node* root;

    inline long long fingerPrint(long long x) {
        x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47;
        return x * kMul;
    }
    inline int frand(void) { return Seed += fingerPrint(Seed); }

    inline int getSiz(Node* p) { return p == NULL ? 0 : p->size; }
    inline void pushDown(Node* p) {
        if (!p->rev) return;
        swap(p->l, p->r), p->rev = false;
        if (p->l != NULL) p->l->rev = !p->l->rev;
        if (p->r != NULL) p->r->rev = !p->r->rev;
        return;
    }
    inline void pushUp(Node* p) { p->size = getSiz(p->l) + getSiz(p->r) + 1; }
    void split(Node* root, Node*& tree1, Node*& tree2, int siz) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        pushDown(root);
        if (getSiz(root->l) + 1 <= siz)
            tree1 = root, split(root->r, tree1->r, tree2, siz - getSiz(root->l) - 1);
        else
            tree2 = root, split(root->l, tree1, tree2->l, siz);
        return pushUp(root);
    }
    void merge(Node*& root, Node* tree1, Node* tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if ((tree1->rank) < (tree2->rank))
            pushDown(root = tree1), merge(root->r, tree1->r, tree2);
        else
            pushDown(root = tree2), merge(root->l, tree1, tree2->l);
        return pushUp(root);
    }
    void print(Node* p) {
        pushDown(p);
        if (p->l != NULL) print(p->l);
        write(p->val), putch(' ');
        if (p->r != NULL) print(p->r);
        return;
    }
    void destroy(Node* p) {
        if (p == NULL) return;
        destroy(p->l), destroy(p->r);
        delete p;
        return;
    }

   public:
    FhqTreap(void) { root = NULL; }
    ~FhqTreap(void) { destroy(root); }
    void build(int n) {
        for (register int i = 1; i <= n; i++) merge(root, root, new Node(frand(), i));
        return;
    }
    void reverse(int l, int r) {
        Node *tree1 = NULL, *tree2 = NULL;
        split(root, root, tree1, l - 1), split(tree1, tree1, tree2, r - l + 1);
        tree1->rev = !tree1->rev;
        merge(root, root, tree1), merge(root, root, tree2);
        return;
    }
    inline void print(void) { return print(root); }
};

FhqTreap<int> treap;

int main() {
    int n = read<int>(), m = read<int>();
    treap.build(n);
    for (register int i = 1, l, r; i <= m; i++) {
        l = read<int>(), r = read<int>();
        treap.reverse(l, r);
    }
    treap.print(), putch('\n');
    return 0;
}