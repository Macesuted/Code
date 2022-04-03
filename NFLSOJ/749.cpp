/**
 * @file 749.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-01
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
    __int128 fx = x;
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

#define maxn 55
#define maxm 10
#define mod 258280327

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int64_t f[maxn][maxm], g[maxn][maxn][maxm], h[maxn][maxn][maxm][512], C[maxn][maxn], pow2[maxn * maxn];

int64_t H(int s, int t, int k, int v) {
    if (s > t) swap(s, t);
    if (v >= (1 << k)) return 0;
    if (!s || !t || !v) return pow2[k * (s + t)];
    if (~h[s][t][k][v]) return h[s][t][k][v];
    if (v >> (k - 1) & 1) return h[s][t][k][v] = 2 * H(s, t, k - 1, v ^ (1 << (k - 1))) % mod;
    h[s][t][k][v] = 2 * H(s, t, k - 1, 0) % mod;
    for (int i = 0; i <= s; i++)
        for (int j = 0; j <= t; j++)
            if (!(i == 0 && j == t) && !(i == s && j == 0))
                h[s][t][k][v] =
                    (h[s][t][k][v] + C[s][i] * C[t][j] % mod * H(i, j, k - 1, v) % mod * H(s - i, t - j, k - 1, v)) % mod;
    return h[s][t][k][v];
}
int64_t G(int s, int t, int k) {
    if (s > t) swap(s, t);
    if (k == 0) return 0;
    if (~g[s][t][k]) return g[s][t][k];
    g[s][t][k] = 0;
    for (int i = 1; i < (1 << k); i++) g[s][t][k] = (g[s][t][k] + H(s, t, k, i)) % mod;
    return g[s][t][k];
}
int64_t F(int n, int m) {
    if (!n || !m) return 0;
    if (~f[n][m]) return f[n][m];
    f[n][m] = 2 * F(n, m - 1) % mod;
    for (int i = 1; i < n; i++)
        f[n][m] = (f[n][m] + (F(i, m - 1) * pow2[(n - i) * (m - 1)] + F(n - i, m - 1) * pow2[i * (m - 1)] + G(i, n - i, m - 1) +
                              pow2[(n + 1) * (m - 1)]) %
                                 mod * C[n][i]) %
                  mod;
    return f[n][m];
}

void solve(void) {
    int n = read(), m = read();
    memset(f, 0xff, sizeof(f)), memset(g, 0xff, sizeof(g)), memset(h, 0xff, sizeof(h));
    return write(F(n, m) * Pow(pow2[n * m], mod - 2) % mod), putch('\n');
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("young.in", "r", stdin), freopen("young.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pow2[0] = 1;
    for (int i = 1; i < maxn * maxn; i++) pow2[i] = pow2[i - 1] * 2 % mod;
    for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
