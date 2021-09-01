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

#define maxn 16
#define maxm 400
#define mod 1000000007

int graph[maxn][maxn], cnt[maxn][1 << maxn];
long long f[1 << maxn], pow2[maxm];

inline int lowbit(int x) { return x & -x; }

int main() {
    pow2[0] = 1;
    for (register int i = 1; i < maxm; i++) pow2[i] = pow2[i - 1] * 2 % mod;
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= m; i++) {
        int x = read<int>() - 1, y = read<int>() - 1;
        graph[x][y]++;
    }
    for (register int i = 0; i < n; i++)
        for (register int j = 1; j < (1 << n); j++)
            cnt[i][j] = cnt[i][j ^ lowbit(j)] + graph[i][(int)log2(lowbit(j))];
    f[0] = 1;
    for (register int i = 1; i < (1 << n); i++)
        for (register int j = i; j; j = (j - 1) & i) {
            if ((j & 1) ^ (j >> 1 & 1)) continue;
            long long ans = 1;
            for (register int t = 0; t < n; t++)
                if (j >> t & 1)
                    ans = ans * pow2[cnt[t][i ^ j]] % mod;
                else if (i >> t & 1)
                    ans = ans * (pow2[cnt[t][j]] - 1) % mod;
            f[i] = (f[i] + f[i ^ j] * ans) % mod;
        }
    write((pow2[m] + mod - f[(1 << n) - 1]) % mod), putch('\n');
    return 0;
}