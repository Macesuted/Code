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

#define maxn 500005

class SegmentTree {
   private:
    int tree[maxn << 3], lazy[maxn << 3];

    inline void pushDown(int p) {
        if (!lazy[p]) return;
        tree[p << 1] += lazy[p], tree[p << 1 | 1] += lazy[p];
        lazy[p << 1] += lazy[p], lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
        return;
    }
    void update(int p, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) return tree[p] += val, lazy[p] += val, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
        tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
        return;
    }

   public:
    int n;

    inline void update(int l, int r, long long val) { return update(1, 1, n, l, r, val); }
    inline int get(void) { return tree[1]; }
} sgtree;

struct Obj {
    int l, r, len;
    inline bool operator<(const Obj& oth) const { return this->len < oth.len; }
};

Obj a[maxn];
int b[maxn << 1], cntb = 0;

inline void upd(int p, int t) { return sgtree.update(a[p].l, a[p].r, t); }

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i].l = read<int>() + 1, a[i].r = read<int>() + 1, a[i].len = a[i].r - a[i].l + 1,
                                          b[++cntb] = a[i].l, b[++cntb] = a[i].r;
    sort(b + 1, b + cntb + 1);
    cntb = sgtree.n = unique(b + 1, b + cntb + 1) - b - 1;
    for (register int i = 1; i <= n; i++) a[i].l = lower_bound(b + 1, b + cntb + 1, a[i].l) - b,
                                          a[i].r = lower_bound(b + 1, b + cntb + 1, a[i].r) - b;
    sort(a + 1, a + n + 1);
    int answer = 0x3f3f3f3f;
    for (register int i = 1, j = 1; i <= n; i++) {
        upd(i, 1);
        while (sgtree.get() == m) upd(j, -1), answer = min(answer, a[i].len - a[j].len), j++;
    }
    write(answer == 0x3f3f3f3f ? -1 : answer), putch('\n');
    return 0;
}