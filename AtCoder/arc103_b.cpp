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

#define maxn 1005

typedef pair<long long, long long> pll;

pll a[maxn];
long long step[40], tail = 0;

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i].first = read<long long>(), a[i].second = read<long long>();
    bool bol = (abs(a[1].first) + abs(a[1].second)) & 1;
    for (register int i = 2; i <= n; i++)
        if (((abs(a[i].first) + abs(a[i].second)) & 1) ^ bol)
            return putstr("-1\n"), 0;
    for (register int i = 30; i >= bol; i--) step[++tail] = 1LL << i;
    step[++tail] = 1;
    write(tail), putch('\n');
    for (register int i = 1; i <= tail; i++) write(step[i]), putch(' ');
    putch('\n');
    for (register int i = 1; i <= n; i++) {
        long long tx = 0, ty = 0;
        for (register int j = 1; j <= tail; j++) {
            long long fx = abs(a[i].first - tx), fy = abs(a[i].second - ty);
            if (fx > fy) {
                if (tx < a[i].first)
                    tx += step[j], putch('R');
                else
                    tx -= step[j], putch('L');
            } else {
                if (ty < a[i].second)
                    ty += step[j], putch('U');
                else
                    ty -= step[j], putch('D');
            }
        }
        putch('\n');
    }
    return 0;
}