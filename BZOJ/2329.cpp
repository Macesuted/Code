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
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
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

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int size, rank;
        int lazyReplace;
        bool lazySwap, lazyInvert;
        int val, sum, lMin, lMax, rMin, rMax;
        Node(void) {
            l = r = NULL, size = rank = sum = lMin = lMax = rMin = rMax = 0;
            lazyReplace = 0, lazySwap = lazyInvert = false;
        }
        Node(int _val) {
            l = r = NULL, rank = rand(), size = 1, sum = val = _val;
            lMin = rMin = min(_val, 0), lMax = rMax = max(_val, 0);
            lazyReplace = 0, lazySwap = lazyInvert = false;
        }
    };
    Node *nil, *root;

    inline Node* ensureReal(Node* p) { return p == NULL ? nil : p; }
    inline void markReplace(Node* p, int v) {
        if (p == NULL) return;
        p->lazyReplace = v, p->lazyInvert = p->lazySwap = false;
        p->val = v, p->sum = v * p->size;
        p->lMin = p->rMin = min(0, p->sum);
        p->lMax = p->rMax = max(0, p->sum);
        return;
    }
    inline void markSwap(Node* p) {
        if (p == NULL) return;
        p->lazySwap ^= true;
        swap(p->l, p->r), swap(p->lMin, p->rMin), swap(p->lMax, p->rMax);
        return;
    }
    inline void markInvert(Node* p) {
        if (p == NULL) return;
        p->lazyInvert ^= true;
        p->val = -p->val, p->sum = -p->sum, p->lMin = -p->lMin, p->lMax = -p->lMax, p->rMin = -p->rMin, p->rMax = -p->rMax;
        swap(p->lMin, p->lMax), swap(p->rMin, p->rMax);
        return;
    }
    inline void pushDown(Node* p) {
        if (p == NULL) return;
        if (p->lazyReplace) markReplace(p->l, p->lazyReplace), markReplace(p->r, p->lazyReplace), p->lazyReplace = 0;
        if (p->lazySwap) markSwap(p->l), markSwap(p->r), p->lazySwap = false;
        if (p->lazyInvert) markInvert(p->l), markInvert(p->r), p->lazyInvert = false;
        return;
    }
    void pushUp(Node* p) {
        Node *l = ensureReal(p->l), *r = ensureReal(p->r);
        p->size = 1 + l->size + r->size;
        p->sum = p->val + l->sum + r->sum;
        p->lMin = min(l->lMin, l->sum + p->val + r->lMin);
        p->lMax = max(l->lMax, l->sum + p->val + r->lMax);
        p->rMin = min(r->rMin, r->sum + p->val + l->rMin);
        p->rMax = max(r->rMax, r->sum + p->val + l->rMax);
        return;
    }
    void split(Node* root, Node*& tree1, Node*& tree2, int size) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        pushDown(root);
        if (1 + ensureReal(root->l)->size <= size)
            tree1 = root, split(root->r, tree1->r, tree2, size - 1 - ensureReal(root->l)->size);
        else
            tree2 = root, split(root->l, tree1, tree2->l, size);
        return pushUp(root);
    }
    void merge(Node*& root, Node* tree1, Node* tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if (tree1->rank < tree2->rank)
            pushDown(root = tree1), merge(root->r, tree1->r, tree2);
        else
            pushDown(root = tree2), merge(root->l, tree1, tree2->l);
        return pushUp(root);
    }

   public:
    FhqTreap(void) { nil = new Node, root = NULL; }
    inline void pushBack(int v) {
        Node* p = new Node(v);
        merge(root, root, p);
        return;
    }
    inline void Replace(int l, int r, int v) {
        Node *treeM = NULL, *treeR = NULL;
        split(root, root, treeM, l - 1), split(treeM, treeM, treeR, r - l + 1);
        markReplace(treeM, v);
        merge(root, root, treeM), merge(root, root, treeR);
        return;
    }
    inline void Swap(int l, int r) {
        Node *treeM = NULL, *treeR = NULL;
        split(root, root, treeM, l - 1), split(treeM, treeM, treeR, r - l + 1);
        markSwap(treeM);
        merge(root, root, treeM), merge(root, root, treeR);
        return;
    }
    inline void Invert(int l, int r) {
        Node *treeM = NULL, *treeR = NULL;
        split(root, root, treeM, l - 1), split(treeM, treeM, treeR, r - l + 1);
        markInvert(treeM);
        merge(root, root, treeM), merge(root, root, treeR);
        return;
    }
    inline int Query(int l, int r) {
        Node *treeM = NULL, *treeR = NULL;
        split(root, root, treeM, l - 1), split(treeM, treeM, treeR, r - l + 1);
        int ans = ((-treeM->lMin + 1) >> 1) + ((treeM->rMax + 1) >> 1);
        merge(root, root, treeM), merge(root, root, treeR);
        return ans;
    }
};

FhqTreap tree;

int main() {
    srand(time(NULL));
    int n = read<int>(), q = read<int>();
    for (register int i = 1; i <= n; i++) {
        char c = getch();
        while (c != '(' && c != ')') c = getch();
        tree.pushBack(c == '(' ? 1 : -1);
    }
    while (q--) {
        string str = getstr();
        int l = read<int>(), r = read<int>();
        if (str == "Replace")
            tree.Replace(l, r, getstr()[0] == '(' ? 1 : -1);
        else if (str == "Swap")
            tree.Swap(l, r);
        else if (str == "Invert")
            tree.Invert(l, r);
        else
            write(tree.Query(l, r)), putch('\n');
    }
    return 0;
}