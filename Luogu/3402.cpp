/**
 * @author Macesuted (macesuted@outlook.com)
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

class UnionSet {
   private:
    struct Node {
        Node *l, *r;
        int fa, siz, indeg;
        Node(void) { l = r = NULL, fa = siz = 0; }
    };
    int n;

    vector<Node*> roots;

    inline Node* createNode(void) { return new Node; }

    void build(Node*& p, int l, int r) {
        if (p == NULL) p = createNode(), p->indeg++;
        if (l == r) return p->fa = l, void();
        int mid = (l + r) >> 1;
        build(p->l, l, mid), build(p->r, mid + 1, r);
        return;
    }
    void change(Node*& p, Node* old, int l, int r, int qp, int val) {
        if (p == NULL) p = createNode(), p->indeg++;
        *p = *old;
        if (l == r) return p->fa = val, void();
        int mid = (l + r) >> 1;
        return (qp <= mid) ? (change(p->l = NULL, old->l, l, mid, qp, val), p->r->indeg++)
                           : (change(p->r = NULL, old->r, mid + 1, r, qp, val), p->l->indeg++),
               void();
    }
    void add(Node* p, int l, int r, int qp) {
        if (l == r) return p->siz++, void();
        int mid = (l + r) >> 1;
        return (qp <= mid) ? add(p->l, l, mid, qp) : add(p->r, mid + 1, r, qp);
    }
    Node* get(Node* p, int l, int r, int qp) {
        if (l == r) return p;
        int mid = (l + r) >> 1;
        return qp <= mid ? get(p->l, l, mid, qp) : get(p->r, mid + 1, r, qp);
    }
    Node* getfa(Node* root, int val) {
        Node* fa = get(root, 1, n, val);
        if (val == fa->fa) return fa;
        return getfa(root, fa->fa);
    }

    void destory(Node* p) {
        if (--p->indeg) return;
        if (p->l != NULL) destory(p->l);
        if (p->r != NULL) destory(p->r);
        delete p;
        return;
    }

   public:
    UnionSet(void) { clear(); }
    ~UnionSet(void) { clear(); }
    void clear(void) {
        for (vector<Node*>::iterator i = roots.begin(); i != roots.end(); i++) destory(*i);
        roots.clear();
        return;
    }
    inline int createRoot(int pre = -1) {
        roots.push_back(new Node);
        if (pre != -1) *roots.back() = *roots[pre];
        return roots.size() - 1;
    }
    inline void build(int tn) { return clear(), build(roots[createRoot()], 1, n = tn); }
    void merge(int x, int y) {
        Node* root = roots[createRoot(roots.size() - 1)];
        Node *fx = getfa(root, x), *fy = getfa(root, y);
        if (fx->fa == fy->fa) return;
        if (fx->siz < fy->siz) swap(fx, fy);
        change(root, roots[roots.size() - 2], 1, n, fy->fa, fx->fa);
        if (fx->siz == fy->siz) add(root, 1, n, fx->fa);
        return;
    }
    bool check(int x, int y) {
        Node* root = roots[createRoot(roots.size() - 1)];
        Node *fx = getfa(root, x), *fy = getfa(root, y);
        return fx->fa == fy->fa;
    }
};

UnionSet S;

int main() {
    int n = read<int>(), m = read<int>();
    S.build(n);
    while (m--) {
        int opt = read<int>();
        if (opt == 1)
            S.merge(read<int>(), read<int>());
        else if (opt == 2)
            S.createRoot(read<int>());
        else
            write(S.check(read<int>(), read<int>())), putch('\n');
    }
    return 0;
}