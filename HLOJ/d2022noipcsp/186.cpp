/**
 * @file 186.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

namespace IO {
const int SIZE = 1 << 25;
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
using IO::getch;
using IO::putch;
using IO::read;
using IO::write;

bool mem1;

#define maxn 3005
#define mod 998244353

int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];
int64_t d[maxn];
mt19937 rnd(20080618);

void solve(void) {
    int n = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) b[i][j] = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) c[i][j] = read();
    // for (int t = 0; t < 15; t++) {
    //     int64_t p = rnd() % (mod - 1) + 1;
    //     for (int i = 1; i <= n; i++) {
    //         d[i] = 0;
    //         for (int j = 1; j <= n; j++) d[i] = (d[i] * p + b[i][j]) % mod;
    //     }
    //     for (int i = 1; i <= n; i++) {
    //         int64_t s = 0, t = 0;
    //         for (int j = 1; j <= n; j++) s = (s + a[i][j] * d[j]) % mod, t = (t * p + c[i][j]) % mod;
    //         if (s != t) return cout << "No" << endl, void();
    //     }
    // }
    cout << "Yes" << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("matrix.in", "r", stdin), freopen("matrix.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}