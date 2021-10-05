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
        Node(int rnk = 0, T v = 0) { rank = rnk, size = 1, l = r = NULL, val = v; }
    };
    static const long long kMul = 0x9ddfea08eb382d69ULL;
    long long Seed = 1145141919810;

    Node* root;

    inline long long fingerPrint(long long x) {
        x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47;
        return x * kMul;
    }
    inline int frand(void) { return Seed += fingerPrint(Seed); }

    inline void update(Node* p) { p->size = (p->l == NULL ? 0 : p->l->size) + (p->r == NULL ? 0 : p->r->size) + 1; }
    void split(Node* root, Node*& tree1, Node*& tree2, T val) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (root->val <= val)
            tree1 = root, split(root->r, tree1->r, tree2, val);
        else
            tree2 = root, split(root->l, tree1, tree2->l, val);
        return update(root);
    }
    void merge(Node*& root, Node* tree1, Node* tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if ((tree1->rank) < (tree2->rank))
            root = tree1, merge(root->r, tree1->r, tree2);
        else
            root = tree2, merge(root->l, tree1, tree2->l);
        return update(root);
    }
    void insert(Node*& root, T val) {
        Node *tree1 = NULL, *tree2 = NULL, *p = new Node(frand(), val);
        split(root, tree1, tree2, val);
        merge(tree1, tree1, p), merge(root, tree1, tree2);
        return;
    }
    void erase(Node*& root, T val) {
        Node *tree1 = NULL, *tree2 = NULL, *tree3 = NULL;
        split(root, tree1, tree2, val - 1), split(tree2, tree2, tree3, val);
        Node *tree2l = tree2->l, *tree2r = tree2->r;
        delete tree2;
        tree2 = NULL;
        merge(tree2, tree2l, tree2r), merge(tree1, tree1, tree2), merge(root, tree1, tree3);
        return;
    }
    T getKTh(Node* root, int rank) {
        if (root == NULL || root->size < rank) throw "[ERROR]: Can't find 'k'th element in Fhq_Treap.";
        while ((root->l == NULL ? 0 : root->l->size) + 1 != rank)
            if (root->l != NULL && root->l->size >= rank)
                root = root->l;
            else
                rank -= (root->l == NULL ? 0 : root->l->size) + 1, root = root->r;
        return root->val;
    }
    int rank(Node*& root, T val) {
        Node *tree1 = NULL, *tree2 = NULL;
        split(root, tree1, tree2, val - 1);
        if (tree1 == NULL) return 1;
        int ret = tree1->size;
        merge(root, tree1, tree2);
        return ret + 1;
    }
    T getPre(Node*& root, T val) {
        Node *tree1 = NULL, *tree2 = NULL;
        split(root, tree1, tree2, val - 1);
        T ret;
        try {
            ret = getKTh(tree1, tree1->size);
        } catch (...) {
            throw "[ERROR]: There doesn't have any element smaller than the element which value equal to 'val' in Fhq_Treap.";
        }
        merge(root, tree1, tree2);
        return ret;
    }
    T getScc(Node*& root, T val) {
        Node *tree1 = NULL, *tree2 = NULL;
        split(root, tree1, tree2, val);
        T ret;
        try {
            ret = getKTh(tree2, 1);
        } catch (...) {
            throw "[ERROR]: There doesn't have any element bigger than the element which value equal to 'val' in Fhq_Treap.";
        }
        merge(root, tree1, tree2);
        return ret;
    }
    void destroy(Node* p) {
        if (p == NULL) return;
        if (p->l != NULL) destroy(p->l);
        if (p->r != NULL) destroy(p->r);
        delete p;
        return;
    }
    void print(Node* p) {
        if (p == NULL) {
            cerr << "EMPTY" << endl;
            return;
        }
        cerr << p << ' ' << p->l << ' ' << p->r << ' ' << p->size << ' ' << p->rank << ' ' << p->val << endl;
        if (p->l != NULL) print(p->l);
        if (p->r != NULL) print(p->r);
        return;
    }

   public:
    FhqTreap(void) { root = NULL; }
    ~FhqTreap(void) { destroy(root); }
    inline void insert(T val) { return insert(root, val); }
    inline void erase(T val) { return erase(root, val); }
    inline T getKTh(int rank) { return getKTh(root, rank); }
    inline int rank(T val) { return rank(root, val); }
    inline T getPre(T val) { return getPre(root, val); }
    inline T getScc(T val) { return getScc(root, val); }
    inline int size(void) { return root->size; }
    inline void print(void) {
        cerr << "#####" << endl;
        print(root);
        cerr << "$$$$$" << endl;
    }
};

FhqTreap<int> tree;

int main() {
    int n = read<int>(), q = read<int>();
    for (register int i = 1; i <= n; i++) tree.insert(read<int>());
    int answer = 0, last = 0;
    while (q--) {
        int opt = read<int>(), x = read<int>() ^ last, ans = 0;
        if (opt == 1)
            tree.insert(x);
        else if (opt == 2)
            tree.erase(x);
        else if (opt == 3)
            ans = tree.rank(x);
        else if (opt == 4)
            ans = tree.getKTh(x);
        else if (opt == 5)
            ans = tree.getPre(x);
        else
            ans = tree.getScc(x);
        if (opt > 2) answer ^= (last = ans);
    }
    write(answer), putch('\n');
    return 0;
}