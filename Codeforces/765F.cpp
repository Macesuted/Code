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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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
#define maxm 300005

int a[maxn];

class SegmentTree {
   private:
    struct Node {
        int ans;
        vector<int> arr;
    };

    Node tree[maxn << 2];

    int n;

    void build(int p, int l, int r) {
        tree[p].arr.resize(r - l + 1);
        for (register int i = l; i <= r; i++) tree[p].arr[i - l] = a[i];
        sort(tree[p].arr.begin(), tree[p].arr.end());
        tree[p].ans = 0x3f3f3f3f;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return;
    }

    void reCalc(int p, int val) {
        int t = upper_bound(tree[p].arr.begin(), tree[p].arr.end(), val) - tree[p].arr.begin();
        if (t != (int)tree[p].arr.size()) tree[p].ans = min(tree[p].ans, tree[p].arr[t] - val);
        if (t > 0) tree[p].ans = min(tree[p].ans, val - tree[p].arr[t - 1]);
        return;
    }

    void update(int p, int l, int r, int ql, int qr, int val, int lim = 0x3f3f3f3f) {
        if (ql <= l && r <= qr) {
            reCalc(p, val);
            if (tree[p].ans >= lim) return;
        }
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val, lim);
        if (ql <= mid) update(p << 1, l, mid, ql, qr, val, min(lim, tree[p << 1 | 1].ans));
        tree[p].ans = min(tree[p].ans, min(tree[p << 1].ans, tree[p << 1 | 1].ans));
        return;
    }

    int getAns(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].ans;
        int mid = (l + r) >> 1;
        if (qr <= mid) return getAns(p << 1, l, mid, ql, qr);
        if (ql > mid) return getAns(p << 1 | 1, mid + 1, r, ql, qr);
        return min(getAns(p << 1, l, mid, ql, qr), getAns(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(void) { return build(1, 1, n); }
    inline void update(int l, int r, int val) { return update(1, 1, n, l, r, val); }
    inline int getAns(int l, int r) { return getAns(1, 1, n, l, r); }
};

SegmentTree tree;

struct Ask {
    int id, l;
};

vector<Ask> ask[maxn];
int answer[maxm];

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int m = read<int>();
    for (register int i = 1; i <= m; i++) {
        int l = read<int>(), r = read<int>();
        ask[r].push_back((Ask){i, l});
    }
    tree.resize(n), tree.build();
    for (register int r = 2; r <= n; r++) {
        tree.update(1, r - 1, a[r]);
        for (vector<Ask>::iterator i = ask[r].begin(); i != ask[r].end(); i++)
            answer[i->id] = tree.getAns(i->l, r);
    }
    for (register int i = 1; i <= m; i++) write(answer[i]), putch('\n');
    return 0;
}