/**
 * @file 1379E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-01
 *
 * @copyright Copyright (c) 2021
 *
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

bool mem1;

#define maxn 100005

int f[maxn];

inline bool is2pow(int n) { return n - (n & -n) == 0; }

void solve(void) {
    int n = read<int>(), k = read<int>();
    if (k > max(0, (n - 3) / 2) || !(n & 1)) return putstr("NO");
    if (k == 0 && !is2pow(n + 1)) return putstr("NO");
    if (k == 1 && is2pow(n + 1)) return putstr("NO");
    if (k == 2 && n == 9) return putstr("NO");
    putstr("YES\n");
    int t = max(0, 2 * k - 2);
    for (int i = 2; i < t; i += 2) f[i] = f[i + 1] = i - 1;
    f[t] = t - 1;
    for (int i = 1; i + t <= n; i++)
        if (i == 1)
            f[i + t] = max(0, t - 1);
        else
            f[i + t] = (i >> 1) + t;
    if (k && is2pow(n - t + 1)) f[n - 1] = f[n] = 2;
    for (int i = 1; i <= n; i++) write(f[i]), putch(' ');
    putch('\n');
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}