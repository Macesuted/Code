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

#define maxn 1005
#define maxk 105

long long lcmBit[maxn], f[maxn], g[maxk][maxn];

int main() {
    int n = read<int>(), k = read<int>(), mod = read<int>();
    for (register int i = 0, t = k; i < n; i++) {
        lcmBit[i] = t;
        if (t % 2 == 0) t /= 2;
        if (t % 5 == 0) t /= 5;
    }
    for (register int i = 1; i <= 100; i++) {
        g[i][0] = 1;
        long long p1 = 0, p2 = 1;
        for (register int j = 1; j <= n; j++) {
            p1 = (p1 * 10 + p2 * 10 / i) % mod, p2 = p2 * 10 % i;
            g[i][j] = (p1 + (p2 > 0)) % mod;
        }
    }
    for (register int i = 0; i < n; i++) {
        f[i] = (g[k][i + 1] + mod - g[k][i]) % mod;
        for (register int j = i - 1; ~j; j--)
            f[i] = (f[i] + mod - (g[lcmBit[j + 1]][i - j] + mod - g[lcmBit[j + 1]][i - j - 1]) * f[j] % mod) % mod;
    }
    long long answer = f[n - 1], p = 9;
    for (register int i = n - 2; ~i; i--) answer = (answer + p * f[i]) % mod, p = p * 10 % mod;
    write(answer), putch('\n');
    return 0;
}