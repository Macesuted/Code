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

#define maxn 18

double f[1 << maxn];
int cnt[1 << maxn];
double a[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int maxS = 1 << n;
    for (register int i = 0; i < n; i++)
        for (register int j = 0; j < n; j++)
            cin >> a[i][j];
    for (register int i = 1; i < maxS; i++) cnt[i] = cnt[i >> 1] + (i & 1);
    f[maxS - 1] = 1;
    for (register int i = maxS - 2; i; i--)
        for (register int j = 0; j < n; j++)
            if (i >> j & 1)
                for (register int k = 0; k < n; k++)
                    if (!(i >> k & 1)) f[i] += f[i ^ (1 << k)] * a[j][k] / (cnt[i] * (cnt[i] + 1) / 2.0);
    for (register int i = 0; i < n; i++) printf("%.6lf%c", f[1 << i], " \n"[i == n - 1]);
    return 0;
}