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

long long sum1, sum2, sum3;
struct Node {
    long long sum1, sum2, sum3;
};
Node tree[maxn << 2];
long long lazy[maxn << 2];
inline void upd(int p, int l, int r, long long val) {
    tree[p].sum1 += (r - l + 1) * val;
    tree[p].sum2 += 1LL * (l + r) * (r - l + 1) / 2 * val;
    tree[p].sum3 += ((1LL * r * (r + 1) * (2 * r + 1) / 6) - (1LL * (l - 1) * l * (2 * l - 1) / 6)) * val;
    lazy[p] += val;
    return;
}
inline void pushDown(int p, int l, int r) {
    int mid = (l + r) >> 1;
    upd(p << 1, l, mid, lazy[p]), upd(p << 1 | 1, mid + 1, r, lazy[p]);
    lazy[p] = 0;
    return;
}
void update(int p, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) return upd(p, l, r, val);
    pushDown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
    if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
    tree[p].sum1 = tree[p << 1].sum1 + tree[p << 1 | 1].sum1;
    tree[p].sum2 = tree[p << 1].sum2 + tree[p << 1 | 1].sum2;
    tree[p].sum3 = tree[p << 1].sum3 + tree[p << 1 | 1].sum3;
    return;
}
void getAns(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum1 += tree[p].sum1, sum2 += tree[p].sum2, sum3 += tree[p].sum3, void();
    pushDown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) getAns(p << 1, l, mid, ql, qr);
    if (qr > mid) getAns(p << 1 | 1, mid + 1, r, ql, qr);
    return;
}

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

int main() {
    int n = read<int>(), q = read<int>();
    while (q--) {
        char c = getch();
        while (c != 'C' && c != 'Q') c = getch();
        if (c == 'C') {
            int l = read<int>(), r = read<int>() - 1, v = read<int>();
            update(1, 1, n, l, r, v);
        } else {
            long long l = read<int>(), r = read<int>() - 1;
            sum1 = sum2 = sum3 = 0;
            getAns(1, 1, n, l, r);
            long long up = (r - l + 1 - l * r) * sum1 + (l + r) * sum2 - sum3,
                      down = (r - l + 2) * (r - l + 1) / 2, GCD = gcd(up, down);
            write(up / GCD), putch('/'), write(down / GCD), putch('\n');
        }
    }
    return 0;
}