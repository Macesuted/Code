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

    inline int getSiz(Node* p) { return p == NULL ? 0 : p->size; }
    inline void pushUp(Node* p) { p->size = getSiz(p->l) + getSiz(p->r) + 1; }
    void split(Node* root, Node*& tree1, Node*& tree2, T val) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
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
            root = tree1, merge(root->r, tree1->r, tree2);
        else
            root = tree2, merge(root->l, tree1, tree2->l);
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
        destroy(p->l), destroy(p->r);
        delete p;
        return;
    }

   public:
    FhqTreap(void) { root = NULL; }
    ~FhqTreap(void) { destroy(root); }
    inline void insert(T val) {
        Node *tree1 = new Node(frand(), val), *tree2 = NULL;
        split(root, root, tree2, val);
        merge(root, root, tree1), merge(root, root, tree2);
        return;
    }
    inline void erase(T val) {
        Node *tree1 = NULL, *tree2 = NULL;
        split(root, root, tree1, val - 1), split(tree1, tree1, tree2, val);
        Node *tree1l = tree1->l, *tree1r = tree1->r;
        delete tree1;
        merge(root, root, tree1l), merge(root, root, tree1r), merge(root, root, tree2);
        return;
    }
    inline int rank(T val) {
        Node* tree1 = NULL;
        split(root, root, tree1, val - 1);
        int ret = getSiz(root);
        merge(root, root, tree1);
        return ret + 1;
    }
    inline T pre(T val) {
        Node* tree1 = NULL;
        split(root, root, tree1, val - 1);
        T ret = -2147483647;
        if (root != NULL) ret = getKTh(root, root->size);
        merge(root, root, tree1);
        return ret;
    }
    inline T suf(T val) {
        Node* tree1 = NULL;
        split(root, root, tree1, val);
        T ret = 2147483647;
        if (tree1 != NULL) ret = getKTh(tree1, 1);
        merge(root, root, tree1);
        return ret;
    }
};

#define maxn 50005

FhqTreap<int> tree[maxn << 2];
int a[maxn];

void build(int p, int l, int r) {
    for (register int i = l; i <= r; i++) tree[p].insert(a[i]);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    return;
}
void update(int p, int l, int r, int qp, int k) {
    tree[p].erase(a[qp]), tree[p].insert(k);
    if (l == r) return;
    int mid = (l + r) >> 1;
    qp <= mid ? update(p << 1, l, mid, qp, k) : update(p << 1 | 1, mid + 1, r, qp, k);
    return;
}
vector<FhqTreap<int>*> nodes;
void getNodes(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return nodes.push_back(&tree[p]);
    int mid = (l + r) >> 1;
    if (ql <= mid) getNodes(p << 1, l, mid, ql, qr);
    if (qr > mid) getNodes(p << 1 | 1, mid + 1, r, ql, qr);
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    build(1, 1, n);
    while (m--) {
        int opt = read<int>();
        if (opt == 1) {
            int l = read<int>(), r = read<int>(), k = read<int>(), answer = 0;
            nodes.clear(), getNodes(1, 1, n, l, r);
            for (vector<FhqTreap<int>*>::iterator i = nodes.begin(); i != nodes.end(); i++) answer += (*i)->rank(k) - 1;
            write(answer + 1), putch('\n');
        } else if (opt == 2) {
            int l = read<int>(), r = read<int>(), k = read<int>();
            nodes.clear(), getNodes(1, 1, n, l, r);
            int vl = -1, vr = 1e8;
            while (vl + 1 < vr) {
                int mid = (vl + vr) >> 1, cnt = 0;
                for (vector<FhqTreap<int>*>::iterator i = nodes.begin(); i != nodes.end(); i++)
                    cnt += (*i)->rank(mid) - 1;
                cnt < k ? vl = mid : vr = mid;
            }
            write(vl), putch('\n');
        } else if (opt == 3) {
            int p = read<int>(), k = read<int>();
            update(1, 1, n, p, k), a[p] = k;
        } else if (opt == 4) {
            int l = read<int>(), r = read<int>(), k = read<int>(), answer = -2147483647;
            nodes.clear(), getNodes(1, 1, n, l, r);
            for (vector<FhqTreap<int>*>::iterator i = nodes.begin(); i != nodes.end(); i++)
                answer = max(answer, (*i)->pre(k));
            write(answer), putch('\n');
        } else {
            int l = read<int>(), r = read<int>(), k = read<int>(), answer = 2147483647;
            nodes.clear(), getNodes(1, 1, n, l, r);
            for (vector<FhqTreap<int>*>::iterator i = nodes.begin(); i != nodes.end(); i++)
                answer = min(answer, (*i)->suf(k));
            write(answer), putch('\n');
        }
    }
    return 0;
}