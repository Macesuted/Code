/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
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

#define maxn 17
#define mod 1000000007

long long f[maxn][1 << maxn], fac[1 << maxn], inv[1 << maxn];
int a[maxn], cnt[1 << maxn];

long long power(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}
inline long long C(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    fac[0] = inv[0] = 1;
    for (register int i = 1; i < (1 << maxn); i++) fac[i] = fac[i - 1] * i % mod;
    inv[(1 << maxn) - 1] = power(fac[(1 << maxn) - 1], mod - 2);
    for (register int i = (1 << maxn) - 2; i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    int n = read<int>(), m = read<int>(), tn = 1 << n;
    for (register int i = 1; i <= m; i++) a[i] = read<int>();
    sort(a + 1, a + m + 1, greater<int>());
    for (register int i = 1; i < tn; i++) cnt[i] = cnt[i >> 1] + (i & 1);
    f[0][0] = 1;
    for (register int i = 1; i <= m; i++)
        for (register int j = 0; j < tn; j++) {
            f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
            for (register int k = 0; k < n; k++)
                if (!(j >> k & 1))
                    f[i][j | (1 << k)] = (f[i][j | (1 << k)] + f[i - 1][j] * C(tn - a[i] - j, (1 << k) - 1) % mod * fac[1 << k] % mod) % mod;
        }
    long long answer = 0;
    for (register int S = 0; S < tn; S++)
        answer = (answer + ((cnt[S] & 1) ? -1 : 1) * f[m][S] % mod * fac[tn - S - 1] % mod + mod) % mod;
    write(answer * tn % mod), putch('\n');
    return 0;
}