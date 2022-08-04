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

#define maxn 1000005

struct Ask {
    int op, l, r;
};

int a[maxn];
Ask ask[maxn];

int tree[maxn << 2], lazy[maxn << 2];

inline void pushDown(int p, int l, int r) {
    if (!lazy[p]) return;
    int mid = (l + r) >> 1;
    lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
    lazy[p]--;
    tree[p << 1] = (mid - l + 1) * lazy[p], tree[p << 1 | 1] = (r - mid) * lazy[p];
    lazy[p] = 0;
    return;
}
void build(int p, int l, int r, int val) {
    lazy[p] = 0;
    if (l == r) return tree[p] = (a[l] >= val), void();
    int mid = (l + r) >> 1;
    build(p << 1, l, mid, val), build(p << 1 | 1, mid + 1, r, val);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
    return;
}
int sum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    pushDown(p, l, r);
    int mid = (l + r) >> 1, answer = 0;
    if (ql <= mid) answer += sum(p << 1, l, mid, ql, qr);
    if (qr > mid) answer += sum(p << 1 | 1, mid + 1, r, ql, qr);
    return answer;
}
void change(int p, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) return tree[p] = (r - l + 1) * val, lazy[p] = val + 1, void();
    pushDown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) change(p << 1, l, mid, ql, qr, val);
    if (qr > mid) change(p << 1 | 1, mid + 1, r, ql, qr, val);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
    return;
}

int n, m, q;

bool check(int lim) {
    build(1, 1, n, lim);
    for (register int i = 1; i <= m; i++) {
        int cnt = sum(1, 1, n, ask[i].l, ask[i].r);
        if (!ask[i].op) {
            if (ask[i].l <= ask[i].r - cnt) change(1, 1, n, ask[i].l, ask[i].r - cnt, 0);
            if (ask[i].r - cnt + 1 <= ask[i].r) change(1, 1, n, ask[i].r - cnt + 1, ask[i].r, 1);
        } else {
            if (ask[i].l <= ask[i].l + cnt - 1) change(1, 1, n, ask[i].l, ask[i].l + cnt - 1, 1);
            if (ask[i].l + cnt <= ask[i].r) change(1, 1, n, ask[i].l + cnt, ask[i].r, 0);
        }
    }
    return sum(1, 1, n, q, q);
}

int main() {
    n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1; i <= m; i++) ask[i].op = read<int>(), ask[i].l = read<int>(), ask[i].r = read<int>();
    q = read<int>();
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        check(mid) ? l = mid : r = mid - 1;
    }
    write(l), putch('\n');
    return 0;
}