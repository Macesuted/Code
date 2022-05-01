/**
 * @file 2495.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-17
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

#define maxn 100005

class SegmentTree {
   private:
    struct Node {
        int maxT, minV;  // minV 为左半部分答案
    };

    Node tree[maxn << 3];
    int n;

    void pushUp(int p, int l, int r) {
        int mid = (l + r) >> 1;
        return tree[p].maxT = max(tree[p << 1].maxT, tree[p << 1 | 1].maxT),
               tree[p].minV = getAns(p << 1, l, mid, tree[p << 1 | 1].maxT), void();
    }
    void build(int p, int l, int r, int T[]) {
        if (l == r) return tree[p].minV = n / 2 - 1 + l + (tree[p].maxT = T[l] - l), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, T), build(p << 1 | 1, mid + 1, r, T);
        return pushUp(p, l, r);
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].minV = n / 2 - 1 + l + (tree[p].maxT = v - l), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p, l, r);
    }
    int getAns(int p, int l, int r, int lim) {
        if (l == r) return n / 2 - 1 + l + max(lim, tree[p].maxT);
        int mid = (l + r) >> 1;
        if (tree[p << 1 | 1].maxT <= lim) return min(getAns(p << 1, l, mid, lim), n / 2 + mid + lim);
        return min(tree[p].minV, getAns(p << 1 | 1, mid + 1, r, lim));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int T[]) { return build(1, 1, n, T); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(void) { return tree[1].minV; }
} ST;

int T[maxn << 1];

void solve(void) {
    int n = read<int>(), m = read<int>(), p = read<int>();
    for (int i = 1; i <= n; i++) T[i] = T[i + n] = read<int>();
    ST.resize(2 * n), ST.build(T), write(ST.query()), putch('\n');
    for (int i = 1, lastans = ST.query(); i <= m; i++) {
        int x = read<int>(), y = read<int>();
        if (p) x ^= lastans, y ^= lastans;
        ST.update(x, y), ST.update(x + n, y), write(lastans = ST.query()), putch('\n');
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
