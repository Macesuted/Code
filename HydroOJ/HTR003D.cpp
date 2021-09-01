/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My tutorial: https://macesuted.cn/article/htr003d/
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

#define maxn 55
#define maxk 2505
#define mod 1000000009

int a[maxn];
long long f[maxn][maxn][maxk];

long long Mod(long long& a) { return a = (a >= mod ? a - mod : a); }

int main() {
    int n = read<int>(), K = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    f[0][0][0] = 1;
    for (register int i = 0; i < n; i++)
        for (register int j = 0; j <= i; j++)
            for (register int k = 0; k <= K; k++)
                if (f[i][j][k]) {
                    // T[j] 向前匹配，S[j] 留空
                    if (j && k + a[i + 1] <= K) Mod(f[i + 1][j][k + a[i + 1]] += 1LL * j * f[i][j][k] % mod);
                    // T[j] 向后匹配，S[j] 留空
                    if (k + 2 * a[i + 1] <= K) Mod(f[i + 1][j + 1][k + 2 * a[i + 1]] += f[i][j][k]);
                    // T[j] 向前匹配，S[j] 填充
                    if (j) Mod(f[i + 1][j - 1][k] += 1LL * j * j % mod * f[i][j][k] % mod);
                    // T[j] = S[j]
                    if (k + a[i + 1] <= K) Mod(f[i + 1][j][k + a[i + 1]] += f[i][j][k]);
                    // T[j] 向后匹配，S[j] 填充
                    if (j && k + a[i + 1] <= K) Mod(f[i + 1][j][k + a[i + 1]] += 1LL * j * f[i][j][k] % mod);
                }
    write(f[n][0][K]), putch('\n');
    return 0;
}
