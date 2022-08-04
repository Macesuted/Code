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
        int rank, size, ver, deg;
        Node *l, *r;
        Node(int rnk = 0, T v = 0, int version = 0) {
            rank = rnk, size = 1, l = r = NULL, val = v, ver = version, deg = 0;
        }
        Node(const Node* p) { *this = *p; }
    };
    static const long long kMul = 0x9ddfea08eb382d69ULL;
    long long Seed = 1145141919810;

    vector<Node*> roots;
    int version;

    inline long long fingerPrint(long long x) {
        x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47;
        return x * kMul;
    }
    inline int frand(void) { return Seed += fingerPrint(Seed); }

    inline Node*& createRoot(int ver) {
        if (roots[ver] == NULL)
            roots.push_back(NULL);
        else
            roots.push_back(new Node(roots[ver]));
        return roots.back();
    }
    inline int getSiz(Node* p) { return p == NULL ? 0 : p->size; }
    inline void pushUp(Node* p) { p->size = getSiz(p->l) + getSiz(p->r) + 1; }
    inline void upgrade(Node*& p) {
        if (p->ver != version) p = new Node(p), p->ver = version;
        return;
    }
    void split(Node* root, Node*& tree1, Node*& tree2, T val) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        upgrade(root);
        if (root->val <= val)
            tree1 = root, split(root->r, tree1->r, tree2, val);
        else
            tree2 = root, split(root->l, tree1, tree2->l, val);
        return pushUp(root);
    }
    void merge(Node*& root, Node* tree1, Node* tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if ((tree1->rank) < (tree2->rank))
            upgrade(root = tree1), merge(root->r, tree1->r, tree2);
        else
            upgrade(root = tree2), merge(root->l, tree1, tree2->l);
        return pushUp(root);
    }
    T getKTh(Node* root, int rank) {
        while (getSiz(root->l) + 1 != rank)
            if (getSiz(root->l) >= rank)
                root = root->l;
            else
                rank -= getSiz(root->l) + 1, root = root->r;
        return root->val;
    }
    void destroy(Node* p) {
        if (p == NULL) return;
        if (--p->deg) return;
        destroy(p->l), destroy(p->r);
        delete p;
        return;
    }

   public:
    FhqTreap(void) { roots.push_back(NULL); }
    ~FhqTreap(void) {
        // for (typename vector<Node*>::iterator i = roots.begin(); i != roots.end(); i++) destroy(*i);
    }
    void insert(int ver, T val) {
        version++;
        Node *&root = createRoot(ver), *tree1 = new Node(frand(), val, version), *tree2 = NULL;
        split(root, root, tree2, val);
        merge(root, root, tree1), merge(root, root, tree2);
        return;
    }
    void erase(int ver, T val) {
        version++;
        Node *&root = createRoot(ver), *tree1 = NULL, *tree2 = NULL;
        split(root, root, tree1, val - 1), split(tree1, tree1, tree2, val);
        if (tree1 == NULL) return merge(root, root, tree2);
        Node *tree1l = tree1->l, *tree1r = tree1->r;
        merge(root, root, tree1l), merge(root, root, tree1r), merge(root, root, tree2);
        return;
    }
    int rank(int ver, T val) {
        version++;
        Node *&root = createRoot(ver), *tree1 = NULL;
        split(root, root, tree1, val - 1);
        int ret = getSiz(root);
        merge(root, root, tree1);
        return ret + 1;
    }
    T getKTh(int ver, int rank) {
        version++;
        Node*& root = createRoot(ver);
        return getKTh(root, rank);
    }
    T pre(int ver, T val) {
        version++;
        Node *&root = createRoot(ver), *tree1 = NULL;
        split(root, root, tree1, val - 1);
        T ret = -2147483647;
        if (root != NULL) ret = getKTh(root, root->size);
        merge(root, root, tree1);
        return ret;
    }
    T suf(int ver, T val) {
        version++;
        Node *&root = createRoot(ver), *tree1 = NULL;
        split(root, root, tree1, val);
        T ret = 2147483647;
        if (tree1 != NULL) ret = getKTh(tree1, 1);
        merge(root, root, tree1);
        return ret;
    }
};

FhqTreap<int> tree;

int main() {
    int n = read<int>();
    while (n--) {
        int v = read<int>(), opt = read<int>(), x = read<int>();
        if (opt == 1)
            tree.insert(v, x);
        else if (opt == 2)
            tree.erase(v, x);
        else if (opt == 3)
            write(tree.rank(v, x)), putch('\n');
        else if (opt == 4)
            write(tree.getKTh(v, x)), putch('\n');
        else if (opt == 5)
            write(tree.pre(v, x)), putch('\n');
        else
            write(tree.suf(v, x)), putch('\n');
    }
    return 0;
}