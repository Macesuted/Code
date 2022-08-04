/**
 * @file support.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-05
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
 *
 */

#include <bits/stdc++.h>

namespace io {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
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
std::string getstr(const std::string& suf = "") {
    std::string s = suf;
    char c = getch();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r') c = getch();
    Il--;
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && *Il != ' ' && *Il != '\t' && *Il != '\n' && *Il != '\v' && *Il != '\f' && *Il != '\r' &&
               *Il != EOF)
            Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(std::string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::buftop;
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

bool mem1;

#define maxn 1000005

long long fac[maxn], ifac[maxn], sum[maxn], a[maxn], mod;

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
long long binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n = read<int>();
    mod = read<long long>();
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Pow(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    for (int i = 0; i <= n; i++) sum[i + 1] = (sum[i] + binom(n, i)) % mod;
    for (int d = 1; d <= n; d++) {
        int L = (n - d + 1) / 2, R = (n + d) / 2;
        for (int i = 1, id = -1; R - (d + 1) * i >= 0; i++, id = -id)
            a[d] = (a[d] + id * (sum[R - (d + 1) * i + 1] + mod - sum[std::max(0, L - (d + 1) * i)])) % mod;
        a[d] = (a[d] + a[d] + sum[R + 1] + mod - sum[L]) % mod;
        a[d] = a[d] * a[d] % mod;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + (a[i] + mod - a[i - 1]) * i) % mod;
    write(ans * Pow(Pow(2, n + n), mod - 2) % mod), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("support.in", "r", stdin), freopen("support.out", "w", stdout);
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
