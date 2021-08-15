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

class SegmentTree {
   private:
    long long sum[maxn << 2], maxVal[maxn << 2];
    int n;

    void build(int p, int l, int r, int a[]) {
        if (l == r) return sum[p] = maxVal[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        sum[p] = sum[p << 1] + sum[p << 1 | 1], maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }
    void update(int p, int l, int r, int ql, int qr, int mod) {
        if (ql <= l && r <= qr && maxVal[p] < mod) return;
        if (l == r) return sum[p] = maxVal[p] = sum[p] % mod, void();
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, mod);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, mod);
        sum[p] = sum[p << 1] + sum[p << 1 | 1], maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }
    void update(int p, int l, int r, int qp, int val) {
        if (l == r) return sum[p] = maxVal[p] = val, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
        sum[p] = sum[p << 1] + sum[p << 1 | 1], maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }
    long long getSum(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[p];
        int mid = (l + r) >> 1;
        long long ans = 0;
        if (ql <= mid) ans += getSum(p << 1, l, mid, ql, qr);
        if (qr > mid) ans += getSum(p << 1 | 1, mid + 1, r, ql, qr);
        return ans;
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(int a[]) { return build(1, 1, n, a); }
    inline void update(int l, int r, int mod) { return update(1, 1, n, l, r, mod); }
    inline void update(int p, int val) { return update(1, 1, n, p, val); }
    inline long long getSum(int l, int r) { return getSum(1, 1, n, l, r); }
};

SegmentTree tree;

int a[maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    tree.resize(n), tree.build(a);
    while (m--) {
        int opt = read<int>();
        if (opt == 1) {
            int l = read<int>(), r = read<int>();
            write(tree.getSum(l, r)), putch('\n');
        } else if (opt == 2) {
            int l = read<int>(), r = read<int>(), mod = read<int>();
            tree.update(l, r, mod);
        } else {
            int p = read<int>(), val = read<int>();
            tree.update(p, val);
        }
    }
    return 0;
}