/**
 * @file 1440.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

bool mem1;

#define maxn 500005

class SegmentTree {
   private:
    struct Node {
        int sum, lsum, rsum, ans;
        Node operator+(const Node& oth) const {
            Node ret;
            ret.sum = sum + oth.sum;
            ret.lsum = max(lsum, sum + oth.lsum);
            ret.rsum = max(oth.rsum, oth.sum + rsum);
            ret.ans = max({ans, oth.ans, rsum + oth.lsum});
            return ret;
        }
    };
    Node a, b;
    Node tree[maxn << 2];

   public:
    void build(int p, int l, int r, int a[]) {
        if (l == r) return tree[p].sum = tree[p].lsum = tree[p].rsum = tree[p].ans = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
        return;
    }
    void upd(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].sum = tree[p].lsum = tree[p].rsum = tree[p].ans = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? upd(p << 1, l, mid, qp, v) : upd(p << 1 | 1, mid + 1, r, qp, v);
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
        return;
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }
} ST;

int a[maxn];

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    ST.build(1, 1, n, a);
    while (m--) {
        int opt = read<int>();
        if (opt == 1) {
            int l = read<int>(), r = read<int>();
            if (l > r) swap(l, r);
            write(ST.query(1, 1, n, l, r).ans), putch('\n');
        } else {
            int p = read<int>(), x = read<int>();
            ST.upd(1, 1, n, p, x);
        }
    }
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
