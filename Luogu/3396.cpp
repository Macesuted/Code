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
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t')) s.push_back(c), c = getch();
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

#define maxn 150005
#define maxSqrtn 505

int ans[maxSqrtn][maxSqrtn], a[maxn];

int main() {
    int n = read<int>(), m = read<int>(), sqrtn = sqrt(n);
    for (register int i = 1; i <= n; i++) {
        a[i] = read<int>();
        for (register int j = 1; j <= sqrtn; j++) ans[j][i % j] += a[i];
    }
    while (m--) {
        char opt = getch();
        while (opt != 'A' && opt != 'C') opt = getch();
        int x = read<int>(), y = read<int>();
        if (opt == 'A') {
            if (x <= sqrtn)
                write(ans[x][y]);
            else {
                int answer = 0;
                for (register int i = y; i <= n; i += x) answer += a[i];
                write(answer);
            }
            putch('\n');
        } else {
            for (register int i = 1; i <= sqrtn; i++) ans[i][x % i] += y - a[x];
            a[x] = y;
        }
    }
    return 0;
}