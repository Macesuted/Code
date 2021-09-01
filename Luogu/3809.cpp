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

#define maxn 1000005

string a;

int sa[maxn], rk[maxn << 1], cnt[maxn], old[maxn], cache[maxn];

int main() {
    cin >> a;
    int n = a.size(), m = max(256, n);
    for (register int i = 1; i <= n; i++) cnt[rk[i] = a[i - 1]]++;
    for (register int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (register int i = n; i; i--) sa[cnt[rk[i]]--] = i;
    for (register int len = 1;; len <<= 1) {
        for (register int i = 1; i <= len; i++) old[i] = n - len + i;
        for (register int i = 1, p = len; i <= n; i++)
            if (sa[i] > len) old[++p] = sa[i] - len;
        for (register int i = 1; i <= m; i++) cnt[i] = 0;
        for (register int i = 1; i <= n; i++) cnt[cache[i] = rk[old[i]]]++;
        for (register int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (register int i = n; i; i--) sa[cnt[cache[i]]--] = old[i];
        for (register int i = 1; i <= n; i++) old[i] = rk[i];
        m = 0;
        for (register int i = 1; i <= n; i++) {
            if (old[sa[i]] != old[sa[i - 1]] || old[sa[i] + len] != old[sa[i - 1] + len]) m++;
            rk[sa[i]] = m;
        }
        if (n == m) break;
    }
    for (register int i = 1; i <= n; i++) write(sa[i]), putch(" \n"[i == n]);
    return 0;
}