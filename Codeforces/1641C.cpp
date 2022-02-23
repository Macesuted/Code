/**
 * @file 1641C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
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

class SegmentTree {
   private:
    int tree[maxn << 2];
    int n;

    int getMin(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1, ans = numeric_limits<int>::max();
        if (ql <= mid) ans = min(ans, getMin(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = min(ans, getMin(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = min(tree[p], v), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
        return;
    }

   public:
    SegmentTree(void) { memset(tree, 0x3f, sizeof(tree)); }
    void resize(int _n) { return n = _n, void(); }
    int getMin(int l, int r) { return getMin(1, 1, n, l, r); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
} ST;

set<int> alive;

void solve(void) {
    int n = read<int>(), q = read<int>();
    for (int i = 1; i <= n; i++) alive.insert(i);
    ST.resize(n);
    alive.insert(0), alive.insert(n + 1);
    for (int i = 1; i <= q; i++) {
        int t = read<int>();
        if (t == 0) {
            int l = read<int>(), r = read<int>(), x = read<int>();
            if (x == 0) {
                auto p = alive.lower_bound(l);
                while (*p <= r) alive.erase(*p), p = alive.lower_bound(l);
            } else
                ST.update(l, r);
        } else {
            int p = read<int>();
            if (alive.find(p) == alive.end()) {
                putstr("NO\n");
                continue;
            }
            int pl = *--alive.find(p), pr = *++alive.find(p);
            if (ST.getMin(pl + 1, p) < pr)
                putstr("YES\n");
            else
                putstr("N/A\n");
        }
    }
    return;
}

bool mem2;

int main() {
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
