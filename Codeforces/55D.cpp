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

int a[2550];
long long f[20][2550][50];

vector<int> bits;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int lcm(int x, int y) { return y ? x / gcd(x, y) * y : x; }

long long dfs(int p, int val, int lcmv, bool op) {
    if (p < 0) return val % lcmv == 0;
    if (!op && f[p][val][a[lcmv]]) return f[p][val][a[lcmv]];
    int lim = op ? bits[p] : 9;
    long long answer = 0;
    for (register int i = 0; i <= lim; i++)
        answer += dfs(p - 1, (val * 10 + i) % 2520, lcm(lcmv, i), op & (i == lim));
    if (!op) f[p][val][a[lcmv]] = answer;
    return answer;
}

long long work(long long val) {
    bits.clear();
    while (val) bits.push_back(val % 10), val /= 10;
    return dfs(bits.size() - 1, 0, 1, true);
}

int main() {
    for (register int i = 1, cnt = 0; i <= 2520; i++)
        if (2520 % i == 0) a[i] = ++cnt;
    int _ = read<int>();
    while (_--) {
        long long l = read<long long>(), r = read<long long>();
        write(work(r) - work(l - 1)), putch('\n');
    }
    return 0;
}