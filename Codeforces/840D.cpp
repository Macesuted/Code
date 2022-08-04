/**
 * @file 840D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-19
 *
 * @copyright Copyright (c) 2021
 *
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

bool mem1;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int cnt;
        Node(void) { l = r = NULL, cnt = 0; }
    };

    vector<Node*> roots;
    int n;

    void build(Node*& root, int l, int r) {
        root = new Node();
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(root->l, l, mid), build(root->r, mid + 1, r);
        return;
    }
    void insert(Node*& root, Node* old, int l, int r, int qp) {
        root = new Node(*old);
        if (l == r) return root->cnt++, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(root->l, old->l, l, mid, qp) : insert(root->r, old->r, mid + 1, r, qp);
        root->cnt = root->l->cnt + root->r->cnt;
        return;
    }
    int getAns(Node* verL, Node* verR, int l, int r, int limit) {
        if (verR->cnt - verL->cnt <= limit) return -1;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int ret = getAns(verL->l, verR->l, l, mid, limit);
        if (ret != -1) return ret;
        return getAns(verL->r, verR->r, mid + 1, r, limit);
    }

   public:
    SegmentTree(void) { roots.push_back(NULL); }
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(void) { return build(roots[0], 1, n); }
    inline void insert(int p) { return roots.push_back(NULL), insert(roots.back(), roots[roots.size() - 2], 1, n, p); }
    inline int getAns(int verL, int verR, int limit) { return getAns(roots[verL], roots[verR], 1, n, limit); }
};

SegmentTree SGT;

void solve(void) {
    int n = read<int>(), q = read<int>();
    SGT.resize(n), SGT.build();
    for (int i = 1; i <= n; i++) SGT.insert(read<int>());
    while (q--) {
        int l = read<int>(), r = read<int>(), k = read<int>();
        write(SGT.getAns(l - 1, r, (r - l + 1) / k)), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << t2 - t1 << "ms" << endl;
    return 0;
}