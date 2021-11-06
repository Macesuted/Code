/**
 * @file 7089.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-04
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

#define maxn 105
#define maxm 10005

int a[maxn], f[maxn][maxm];

int ceil(int up, int down) { return (up + down - 1) / down; }

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    for (int i = 0; i <= m; i++) f[0][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            f[i][j] = numeric_limits<int>::max();
    for (int i = 1; i <= n; i++) {
        int lim = read<int>();
        static vector<int> rec;
        rec.clear();
        for (int l = 1, r; l <= lim; l = r + 1) {
            rec.push_back(l - 1);
            r = l;
            while (ceil(a[i], r + 1) == ceil(a[i], l) && r < lim) r++;
        }
        for (auto j : rec)
            for (int k = m, cost = ceil(a[i], j + 1); k >= j; k--)
                f[i][k] = min(f[i][k], f[i - 1][k - j] + cost);
    }
    int ans = numeric_limits<int>::max();
    for (int i = 0; i <= m; i++) ans = min(ans, f[n][i]);
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
    int _ = read<int>();
    while (_--) solve();
    return 0;
}