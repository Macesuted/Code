/**
 * @file 1599F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-29
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
using io::write;

bool mem1;

#define maxn 200005
#define mod 1000000007

int base[3];
int a[maxn], sum[3][maxn], g[55][maxn], C[55][55];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

bool check(int l, int r, int d) {
    int f = ((sum[0][r] + mod - sum[0][l - 1]) * 2LL % mod * Pow(r - l + 1, mod - 2) % mod - 1LL * (r - l) * d % mod +
             mod) *
            Pow(2, mod - 2) % mod;
    // cerr << "First: " << f << endl;
    for (int t = 0; t < 3; t++) {
        long long ans = 0, ft = 1, dt = Pow(d, base[t]), revD = Pow(d, mod - 2);
        for (int i = 0; i <= base[t]; i++, ft = ft * f % mod, dt = dt * revD % mod)
            ans = (ans + C[base[t]][i] * ft % mod * dt % mod * g[base[t] - i][r - l]) % mod;
        // cerr << ans << ' ' << (sum[t][r] + mod - sum[t][l - 1]) % mod << endl;
        if (ans != (sum[t][r] + mod - sum[t][l - 1]) % mod) return false;
    }
    return true;
}

void solve(void) {
    for (int i = 0; i < 55; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    int n = read<int>(), q = read<int>();
    mt19937 rnd(time(NULL));
    base[0] = 1;
    for (int t = 1; t < 3; t++) base[t] = rnd() % 50 + 1;
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        for (int t = 0; t < 3; t++) sum[t][i] = (Pow(a[i], base[t]) + sum[t][i - 1]) % mod;
    }
    for (int t = 0; t < 55; t++) {
        g[t][0] = Pow(0, t);
        for (int i = 1; i < maxn; i++) g[t][i] = (g[t][i - 1] + Pow(i, t)) % mod;
    }
    while (q--) {
        int l = read<int>(), r = read<int>(), d = read<int>();
        putstr(check(l, r, d) ? "Yes" : "No"), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}