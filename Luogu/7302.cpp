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

struct Obj {
    int t, p, v, k1, k2;
    inline bool operator<(const Obj& oth) const { return this->k1 > oth.k1; }
};

Obj a[maxn];
int b[maxn];

int tree[maxn];
void insert(int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[i] = max(tree[i], val);
    return;
}
int maxVal(int p) {
    int ans = 0;
    for (register int i = p; i; i -= i & -i) ans = max(ans, tree[i]);
    return ans;
}

int main() {
    int w = read<int>(), n = read<int>();
    for (register int i = 1; i <= n; i++) a[i].t = read<int>(), a[i].p = read<int>(), a[i].v = read<int>(),
                                          a[i].k1 = a[i].p + 2 * a[i].t, b[i] = a[i].k2 = a[i].p - 2 * a[i].t;
    sort(b + 1, b + n + 1);
    int btail = unique(b + 1, b + n + 1) - b - 1;
    for (register int i = 1; i <= n; i++) a[i].k2 = lower_bound(b + 1, b + btail + 1, a[i].k2) - b;
    sort(a + 1, a + n + 1);
    for (register int i = 1; i <= n; i++) insert(a[i].k2, maxVal(a[i].k2) + a[i].v);
    write(maxVal(maxn - 1)), putch('\n');
    return 0;
}