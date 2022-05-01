/**
 * @file 108.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
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
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

#define maxn 100005

typedef complex<double> Complex;

const double PI = acos(-1);

int rev[maxn << 2];

void DFT(Complex a[], int n, int mode) {
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int len = 1; len < n; len <<= 1) {
        Complex base(cos(PI / len), mode * sin(PI / len));
        for (int i = 0; i < n; i += len << 1) {
            Complex w(1, 0);
            for (int j = i; j < i + len; j++, w *= base)
                tie(a[j], a[j + len]) = make_pair(a[j] + w * a[j + len], a[j] - w * a[j + len]);
        }
    }
    return;
}

Complex a[maxn << 2], b[maxn << 2];

void solve(void) {
    int n = read<int>(), m = read<int>(), len = 1, lglen = 0;
    while (len < n + m + 1) len <<= 1, lglen++;
    for (int i = 0; i <= n; i++) a[i].real(read<int>());
    for (int i = 0; i <= m; i++) b[i].real(read<int>());
    for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lglen - 1));
    DFT(a, len, +1), DFT(b, len, +1);
    for (int i = 0; i < len; i++) a[i] *= b[i];
    DFT(a, len, -1);
    for (int i = 0; i <= n + m; i++) write((int)(a[i].real() / len + 0.5)), putch(" \n"[i == n + m]);
    return;
}

bool mem2;

int main() {
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
