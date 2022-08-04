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

#define maxlgn 62
long long mod;

long long f[maxlgn][2][2][2], g[maxlgn][2][2][2];

int main() {
    int _ = read<int>();
    while (_--) {
        long long n = read<long long>(), m = read<long long>(), k = read<long long>();
        mod = read<long long>();
        memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
        g[maxlgn - 1][1][1][1] = 1;
        for (register int i = maxlgn - 2; ~i; i--) {
            int np = (n >> i & 1), mp = (m >> i & 1), kp = (k >> i & 1);
            for (register int a = 0; a <= 1; a++)
                for (register int b = 0; b <= 1; b++)
                    for (register int c = 0; c <= 1; c++)
                        if (f[i + 1][a][b][c] || g[i + 1][a][b][c]) {
                            for (register int ca = 0; ca <= (a ? np : 1); ca++)
                                for (register int cb = 0; cb <= (b ? mp : 1); cb++) {
                                    int cc = ca ^ cb;
                                    if (c && cc < kp) continue;
                                    int pa = (a && ca == np), pb = (b && cb == mp), pc = (c && cc == kp);
                                    g[i][pa][pb][pc] = (g[i][pa][pb][pc] + g[i + 1][a][b][c]) % mod;
                                    f[i][pa][pb][pc] = (f[i][pa][pb][pc] + f[i + 1][a][b][c] +
                                                        (1LL << i) % mod * (cc - kp + mod) % mod * g[i + 1][a][b][c]) %
                                                       mod;
                                }
                        }
        }
        write(f[0][0][0][0]), putch('\n');
    }
    return 0;
}