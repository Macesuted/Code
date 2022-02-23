/**
 * @file 1608F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

#define maxn 2005
#define maxk 105
#define mod 998244353

long long f[2][maxn][maxn], g[maxn][maxn], fac[maxn], ifac[maxn];
int b[maxn];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n = read<int>(), K = read<int>();
    for (int i = 1; i <= n; i++) b[i] = read<int>();
    f[0][0][0] = g[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        bool thi = i & 1, tha = !thi;
        for (int j = 0; j <= i - 1; j++)
            for (int k = max(0, b[i - 1] - K); k <= min({i - 1, b[i - 1] + K, j}); k++) {
                g[j][k] = f[tha][j][k] * fac[j - k] % mod;
                if (k) g[j][k] = (g[j][k] + g[j][k - 1]) % mod;
            }
        for (int j = 1; j <= i; j++)
            for (int k = max(0, b[i] - K); k <= min({i, b[i] + K, j}); k++) {
                f[thi][j][k] = (f[tha][j][k] * j + f[tha][j - 1][k]) % mod;
                if (k) f[thi][j][k] = (f[thi][j][k] + g[j - 1][min(k - 1, b[i - 1] + K)] * ifac[j - k]) % mod;
            }
        if (i == 1)
            f[0][0][0] = g[0][0] = 0;
        else
            for (int j = 0; j <= i - 1; j++)
                for (int k = max(0, b[i - 1] - K); k <= min({i - 1, b[i - 1] + K, j}); k++) f[tha][j][k] = g[j][k] = 0;
    }
    long long ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = max(0, b[n] - K); j <= min({n, b[n] + K, i}); j++)
            ans = (ans + f[n & 1][i][j] * fac[n - j] % mod * ifac[n - i]) % mod;
    return write(ans), putch('\n');
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Pow(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
