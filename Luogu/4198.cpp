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

#define maxn 100005

class SegmentTree {
   private:
    struct Double {
        long long up, down;
        inline bool operator<(const Double& oth) const { return this->up * oth.down < oth.up * this->down; }
    };
    struct Node {
        int ans;
        Double maxVal;
        Node(void) { maxVal = (Double){0, 1}, ans = 0; }
    };
    Node tree[maxn << 2];
    int n;

    int getAns(int p, int l, int r, Double limit) {
        if (!(limit < tree[p].maxVal)) return 0;
        if (l == r) return 1;
        int mid = (l + r) >> 1;
        if (tree[p << 1].maxVal < limit) return getAns(p << 1 | 1, mid + 1, r, limit);
        return tree[p].ans - tree[p << 1].ans + getAns(p << 1, l, mid, limit);
    }
    void update(int p, int l, int r, int qp, int val) {
        if (l == r) return tree[p].ans = 1, tree[p].maxVal = (Double){val, l}, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
        tree[p].ans = tree[p << 1].ans + getAns(p << 1 | 1, mid + 1, r, tree[p << 1].maxVal);
        tree[p].maxVal = max(tree[p << 1].maxVal, tree[p << 1 | 1].maxVal);
        return;
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void update(int p, int val) { return update(1, 1, n, p, val); }
    inline int getAns(void) { return tree[1].ans; }
};

SegmentTree tree;

int main() {
    int n = read<int>(), m = read<int>();
    tree.resize(n);
    while (m--) {
        int p = read<int>(), v = read<int>();
        tree.update(p, v);
        write(tree.getAns()), putch('\n');
    }
    return 0;
}