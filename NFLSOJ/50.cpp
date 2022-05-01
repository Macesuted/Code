/**
 * @file 50.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-31
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

#define maxn 100005
#define mod 1000000007

typedef tuple<int, int, int> tiii;

int fa[maxn], siz[maxn];
tiii f[2][maxn];
int64_t fac[maxn], ifac[maxn], inv[maxn], sum[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }
int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

tiii operator+(const tiii& a, const int& v) { return {get<0>(a), get<1>(a), (get<2>(a) + v) % mod}; }
tiii operator-(const tiii& a, const int& v) { return a + Mod(mod - v); }
tiii operator*(const tiii& a, const int& v) {
    return {1LL * get<0>(a) * v % mod, 1LL * get<1>(a) * v % mod, 1LL * get<2>(a) * v % mod};
}
tiii operator+(const tiii& a, const tiii& b) {
    return {Mod(get<0>(a) + get<0>(b)), Mod(get<1>(a) + get<1>(b)), Mod(get<2>(a) + get<2>(b))};
}
tiii operator-(const tiii& a, const tiii& b) {
    return a + tiii{Mod(mod - get<0>(b)), Mod(mod - get<1>(b)), Mod(mod - get<2>(b))};
}

void solve(void) {
    int n = read();
    if (n == 2) return putstr("500000004\n");
    string s = getstr();
    for (int i = 2; i <= n; i++) fa[i] = read();
    f[0][1] = {1, 0, 0}, f[1][1] = {0, 1, 0};
    for (int i = 1; i < n - 1; i++)
        f[1][i + 1] = (f[1][i] * n - (i > 1) - f[1][i - 1] * (i - 1) - f[0][i - 1]) * inv[n - i],
                 f[0][i + 1] = (f[0][i] * n - 1 - f[0][i - 1] * i - f[1][i + 1]) * inv[n - i - 1];
    tiii p1 = f[0][n - 1] * n - f[0][n - 2] * (n - 1), p2 = f[1][n - 1] * n - f[1][n - 2] * (n - 2) - f[0][n - 2] - 1;
    int64_t f10 = (1LL * get<1>(p1) * get<2>(p2) % mod + mod - 1LL * get<1>(p2) * get<2>(p1) % mod) *
                  Pow(1LL * get<0>(p1) * get<1>(p2) % mod + mod - 1LL * get<0>(p2) * get<1>(p1) % mod, mod - 2) % mod,
            f11 = (1LL * get<0>(p1) * get<2>(p2) % mod + mod - 1LL * get<0>(p2) * get<2>(p1) % mod) *
                  Pow(1LL * get<1>(p1) * get<0>(p2) % mod + mod - 1LL * get<1>(p2) * get<0>(p1) % mod, mod - 2) % mod;
    int cnt = 0;
    for (auto i : s) cnt += (i == '1');
    int64_t F[2] = {(get<0>(f[0][cnt]) * f10 + get<1>(f[0][cnt]) * f11 + get<2>(f[0][cnt])) % mod,
                    (get<0>(f[1][cnt]) * f10 + get<1>(f[1][cnt]) * f11 + get<2>(f[1][cnt])) % mod};
    for (int i = n; i; i--) siz[fa[i]] += ++siz[i], sum[fa[i]] += sum[i] + siz[i];
    for (int i = 2; i <= n; i++) sum[i] = sum[fa[i]] + n - 2 * siz[i];
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + sum[i] * (F[s[i - 1] - '0'] + inv[n])) % mod;
    write(ans * inv[n] % mod), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = inv[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Pow(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 1; i < maxn; i++) inv[i] = fac[i - 1] * ifac[i] % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
