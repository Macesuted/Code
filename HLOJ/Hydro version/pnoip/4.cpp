/**
 * @file 4.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-26
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

#define maxn 105
#define maxx 100005
#define mod 998244353

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

vector<long long> f[maxn][maxn];
long long fac[maxx], ifac[maxx];

long long binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n = read<int>(), X = read<int>();
    if (n == 1) return write(X), putch('\n');
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++) f[i][j].resize(i * j + 1);
    f[2][0][0] = f[2][1][2] = 2;
    for (int i = 2; i < n; i++)
        for (int j = 0; j < i; j++)
            for (int k = 0; k < (int)f[i][j].size(); k++)
                if (f[i][j][k]) {
                    f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k] * (i + 1 - j)) % mod;
                    f[i + 1][j + 1][k + i + 1] =
                        (f[i + 1][j + 1][k + i + 1] + f[i][j][k] * (2 * (i - 1 - j) + 2)) % mod;
                    if (j < i - 1)
                        f[i + 1][j + 2][k + 2 * (i + 1)] =
                            (f[i + 1][j + 2][k + 2 * (i + 1)] + f[i][j][k] * (i - 1 - j)) % mod;
                }
    long long ans = 0;
    for (int i = 0; i < (int)f[n][n - 1].size(); i++)
        if (i + 1 < X) ans = (ans + f[n][n - 1][i] * binom(X - i - 1 + n, n)) % mod;
    return write(ans), putch('\n');
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxx; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxx - 1] = Pow(fac[maxx - 1], mod - 2);
    for (int i = maxx - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
