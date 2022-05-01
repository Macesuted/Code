/**
 * @file 1632D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-02
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

#define maxn 200005

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int a[maxn];

class SegmentTree {
   private:
    int tree[maxn << 2], n;

    void build(int p, int l, int r, int a[]) {
        if (l == r) return tree[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        tree[p] = gcd(tree[p << 1], tree[p << 1 | 1]);
        return;
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = gcd(ans, query(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = gcd(ans, query(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} SGT;

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    SGT.resize(n), SGT.build(a);
    int ans = 0;
    for (int i = 1, p = 1, lastP = 0; i <= n; i++) {
        while (p <= i && SGT.query(p, i) < i - p + 1) p++;
        while (p - 1 > lastP && SGT.query(p - 1, i) >= i - (p - 1) + 1) p--;
        if (SGT.query(p, i) == i - p + 1) lastP = i, p = i + 1, ans++;
        write(ans), putch(" \n"[i == n]);
    }
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
