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

#define maxn 55
#define mod 1000000007

int a[maxn];
long long pow2[maxn];
long long f[maxn][2][2][2];

int main() {
    int n = read<int>(), p = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    pow2[0] = 1;
    for (register int i = 1; i <= n; i++) pow2[i] = (pow2[i - 1] << 1) % mod;
    f[0][0][0][0] = 1;
    for (register int i = 1; i <= n; i++)
        for (register int ba = 0; ba <= 1; ba++)
            for (register int bb = 0; bb <= 1; bb++)
                for (register int bw = 0; bw <= 1; bw++) {
                    long long& g = f[i - 1][ba][bb][bw];
                    if (a[i] != 0) {
                        if (bb) {
                            f[i][ba][bb][bw] = (f[i][ba][bb][bw] + g * pow2[i - 2]) % mod;
                            f[i][!ba][bb][bw | 1] = (f[i][!ba][bb][bw | 1] + g * pow2[i - 2]) % mod;
                        } else
                            f[i][!ba][bb][bw | 1] = (f[i][!ba][bb][bw | 1] + g * pow2[i - 1]) % mod;
                    }
                    if (a[i] != 1) {
                        if (bw) {
                            f[i][ba][bb][bw] = (f[i][ba][bb][bw] + g * pow2[i - 2]) % mod;
                            f[i][!ba][bb | 1][bw] = (f[i][!ba][bb | 1][bw] + g * pow2[i - 2]) % mod;
                        } else
                            f[i][!ba][bb | 1][bw] = (f[i][!ba][bb | 1][bw] + g * pow2[i - 1]) % mod;
                    }
                }
    write((f[n][p][0][0] + f[n][p][0][1] + f[n][p][1][0] + f[n][p][1][1]) % mod), putch('\n');
    return 0;
}