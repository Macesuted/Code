/**
 * @file 1523G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-21
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

#define maxn 50005
#define maxm 100005

typedef pair<int, int> pii;

class SegmentTree2 {
   private:
    class SegmentTree {
       private:
        struct Node {
            int minVal;
            Node *l, *r;
            Node(void) { l = r = NULL, minVal = numeric_limits<int>::max(); }
        };

        Node* root;
        int n;

        void update(Node*& p, int l, int r, int qp, int v) {
            if (p == NULL) p = new Node();
            if (l == r) return p->minVal = min(p->minVal, v), void();
            if (p->l == NULL) p->l = new Node();
            if (p->r == NULL) p->r = new Node();
            int mid = (l + r) >> 1;
            qp <= mid ? update(p->l, l, mid, qp, v) : update(p->r, mid + 1, r, qp, v);
            p->minVal = min(p->l->minVal, p->r->minVal);
            return;
        }
        int getMin(Node* p, int l, int r, int ql, int qr) {
            if (p == NULL) return numeric_limits<int>::max();
            if (ql <= l && r <= qr) return p->minVal;
            int mid = (l + r) >> 1, ans = numeric_limits<int>::max();
            if (ql <= mid) ans = min(ans, getMin(p->l, l, mid, ql, qr));
            if (qr > mid) ans = min(ans, getMin(p->r, mid + 1, r, ql, qr));
            return ans;
        }

       public:
        SegmentTree(void) { root = NULL; }
        void resize(int _n) { return n = _n, void(); }
        void update(int p, int v) { return update(root, 1, n, p, v); }
        int getMin(int l, int r) { return getMin(root, 1, n, l, r); }
    };

    struct Node {
        SegmentTree tree;
        Node *l, *r;
        Node(int n) { l = r = NULL, tree.resize(n); }
    };

    Node* root;
    int n;

    void update(Node*& p, int l, int r, int x, int y, int v) {
        if (p == NULL) p = new Node(n);
        p->tree.update(y, v);
        if (l == r) return;
        int mid = (l + r) >> 1;
        x <= mid ? update(p->l, l, mid, x, y, v) : update(p->r, mid + 1, r, x, y, v);
        return;
    }
    int getMin(Node* p, int l, int r, int xl, int xr, int yl, int yr) {
        if (p == NULL) return numeric_limits<int>::max();
        if (xl <= l && r <= xr) return p->tree.getMin(yl, yr);
        int mid = (l + r) >> 1, ans = numeric_limits<int>::max();
        if (xl <= mid) ans = min(ans, getMin(p->l, l, mid, xl, xr, yl, yr));
        if (xr > mid) ans = min(ans, getMin(p->r, mid + 1, r, xl, xr, yl, yr));
        return ans;
    }

   public:
    SegmentTree2(void) { root = NULL; }
    void resize(int _n) { return n = _n, void(); }
    void update(int x, int y, int v) { return update(root, 1, n, x, y, v); }
    int getMin(int xl, int xr, int yl, int yr) { return getMin(root, 1, n, xl, xr, yl, yr); }
} ST;

struct Seg {
    int l, r, id;
};

Seg a[maxm], b[maxm];
int ans[maxn], n;

int solve(int l, int r) {
    int p = ST.getMin(l, r, l, r);
    if (p == numeric_limits<int>::max()) return 0;
    int ans = b[p].r - b[p].l + 1;
    if (b[p].l > l) ans += solve(l, b[p].l - 1);
    if (b[p].r < r) ans += solve(b[p].r + 1, r);
    return ans;
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) a[i].l = read<int>(), a[i].r = read<int>(), a[i].id = i, b[i] = a[i];
    sort(a + 1, a + m + 1, [](Seg a, Seg b) { return a.r - a.l > b.r - b.l; });
    ST.resize(n);
    for (int i = n, j = 1; i; i--) {
        while (j <= m && a[j].r - a[j].l + 1 >= i) ST.update(a[j].l, a[j].r, a[j].id), j++;
        ans[i] = solve(1, n);
    }
    for (int i = 1; i <= n; i++) write(ans[i]), putch('\n');
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
