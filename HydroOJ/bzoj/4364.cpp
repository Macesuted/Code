/**
 * @file 4364.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
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
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 2000005

class SegmentTree {
   private:
    struct Node {
        int vl, vr, v;
        Node(void) { vl = v = 0, vr = 1e5; }
    };

    Node tree[maxn << 2];
    int n;

    void upd(int p, int vl, int vr) {
        return tree[p].v = min(max(tree[p].v, vl), vr), tree[p].vl = min(max(tree[p].vl, vl), vr),
               tree[p].vr = min(max(tree[p].vr, vl), vr), void();
    }
    void pushDown(int p) {
        return upd(p << 1, tree[p].vl, tree[p].vr), upd(p << 1 | 1, tree[p].vl, tree[p].vr), tree[p].vl = 0, tree[p].vr = 1e5,
                                                                                             void();
    }
    void update(int p, int l, int r, int ql, int qr, int vl, int vr) {
        if (ql <= l && r <= qr) return upd(p, vl, vr);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, vl, vr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, vl, vr);
        return;
    }
    void print(int p, int l, int r) {
        if (l == r) return write(tree[p].v), putch('\n');
        pushDown(p);
        int mid = (l + r) >> 1;
        print(p << 1, l, mid), print(p << 1 | 1, mid + 1, r);
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int vl, int vr) { return update(1, 1, n, l, r, vl, vr); }
    void print(void) { return print(1, 1, n); }
} ST;

void solve(void) {
    int n = read(), k = read();
    ST.resize(n);
    while (k--) {
        int op = read(), l = read() + 1, r = read() + 1, h = read();
        ST.update(l, r, op == 1 ? h : 0, op == 2 ? h : 1e5);
    }
    ST.print();
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}