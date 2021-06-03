/**
 * @author Macesuted (macesuted@qq.com)
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

typedef pair<int, int> pii;

struct Node {
    int l, r, n, nl, nr, nlr;
};

int a[maxn];

Node tree[maxn << 2];
int lazy[maxn << 2];

inline Node merge(Node l, Node r) {
    Node answer;
    answer.l = l.l, answer.r = r.r;
    answer.n = min(l.nr + r.nl - (l.r == r.l), min(l.n + r.nl, l.nr + r.n));
    answer.nl = min(l.nlr + r.nl - (l.r == r.l), min(l.nl + r.nl, l.nlr + r.n));
    answer.nr = min(l.nr + r.nlr - (l.r == r.l), min(l.n + r.nlr, l.nr + r.nr));
    answer.nlr = min(l.nlr + r.nlr - (l.r == r.l), min(l.nl + r.nlr, l.nlr + r.nr));
    return answer;
}
inline void upd(int p, int val) { return tree[p].l += val, tree[p].r += val, lazy[p] += val, void(); }
inline void pushDown(int p) {
    if (!lazy[p]) return;
    upd(p << 1, lazy[p]), upd(p << 1 | 1, lazy[p]), lazy[p] = 0;
    return;
}
inline void pushUp(int p) { return tree[p] = merge(tree[p << 1], tree[p << 1 | 1]), void(); }
void build(int p, int l, int r) {
    if (l == r) {
        tree[p].l = tree[p].r = a[l];
        tree[p].n = lazy[p] = 0;
        tree[p].nl = tree[p].nr = tree[p].nlr = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    return pushUp(p);
}
void update(int p, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) return upd(p, val);
    pushDown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
    if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
    return pushUp(p);
}
Node getAns(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    pushDown(p);
    int mid = (l + r) >> 1;
    if (qr <= mid) return getAns(p << 1, l, mid, ql, qr);
    if (ql > mid) return getAns(p << 1 | 1, mid + 1, r, ql, qr);
    return merge(getAns(p << 1, l, mid, ql, qr), getAns(p << 1 | 1, mid + 1, r, ql, qr));
}

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1; i < n; i++) a[i] = a[i + 1] - a[i];
    build(1, 1, --n);
    int q = read<int>();
    while (q--) {
        char c = getstr()[0];
        if (c == 'A') {
            int from = read<int>(), to = read<int>(), a = read<int>(), b = read<int>();
            if (from > 1) update(1, 1, n, from - 1, from - 1, a);
            if (from < to) update(1, 1, n, from, to - 1, b);
            if (to <= n) update(1, 1, n, to, to, -(a + (to - from) * b));
        } else {
            int from = read<int>(), to = read<int>();
            if (from == to)
                write(1), putch('\n');
            else {
                Node ret = getAns(1, 1, n, from, to - 1);
                write(ret.nlr), putch('\n');
            }
        }
    }
    return 0;
}