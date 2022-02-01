/**
 * @file 1626F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-01
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My tutorial: https://macesuted.moe/article/cf1626f
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

#define maxk 18
#define maxn 10000005
#define maxL 720725
#define mod 998244353

int a[maxn];
long long f[maxk][maxL];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n = read<int>(), a0 = read<int>(), x = read<int>(), y = read<int>(), k = read<int>(), M = read<int>();
    a[1] = a0;
    for (int i = 2; i <= n; i++) a[i] = (1LL * a[i - 1] * x % M + y) % M;
    int L = 720720;
    long long ans = 0, coeff = k * Pow(n, k - 1) % mod;
    for (int i = 1; i <= n; i++) {
        int rest = a[i] % L;
        f[0][rest]++;
        ans = (ans + 1LL * (a[i] - rest) * coeff) % mod;
    }
    for (int i = 0; i < k; i++) {
        long long t = Pow(n, k - i - 1);
        for (int j = 0; j < L; j++)
            if (f[i][j]) {
                f[i + 1][j] = (f[i + 1][j] + 1LL * f[i][j] * (n - 1) % mod) % mod;
                f[i + 1][j - j % (i + 1)] = (f[i + 1][j - j % (i + 1)] + f[i][j]) % mod;
                ans = (ans + 1LL * j * f[i][j] % mod * t) % mod;
            }
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
