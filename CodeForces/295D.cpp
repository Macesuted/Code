/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Draft: https://img-kysic-1258722770.file.myqcloud.com/b78115e628143efb1c9163c7bd5d44c7/75b95a13254dd.png
 *      My Tutorial: https://www.macesuted.cn/article/cf979e/
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

#define maxn 2005
#define mod 1000000007

long long f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], cac[maxn][maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 0; i <= m - 2; i++) f[1][i] = 1;
    for (register int i = 2; i <= n; i++) {
        f[i][0] = cac[i][0] = f[i - 1][0];
        for (register int j = 1; j <= m - 2; j++)
            cac[i][j] = (cac[i][j - 1] + f[i - 1][j]) % mod, f[i][j] = (f[i][j - 1] + cac[i][j]) % mod;
    }
    for (register int i = 1; i <= n; i++)
        for (register int j = 0; j <= m - 2; j++)
            g[i][j] = (g[i - 1][j] + f[i][j]) % mod;
    memset(cac, 0, sizeof(cac));
    for (register int i = 1; i < n; i++)
        for (register int j = 1; j <= m - 2; j++)
            cac[i][j] = (cac[i][j - 1] + g[i][j - 1]) % mod, h[i][j] = (h[i][j - 1] + cac[i][j] + g[i][j - 1]) % mod;
    long long answer = 0;
    for (register int i = 1; i <= n; i++)
        for (register int j = 0; j <= m - 2; j++)
            answer = (answer + (m - j - 1) * g[i][j] % mod * (1 + h[n - i][j])) % mod;
    write(answer), putch('\n');
    return 0;
}