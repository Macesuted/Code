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

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

class SegmentTree1 {
   private:
    int minVal[maxn << 2], maxVal[maxn << 2];
    int n;

    void build(int p, int l, int r, int a[]) {
        if (l == r) return minVal[p] = maxVal[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        minVal[p] = min(minVal[p << 1], minVal[p << 1 | 1]), maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }
    int getMin(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return minVal[p];
        int mid = (l + r) >> 1, ans = 0x3f3f3f3f;
        if (ql <= mid) ans = min(ans, getMin(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = min(ans, getMin(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
    int getMax(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return maxVal[p];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = max(ans, getMax(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = max(ans, getMax(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
    void update(int p, int l, int r, int qp, int val) {
        if (l == r) return minVal[p] = maxVal[p] = val, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
        minVal[p] = min(minVal[p << 1], minVal[p << 1 | 1]), maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(int a[]) { return build(1, 1, n, a); }
    inline int getMin(int l, int r) { return getMin(1, 1, n, l, r); }
    inline int getMax(int l, int r) { return getMax(1, 1, n, l, r); }
    inline void update(int p, int val) { return update(1, 1, n, p, val); }
};
class SegmentTree2 {
   private:
    int tree[maxn << 2];
    int n;

    void build(int p, int l, int r, int a[]) {
        if (l == r) return tree[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        tree[p] = gcd(tree[p << 1], tree[p << 1 | 1]);
        return;
    }
    int getGcd(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = gcd(ans, getGcd(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = gcd(ans, getGcd(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
    void update(int p, int l, int r, int qp, int val) {
        if (l == r) return tree[p] = val, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
        tree[p] = gcd(tree[p << 1], tree[p << 1 | 1]);
        return;
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(int a[]) { return build(1, 1, n, a); }
    inline int getGcd(int l, int r) { return getGcd(1, 1, n, l, r); }
    inline void update(int p, int val) { return update(1, 1, n, p, val); }
};
class SegmentTree3 {
   private:
    int maxVal[maxn << 2];
    int n;

    void build(int p, int l, int r, int a[]) {
        if (l == r) return maxVal[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }
    int getMax(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return maxVal[p];
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = max(ans, getMax(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = max(ans, getMax(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }
    void update(int p, int l, int r, int qp, int val) {
        if (l == r) return maxVal[p] = val, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
        maxVal[p] = max(maxVal[p << 1], maxVal[p << 1 | 1]);
        return;
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(int a[]) { return build(1, 1, n, a); }
    inline int getMax(int l, int r) { return getMax(1, 1, n, l, r); }
    inline void update(int p, int val) { return update(1, 1, n, p, val); }
};

SegmentTree1 tree1;
SegmentTree2 tree2;
SegmentTree3 tree3;

int a[maxn], b[maxn], pos[maxn];

map<int, set<int> > record;

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) record[a[i] = read<int>()].insert(i);
    for (register int i = 1; i <= n; i++) b[i] = abs(a[i] - a[i - 1]);
    for (map<int, set<int> >::iterator i = record.begin(); i != record.end(); i++) {
        int pre = 0;
        for (set<int>::iterator j = i->second.begin(); j != i->second.end(); j++) pos[*j] = pre, pre = *j;
    }
    tree1.resize(n), tree1.build(a);
    tree2.resize(n), tree2.build(b);
    tree3.resize(n), tree3.build(pos);
    while (m--) {
        if (read<int>() == 1) {
            int p = read<int>(), v = read<int>();
            tree1.update(p, v);
            tree2.update(p, b[p] = abs(v - a[p - 1])), tree2.update(p + 1, b[p + 1] = abs(a[p + 1] - v));
            set<int>::iterator aft = ++record[a[p]].find(p);
            if (aft != record[a[p]].end()) tree3.update(*aft, tree3.getMax(p, p));
            record[a[p]].erase(p);
            a[p] = v;
            int tail = record[a[p]].empty() ? 0 : *record[a[p]].rbegin();
            record[a[p]].insert(p);
            aft = ++record[a[p]].find(p);
            if (aft != record[a[p]].end()) {
                tree3.update(p, tree3.getMax(*aft, *aft));
                tree3.update(*aft, p);
            } else
                tree3.update(p, tail);
        } else {
            int l = read<int>(), r = read<int>(), k = 1;
            bool check = true;
            int down = tree1.getMin(l, r), up = tree1.getMax(l, r);
            if ((up - down) % k != 0 || (up - down) / k != r - l) check = false;
            if (l < r && tree2.getGcd(l + 1, r) != k) check = false;
            if (tree3.getMax(l, r) >= l) check = false;
            putstr(check ? "damushen" : "yuanxing"), putch('\n');
        }
        // for (register int i = 1; i <= n; i++) printf("%d ", tree1.getMax(i, i));
        // puts("");
        // for (register int i = 1; i <= n; i++) printf("%d ", tree2.getGcd(i, i));
        // puts("");
        // for (register int i = 1; i <= n; i++) printf("%d ", tree3.getMax(i, i));
        // puts("");
    }
    return 0;
}