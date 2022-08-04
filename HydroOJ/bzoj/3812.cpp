/**
 * @file 3812.cpp
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

#define maxn 15
#define mod 1000000007

int pow2[maxn * maxn], c[maxn][1 << maxn], e[1 << maxn];
int64_t f[1 << maxn], g[1 << maxn];
bool graph[maxn][maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n = read(), m = read();
    for (int i = 1; i <= m; i++) {
        int x = read() - 1, y = read() - 1;
        graph[x][y] = true;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1 << n); j++)
            for (int k = 0; k < n; k++) c[i][j] += ((j >> k & 1) && graph[i][k]);
    auto E = [&](int S, int T) {
        int ans = 0;
        for (int i = 0; i < n; i++)
            if (S >> i & 1) ans += c[i][T];
        return ans;
    };
    for (int S = 0; S < (1 << n); S++) e[S] = E(S, S);
    for (int S = 1; S < (1 << n); S++) {
        if (__builtin_popcount(S) == 1) {
            f[S] = g[S] = 1;
            continue;
        }
        int u = S & -S, rest = S ^ u;
        g[S] = Mod(mod - f[u] * g[rest] % mod);
        for (int T = (rest - 1) & rest; T; T = (T - 1) & rest) g[S] = Mod(g[S] + mod - f[T | u] * g[rest ^ T] % mod);
        f[S] = pow2[e[S]];
        for (int T = S; T; T = (T - 1) & S)
            f[S] = Mod(f[S] + mod - g[T] * pow2[E(T, S ^ T)] % mod * pow2[e[S ^ T]] % mod);
        g[S] = Mod(g[S] + f[S]);
    }
    write(f[(1 << n) - 1]), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pow2[0] = 1;
    for (int i = 1; i < maxn * maxn; i++) pow2[i] = Mod(pow2[i - 1] * 2);

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
