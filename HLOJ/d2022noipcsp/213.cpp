/**
 * @file 213.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
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
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::putch;
using IO::read;
using IO::write;

vector<int> a, b, v, pos;
vector<int64_t> f;
int64_t lim;

void insert(vector<int64_t>& f, int c, int v) {
    for (int i = (int)f.size() - 1; i >= c; i--) f[i] = max(f[i], f[i - c] + v);
    return;
}
int64_t getSum(vector<int64_t>& f) {
    int64_t ans = 0;
    for (auto i : f) ans += i;
    return ans;
}

void solve(int l, int r, int tl, int tr) {
    if (l > r) return;
    if (tl == tr) {
        for (int i = l; i <= r; i++) pos[i] = tl;
        return;
    }
    int tm = (tl + tr) >> 1, ql = l - 1, qr = min(r, tm) + 1;
    vector<int64_t> g = f;
    for (int i = max(qr, tl); i <= tm; i++) insert(g, b[i], v[i]);
    for (int i = tm + 1; i <= tr; i++) insert(g, a[i], v[i]);
    while (ql + 1 < qr) {
        int qm = (ql + qr) >> 1;
        vector<int64_t> h = g;
        for (int i = ql + 1; i < qm; i++) insert(h, a[i], v[i]);
        for (int i = qm; i < qr; i++) insert(h, b[i], v[i]);
        if (getSum(h) <= lim)
            while (ql < qm) ql++, insert(g, a[ql], v[ql]);
        else
            while (qr > qm) qr--, insert(g, b[qr], v[qr]);
    }
    g = f;
    for (int i = qr; i <= min(r, tl - 1); i++) insert(f, b[i], v[i]);
    for (int i = tm + 1; i <= tr; i++) insert(f, a[i], v[i]);
    solve(l, ql, tl, tm);
    f = g;
    for (int i = l; i <= ql; i++) insert(f, a[i], v[i]);
    for (int i = max(tl, r + 1); i <= tm; i++) insert(f, b[i], v[i]);
    solve(qr, r, tm + 1, tr);
    return;
}

void solve(void) {
    int n = read(), m = read();
    lim = read<int64_t>() * m;
    a.resize(n + 1), b.resize(n + 1), v.resize(n + 1), pos.resize(n + 1), f.resize(m + 1);
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    for (int i = 1; i <= n; i++) v[i] = read();
    solve(1, n, 1, n + 1);
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += n - pos[i] + 1;
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("store.in", "r", stdin), freopen("store.out", "w", stdout);
#endif
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