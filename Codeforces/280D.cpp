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

#define maxn 100005

typedef pair<int, int> pii;

int a[maxn];

struct Segment {
    int l, r, sum;
    Segment(void) { l = 1, r = 0, sum = 0; }
    Segment(int L, int R, int SUM) : l(L), r(R), sum(SUM) {}
};
struct Node {
    int sum;
    Segment bl, bm, br;
    Segment sl, sm, sr;
};
struct retVal {
    int l, r, sum;
    Segment pl, pm, pr;
};

Node tree[maxn << 2];
bool rev[maxn << 2];

inline void work(int p) {
    tree[p].sum *= -1;
    tree[p].bl.sum *= -1, tree[p].bm.sum *= -1, tree[p].br.sum *= -1;
    tree[p].sl.sum *= -1, tree[p].sm.sum *= -1, tree[p].sr.sum *= -1;
    swap(tree[p].bl, tree[p].sl), swap(tree[p].bm, tree[p].sm), swap(tree[p].br, tree[p].sr);
    return;
}
inline void pushDown(int p) {
    if (!rev[p]) return;
    rev[p << 1] ^= true, rev[p << 1 | 1] ^= true;
    work(p << 1), work(p << 1 | 1);
    rev[p] = false;
    return;
}
inline void pushUp(int p, int l, int r) {
    Node &left = tree[p << 1], &right = tree[p << 1 | 1];
    tree[p].sum = left.sum + right.sum;
    tree[p].bl = left.bl;
    if (tree[p].bl.sum < left.sum + right.bl.sum) tree[p].bl = (Segment){l, right.bl.r, left.sum + right.bl.sum};
    tree[p].bm = left.bm.sum > right.bm.sum ? left.bm : right.bm;
    if (tree[p].bm.sum < left.br.sum + right.bl.sum) tree[p].bm = (Segment){left.br.l, right.bl.r, left.br.sum + right.bl.sum};
    tree[p].br = right.br;
    if (tree[p].br.sum < left.br.sum + right.sum) tree[p].br = (Segment){left.br.l, r, left.br.sum + right.sum};
    tree[p].sl = left.sl;
    if (tree[p].sl.sum > left.sum + right.sl.sum) tree[p].sl = (Segment){l, right.sl.r, left.sum + right.sl.sum};
    tree[p].sm = left.sm.sum < right.sm.sum ? left.sm : right.sm;
    if (tree[p].sm.sum > left.sr.sum + right.sl.sum) tree[p].sm = (Segment){left.sr.l, right.sl.r, left.sr.sum + right.sl.sum};
    tree[p].sr = right.sr;
    if (tree[p].sr.sum > left.sr.sum + right.sum) tree[p].sr = (Segment){left.sr.l, r, left.sr.sum + right.sum};
    return;
}
inline retVal merge(retVal left, retVal right) {
    if (left.pl.l == 1 && left.pr.r == 0) return right;
    retVal ans;
    ans.sum = left.sum + right.sum, ans.l = left.l, ans.r = right.r;
    ans.pl = left.pl;
    if (ans.pl.sum < left.sum + right.pl.sum) ans.pl = (Segment){ans.l, right.pl.r, left.sum + right.pl.sum};
    ans.pm = left.pm.sum > right.pm.sum ? left.pm : right.pm;
    if (ans.pm.sum < left.pr.sum + right.pl.sum) ans.pm = (Segment){left.pr.l, right.pl.r, left.pr.sum + right.pl.sum};
    ans.pr = right.pr;
    if (ans.pr.sum < left.pr.sum + right.sum) ans.pr = (Segment){left.pr.l, ans.r, left.pr.sum + right.sum};
    return ans;
}
void build(int p, int l, int r) {
    rev[p] = false;
    if (l == r) {
        tree[p].sum = a[l];
        tree[p].bl = tree[p].bm = tree[p].br = tree[p].sl = tree[p].sm = tree[p].sr = (Segment){l, l, a[l]};
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    return pushUp(p, l, r);
}
void update(int p, int l, int r, int qp, int val) {
    if (l == r) return tree[p].sum = tree[p].bl.sum = tree[p].bm.sum = tree[p].br.sum =
                           tree[p].sl.sum = tree[p].sm.sum = tree[p].sr.sum = val,
                       void();
    pushDown(p);
    int mid = (l + r) >> 1;
    qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
    return pushUp(p, l, r);
}
retVal query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return (retVal){l, r, tree[p].sum, tree[p].bl, tree[p].bm, tree[p].br};
    pushDown(p);
    int mid = (l + r) >> 1;
    retVal ans;
    if (ql <= mid) ans = merge(ans, query(p << 1, l, mid, ql, qr));
    if (qr > mid) ans = merge(ans, query(p << 1 | 1, mid + 1, r, ql, qr));
    return ans;
}
void reverse(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return rev[p] ^= true, work(p), void();
    pushDown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) reverse(p << 1, l, mid, ql, qr);
    if (qr > mid) reverse(p << 1 | 1, mid + 1, r, ql, qr);
    return pushUp(p, l, r);
}

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    build(1, 1, n);
    int q = read<int>();
    while (q--) {
        if (!read<int>()) {
            int p = read<int>(), val = read<int>();
            update(1, 1, n, p, val);
        } else {
            int l = read<int>(), r = read<int>(), k = read<int>(), ans = 0;
            static stack<pii> S;
            while (!S.empty()) S.pop();
            for (register int i = 1; i <= k; i++) {
                retVal ret = query(1, 1, n, l, r);
                if (ret.pm.sum <= 0) break;
                ans += ret.pm.sum;
                reverse(1, 1, n, ret.pm.l, ret.pm.r), S.push((pii){ret.pm.l, ret.pm.r});
            }
            while (!S.empty()) reverse(1, 1, n, S.top().first, S.top().second), S.pop();
            write(ans), putch('\n');
        }
    }
    return 0;
}