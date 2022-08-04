/**
 * @file 7086.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-08
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

bool mem1;

long double A, B, C;

long double calc(long long tim) { return A * tim * tim + B * tim + C; }

void write(long long val, bool sure = true) {
    if (!sure)
        for (long long i = max(0LL, val + 1); i <= min((long long)1e18, val + 100); i++)
            if (calc(i) > 0) return io::write(i), putch('\n');
    if (val > 1e18 || !sure) return putstr("none\n");
    return io::write(val), putch('\n');
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    A = 0, B = 0, C = 0;
    for (int i = 1; i <= n; i++) {
        long double h = read<int>(), dh = read<int>(), d = read<int>(), dd = read<int>();
        A += dh * dd, B += d * dh + h * dd, C += h * d;
    }
    for (int i = 1; i <= m; i++) {
        long double h = read<int>(), dh = read<int>(), d = read<int>(), dd = read<int>();
        A -= dh * dd, B -= d * dh + h * dd, C -= h * d;
    }
    if (C > 0) return write(0);
    if (A == 0) {
        if (B <= 0) return putstr("none\n");
        return write((-C) / B, false);
    }
    long double delta = B * B - 4 * A * C;
    write((-B + sqrt(delta)) / (2 * A), false);
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
