/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
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

#define maxn 500005
#define mod 1000000000
#define int long long

long long a[maxn], f[3][maxn], g[3][maxn];

long long solve(int l, int r) {
    if (l == r) return a[l] * a[l] % mod;
    int mid = (l + r) >> 1;
    f[0][mid] = f[1][mid] = f[2][mid] = g[0][mid] = g[1][mid] = g[2][mid] = 0;
    long long minVal = a[mid + 1], maxVal = a[mid + 1];
    for (register int i = mid + 1; i <= r; i++) {
        minVal = min(minVal, a[i]), maxVal = max(maxVal, a[i]);
        f[0][i] = (f[0][i - 1] + minVal * (i - mid)) % mod, g[0][i] = (g[0][i - 1] + minVal) % mod;
        f[1][i] = (f[1][i - 1] + maxVal * (i - mid)) % mod, g[1][i] = (g[1][i - 1] + maxVal) % mod;
        f[2][i] = (f[2][i - 1] + minVal * maxVal % mod * (i - mid)) % mod,
        g[2][i] = (g[2][i - 1] + minVal * maxVal) % mod;
    }
    long long answer = 0;
    minVal = a[mid], maxVal = a[mid];
    for (register int i = mid, p1 = mid, p2 = mid; i >= l; i--) {
        minVal = min(minVal, a[i]), maxVal = max(maxVal, a[i]);
        while (p1 < r && a[p1 + 1] > minVal) p1++;
        while (p2 < r && a[p2 + 1] < maxVal) p2++;
        register int pl = min(p1, p2), pr = max(p1, p2);
        if (pl > mid) answer = (answer + minVal * maxVal % mod * ((mid + pl - i * 2 + 3) * (pl - mid) / 2 % mod)) % mod;
        if (p1 > pl)
            answer =
                (answer + minVal * ((f[1][p1] - f[1][pl] + mod) + (mid - i + 1) * (g[1][p1] - g[1][pl] + mod) % mod)) %
                mod;
        if (p2 > pl)
            answer =
                (answer + maxVal * ((f[0][p2] - f[0][pl] + mod) + (mid - i + 1) * (g[0][p2] - g[0][pl] + mod) % mod)) %
                mod;
        answer = (answer + (f[2][r] - f[2][pr] + mod) % mod + (mid - i + 1) * (g[2][r] - g[2][pr] + mod) % mod) % mod;
    }
    return (answer + solve(l, mid) + solve(mid + 1, r)) % mod;
}

signed main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    write(solve(1, n)), putch('\n');
    return 0;
}