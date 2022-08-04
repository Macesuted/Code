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

#define maxn 12
#define mod 2004

int m[maxn], n;
long long fac = 1, sum;

long long C(int n, int m) {
    long long Mod = mod * fac, ans = 1;
    for (register int i = m - n + 1; i <= m; i++) ans = ans * i % Mod;
    return ans / fac % mod;
}

void dfs(int p, int val, int times, int lim) {
    if (times > lim) return;
    if (p == n + 1) return sum = (sum + 1LL * val * C(n, n + lim - times)) % mod, void();
    dfs(p + 1, val, times, lim), dfs(p + 1, -val, times + m[p] + 1, lim);
    return;
}

long long solve(int lim) {
    sum = 0;
    dfs(1, 1, 0, lim);
    return sum;
}

int main() {
    n = read<int>();
    int l = read<int>(), r = read<int>();
    for (register int i = 1; i <= n; i++) m[i] = read<int>(), fac *= i;
    write(((solve(r) - solve(l - 1)) % mod + mod) % mod), putch('\n');
    return 0;
}