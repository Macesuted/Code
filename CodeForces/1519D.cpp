/**
 * @author Macesuted (macesuted@qq.com)
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
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 5005

long long a[maxn], b[maxn];

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1; i <= n; i++) b[i] = read<int>();
    long long answer = 0, beg = 0;
    for (register int i = 1; i <= n; i++) beg += a[i] * b[i];
    answer = beg;
    for (register int i = 1; i <= n; i++) {
        long long tat = beg;
        for (register int r = 1; 1 <= i - r && i + r <= n; r++) {
            tat -= a[i - r] * b[i - r] + a[i + r] * b[i + r];
            tat += a[i - r] * b[i + r] + a[i + r] * b[i - r];
            answer = max(answer, tat);
        }
    }
    for (register int i = 1; i < n; i++) {
        long long tat = beg;
        for (register int r = 1; 1 <= i + 1 - r && i + r <= n; r++) {
            tat -= a[i + 1 - r] * b[i + 1 - r] + a[i + r] * b[i + r];
            tat += a[i + 1 - r] * b[i + r] + a[i + r] * b[i + 1 - r];
            answer = max(answer, tat);
        }
    }
    write(answer), putch('\n');
    return 0;
}