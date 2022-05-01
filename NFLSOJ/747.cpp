/**
 * @file 747.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-12
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

#define maxn 1005
#define maxm 105

typedef long double float128_t;

float128_t r[maxn], p[maxn], s[maxn], f[maxn][maxn * 2], g[maxm * 2];

void solve(int n, int m1, int m2) {
    for (int i = 1; i <= n; i++) r[i] = read() / 100., p[i] = read() / 100., s[i] = read() / 100.;
    auto check = [&](float128_t t) {
        for (int i = -n + maxn; i <= -1 + maxn; i++) f[n][i] = -t;
        f[n][0 + maxn] = 0;
        for (int i = +1 + maxn; i <= +n + maxn; i++) f[n][i] = 1 - t;
        for (int i = n; i; i--)
            for (int j = -(i - 1) + maxn; j <= +(i - 1) + maxn; j++)
                f[i - 1][j] = max({f[i][j - 1] * p[i] + f[i][j] * r[i] + f[i][j + 1] * s[i],
                                   f[i][j - 1] * s[i] + f[i][j] * p[i] + f[i][j + 1] * r[i],
                                   f[i][j - 1] * r[i] + f[i][j] * s[i] + f[i][j + 1] * p[i]});
        return f[0][0 + maxn] >= 0;
    };
    float128_t L = 0, R = 1;
    for (int x = 100; x; x--) {
        float128_t mid = (L + R) / 2;
        check(mid) ? L = mid : R = mid;
    }
    g[-m2 + maxm] = 0, g[-m2 + 1 + maxm] = 1;
    for (int i = -m2 + 2 + maxm; i <= +m1 + maxm; i++) g[i] = (g[i - 1] - g[i - 2] * (1 - L)) / L;
    writeDouble(g[0 + maxm] / g[m1 + maxm], 5), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("rps.in", "r", stdin), freopen("rps.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int n, m1, m2;
    while ((n = read()) && (m1 = read()) && (m2 = read())) solve(n, m1, m2);

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}