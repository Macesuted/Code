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

#define maxn 100005

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int sum, indeg;
        Node(void) { l = r = NULL, sum = 0; }
    };
    int n;

    vector<Node*> roots;

    inline Node* createNode(void) { return new Node; }

    void build(Node*& p, int l, int r) {
        if (p == NULL) p = createNode(), p->indeg++;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p->l, l, mid), build(p->r, mid + 1, r);
        p->sum = p->l->sum + p->r->sum;
        return;
    }
    void change(Node*& p, Node* old, int l, int r, int qp, int val) {
        if (p == NULL) p = createNode(), p->indeg++;
        *p = *old;
        if (l == r) return p->sum = val, void();
        int mid = (l + r) >> 1;
        (qp <= mid) ? (change(p->l = NULL, old->l, l, mid, qp, val), p->r->indeg++) : (change(p->r = NULL, old->r, mid + 1, r, qp, val), p->l->indeg++);
        p->sum = p->l->sum + p->r->sum;
        return;
    }
    int get(Node* p, int l, int r, int qp) {
        if (l == r) return p->sum;
        int mid = (l + r) >> 1;
        return qp <= mid ? get(p->l, l, mid, qp) : get(p->r, mid + 1, r, qp);
    }

    void destory(Node* p) {
        if (--p->indeg) return;
        if (p->l != NULL) destory(p->l);
        if (p->r != NULL) destory(p->r);
        delete p;
        return;
    }

   public:
    SegmentTree(void) { clear(); }
    ~SegmentTree(void) { clear(); }
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
    inline void change(int from, int p, int val) { return change(roots[createRoot()], roots[from], 1, n, p, val); }
    inline int get(int ver, int p) { return createRoot(ver), get(roots[ver], 1, n, p); }
};

int a[maxn], b[maxn];
SegmentTree tree;

int main() {
    int type = read<int>(), n = read<int>(), q = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    tree.build(m);
    for (register int i = n; i >= 1; i--) tree.change(n - i, a[i], i);
    while (q--) {
        int l = read<int>();
        for (register int i = 1; i <= l; i++) b[i] = read<int>();
        int p = tree.get(n, b[1]);
        for (register int i = 2; i <= l && p; i++) p = tree.get(n - p, b[i]);
        putstr(p ? "Yes" : "No"), putch('\n');
    }
    return 0;
}