/**
 * @file 2996.cpp
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

#define maxn 100005

class SegmentTree {
   private:
    long long tree[maxn << 2], lazy[maxn << 2];
    int n;

    void upd(int p, long long v) { return tree[p] += v, lazy[p] += v, void(); }
    void pushDown(int p) { return upd(p << 1, lazy[p]), upd(p << 1 | 1, lazy[p]), lazy[p] = 0, void(); }
    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int qp, long long v) {
        if (l == r) return tree[p] = max(tree[p], v), void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void add(int p, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) return upd(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void clear(void) { return memset(tree, 0, sizeof(tree)), memset(lazy, 0, sizeof(lazy)), void(); }
    void resize(int _n) { return n = _n, void(); }
    void update(int p, long long v) { return update(1, 1, n, p, v); }
    void add(int l, int r, long long v) { return add(1, 1, n, l, r, v); }
    long long query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int H[maxn], P[maxn], C[maxn], t[maxn];
long long f[maxn], g[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) H[i] = t[i] = read<int>(), P[i] = read<int>(), C[i] = read<int>();
    sort(t + 1, t + n + 1);
    int nt = unique(t + 1, t + n + 1) - t - 1;
    for (int i = 1; i <= n; i++) H[i] = lower_bound(t + 1, t + nt + 1, H[i]) - t;
    ST.resize(nt);
    for (int i = 1; i <= n; i++)
        ST.update(H[i], f[i] = ST.query(1, H[i]) + P[i]), (H[i] > 1) && (ST.add(1, H[i] - 1, -C[i]), 0);
    ST.clear();
    for (int i = n; i; i--)
        ST.update(H[i], g[i] = ST.query(1, H[i]) + P[i]), (H[i] > 1) && (ST.add(1, H[i] - 1, -C[i]), 0);
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i] + g[i] - P[i]);
    write(ans), putch('\n');
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
