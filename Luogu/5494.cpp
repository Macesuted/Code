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

#define maxn 200005

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        long long cnt;
        Node(void) { l = r = NULL, cnt = 0; }
    };

    Node* root;
    int n;

    inline long long getCnt(Node* p) { return p == NULL ? 0 : p->cnt; }
    inline void update(Node* p) { return p->cnt = getCnt(p->l) + getCnt(p->r), void(); }
    void destroy(Node*& p) {
        if (p == NULL) return;
        if (p->l != NULL) destroy(p->l);
        if (p->r != NULL) destroy(p->r);
        delete p;
        p = NULL;
        return;
    }
    void split(Node*& ans, Node*& p, int l, int r, int ql, int qr) {
        if (p == NULL) return;
        if (ans == NULL) ans = new Node();
        if (ql <= l && r <= qr) return ans = p, p = NULL, void();
        int mid = (l + r) >> 1;
        if (ql <= mid) split(ans->l, p->l, l, mid, ql, qr);
        if (qr > mid) split(ans->r, p->r, mid + 1, r, ql, qr);
        return update(ans), update(p);
    }
    void merge(Node*& p, Node*& oth, int l, int r) {
        if (p == NULL) return p = oth, oth = NULL, void();
        if (oth == NULL) return;
        if (l == r) return p->cnt += oth->cnt, void();
        int mid = (l + r) >> 1;
        merge(p->l, oth->l, l, mid), merge(p->r, oth->r, mid + 1, r);
        return update(p);
    }
    void insert(Node*& p, int l, int r, int qp, int val) {
        if (p == NULL) p = new Node();
        if (l == r) return p->cnt += val, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp, val) : insert(p->r, mid + 1, r, qp, val);
        return update(p);
    }
    long long count(Node* p, int l, int r, int ql, int qr) {
        if (p == NULL) return 0;
        if (ql <= l && r <= qr) return p->cnt;
        int mid = (l + r) >> 1;
        long long answer = 0;
        if (ql <= mid) answer += count(p->l, l, mid, ql, qr);
        if (qr > mid) answer += count(p->r, mid + 1, r, ql, qr);
        return answer;
    }
    int findKth(Node* p, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (k > getCnt(p->l)) return findKth(p->r, mid + 1, r, k - getCnt(p->l));
        return findKth(p->l, l, mid, k);
    }

   public:
    SegmentTree(void) { root = NULL, n = 2e5; }

    inline void clear(void) { return destroy(root); }
    inline SegmentTree split(int l, int r) {
        SegmentTree ans;
        split(ans.root, root, 1, n, l, r);
        return ans;
    }
    inline void merge(SegmentTree& oth) { return merge(root, oth.root, 1, n), oth.clear(); }
    inline void insert(int p, int val) { return insert(root, 1, n, p, val); }
    inline long long count(int l, int r) { return count(root, 1, n, l, r); }
    inline int findKth(int k) { return (root == NULL || root->cnt < k) ? -1 : findKth(root, 1, n, k); }
};

SegmentTree trees[maxn];
int cnt = 1;

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) trees[1].insert(i, read<int>());
    while (m--) {
        int opt = read<int>();
        if (opt == 0) {
            int p = read<int>(), x = read<int>(), y = read<int>();
            trees[++cnt] = trees[p].split(x, y);
        } else if (opt == 1) {
            int p = read<int>(), t = read<int>();
            trees[p].merge(trees[t]);
        } else if (opt == 2) {
            int p = read<int>(), x = read<int>(), q = read<int>();
            trees[p].insert(q, x);
        } else if (opt == 3) {
            int p = read<int>(), x = read<int>(), y = read<int>();
            write(trees[p].count(x, y)), putch('\n');
        } else {
            int p = read<int>(), k = read<int>();
            write(trees[p].findKth(k)), putch('\n');
        }
    }
    return 0;
}