/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Solution: https://macesuted.moe/article/sp-ngcd
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

#define maxn 100005

const int prime[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int cnt[1 << 15], f[1 << 15], g[15][1 << 15], rev[1 << 15];

void solve(void) {
    int n = read<int>(), maxS = 1 << 15;
    memset(cnt, 0, sizeof(cnt));
    for (register int i = 0; i < n; i++) {
        long long num = read<long long>();
        int stat = 0;
        for (register int j = 0; j < 15; j++)
            if (num % prime[j] == 0) stat |= 1 << j;
        cnt[stat]++;
    }
    for (register int i = 0; i < maxS; i++) {
        f[i] = cnt[0];
        for (register int j = i; j; j = (j - 1) & i) f[i] += cnt[j];
    }
    for (register int t = 0; t < 15; t++)
        for (register int i = 0; i < maxS; i++) {
            g[t][i] = cnt[1 << t];
            if (i >> t & 1) continue;
            for (register int j = i; j; j = (j - 1) & i) g[t][i] += cnt[j | (1 << t)];
        }
    long long answer = 0;
    for (register int i = 0; i < maxS; i++) answer += 1LL * cnt[i] * f[rev[i]];
    for (register int i = 0; i < 15; i++)
        for (register int j = 0; j < maxS; j++) {
            if (!(j >> i & 1)) continue;
            answer += 1LL * cnt[j] * g[i][rev[j]];
        }
    write(answer), putch('\n');
    return;
}

int main() {
    for (register int i = 0; i < (1 << 15); i++) rev[i] = (~i) & ((1 << 15) - 1);
    int _ = read<int>();
    while (_--) solve();
    return 0;
}