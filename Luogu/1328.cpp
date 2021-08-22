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
string getstr(void) {
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

#define maxn 205

int f(int x, int y) {
    if (x == y) return 0;
    if (x > y) return 1 - f(y, x);
    if (x == 1 && y == 2) return 0;
    if (x == 1 && y == 3) return 1;
    if (x == 1 && y == 4) return 1;
    if (x == 1 && y == 5) return 0;
    if (x == 2 && y == 3) return 0;
    if (x == 2 && y == 4) return 1;
    if (x == 2 && y == 5) return 0;
    if (x == 3 && y == 4) return 0;
    if (x == 3 && y == 5) return 1;
    if (x == 4 && y == 5) return 1;
    return 0;
}

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int a[maxn], b[maxn];

int main() {
    // freopen("rps.in", "r", stdin), freopen("rps.out", "w", stdout);
    int n = read<int>(), na = read<int>(), nb = read<int>();
    for (register int i = 0; i < na; i++) a[i] = read<int>() + 1;
    for (register int i = 0; i < nb; i++) b[i] = read<int>() + 1;
    int sa = 0, sb = 0, pa = 0, pb = 0;
    while (n--) {
        sa += f(a[pa], b[pb]), sb += f(b[pb], a[pa]);
        pa = (pa + 1) % na, pb = (pb + 1) % nb;
    }
    write(sa), putch(' '), write(sb), putch('\n');
    return 0;
}