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

class SegmentTree {
   public:
    struct Node {
        Node *l, *r;
        int maxBef, maxAft, sum;
        Node(void) { l = r = NULL; }
        inline Node operator+(const Node& oth) const {
            Node l = *this, r = oth, p;
            p.maxBef = max(l.maxBef, l.sum + r.maxBef);
            p.maxAft = max(l.maxAft + r.sum, r.maxAft);
            p.sum = l.sum + r.sum;
            return p;
        }
    };

   private:
    inline Node merge(Node* l, Node* r) {
        Node p = *l + *r;
        p.l = l, p.r = r;
        return p;
    }

    vector<Node*> roots;

    int n;

    void build(Node*& p, int l, int r) {
        if (p == NULL) p = new Node();
        if (l == r) return p->maxBef = p->maxAft = p->sum = 1, void();
        int mid = (l + r) >> 1;
        build(p->l, l, mid), build(p->r, mid + 1, r);
        *p = merge(p->l, p->r);
        return;
    }
    void update(Node*& p, Node* old, int l, int r, int qp) {
        p = new Node(), *p = *old;
        if (l == r) return p->maxBef = p->maxAft = 0, p->sum = -1, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, old->l, l, mid, qp) : update(p->r, old->r, mid + 1, r, qp);
        *p = merge(p->l, p->r);
        return;
    }
    Node ask(Node* p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return *p;
        int mid = (l + r) >> 1;
        if (qr <= mid) return ask(p->l, l, mid, ql, qr);
        if (ql > mid) return ask(p->r, mid + 1, r, ql, qr);
        return ask(p->l, l, mid, ql, qr) + ask(p->r, mid + 1, r, ql, qr);
    }

   public:
    inline void resize(int _n) { n = _n, roots.push_back(NULL); }
    inline void build(void) {
        Node* newRoot = NULL;
        build(newRoot, 1, n);
        return roots.push_back(newRoot);
    }
    inline void update(int p) {
        Node* newRoot = NULL;
        update(newRoot, roots.back(), 1, n, p);
        return roots.push_back(newRoot);
    }
    inline Node ask(int ver, int l, int r) { return ask(roots[ver], 1, n, l, r); }
};

#define maxn 20005

typedef pair<int, int> pii;

SegmentTree tree;

int a[maxn];
pii b[maxn];
int p[5];

inline bool check(int v) {
    int val = tree.ask(v, p[1], p[2] - 1).maxAft + tree.ask(v, p[2], p[3]).sum + tree.ask(v, p[3] + 1, p[4]).maxBef;
    return val >= 0;
}

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) b[i] = (pii){a[i] = read<int>(), i};
    sort(b + 1, b + n + 1);
    tree.resize(n), tree.build();
    for (register int i = 1; i < n; i++) tree.update(b[i].second);
    int q = read<int>(), lastans = 0;
    while (q--) {
        for (register int i = 1; i <= 4; i++) p[i] = (read<int>() + lastans) % n + 1;
        sort(p + 1, p + 5);
        if (check(n)) {
            write(lastans = b[n].first), putch('\n');
            continue;
        }
        int l = 1, r = n;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            check(mid) ? l = mid : r = mid;
        }
        write(lastans = b[l].first), putch('\n');
    }
    return 0;
}