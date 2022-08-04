/**
 * @file 1270H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 500005
#define maxV 1000005

class SegmentTree {
   private:
    struct Node {
        int minVal, cnt, lazy;
    };

    Node tree[maxV << 2];
    int n;

    void update(int p, int v) { return tree[p].minVal += v, tree[p].lazy += v, void(); }
    void pushDown(int p) {
        return update(p << 1, tree[p].lazy), update(p << 1 | 1, tree[p].lazy), tree[p].lazy = 0, void();
    }
    void pushUp(int p) {
        tree[p].minVal = min(tree[p << 1].minVal, tree[p << 1 | 1].minVal), tree[p].cnt = 0;
        if (tree[p].minVal == tree[p << 1].minVal) tree[p].cnt += tree[p << 1].cnt;
        if (tree[p].minVal == tree[p << 1 | 1].minVal) tree[p].cnt += tree[p << 1 | 1].cnt;
        return;
    }
    void insert(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].cnt += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v) : insert(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return update(p, v);
        if (l == r) return;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }

   public:
    SegmentTree(void) { n = 1000000; }
    void insert(int p, int v) { return insert(1, 1, n, p, v); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    int query(void) { return tree[1].cnt; }
} ST;

int a[maxn];

void solve(void) {
    int n = read<int>(), q = read<int>();
    for (int i = 1; i <= n; i++) ST.insert(a[i] = read<int>(), +1);
    a[0] = 1000001, a[n + 1] = 0;
    for (int i = 1; i <= n + 1; i++)
        if (a[i - 1] > a[i]) ST.update(a[i], a[i - 1] - 1, +1);
    while (q--) {
        int p = read<int>();
        if (a[p - 1] > a[p]) ST.update(a[p], a[p - 1] - 1, -1);
        if (a[p] > a[p + 1]) ST.update(a[p + 1], a[p] - 1, -1);
        ST.insert(a[p], -1), ST.insert(a[p] = read<int>(), +1);
        if (a[p - 1] > a[p]) ST.update(a[p], a[p - 1] - 1, +1);
        if (a[p] > a[p + 1]) ST.update(a[p + 1], a[p] - 1, +1);
        write(ST.query()), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
