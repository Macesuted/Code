/**
 * @file 1383D.cpp
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

#define maxn 255

typedef pair<int, int> pii;

int a[maxn][maxn], b[maxn][maxn];
bool lmax[maxn * maxn], cmax[maxn * maxn];
queue<pii> up, lef;

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = read<int>();
    for (int i = 1; i <= n; i++) {
        int maxv = 0;
        for (int j = 1; j <= m; j++) maxv = max(maxv, a[i][j]);
        lmax[maxv] = true;
    }
    for (int i = 1; i <= m; i++) {
        int maxv = 0;
        for (int j = 1; j <= n; j++) maxv = max(maxv, a[j][i]);
        cmax[maxv] = true;
    }
    for (int i = n * m, x = 0, y = 0; i; i--) {
        if (lmax[i] || cmax[i]) {
            x += lmax[i], y += cmax[i];
            if (lmax[i] && y > 1) lef.push({x, y - 1});
            if (cmax[i] && x > 1) up.push({x - 1, y});
            b[x][y] = i;
        } else {
            if (!up.empty()) {
                pii p = up.front();
                up.pop();
                b[p.first][p.second] = i;
                if (p.first > 1) up.emplace(p.first - 1, p.second);
            } else {
                pii p = lef.front();
                lef.pop();
                b[p.first][p.second] = i;
                if (p.second > 1) lef.emplace(p.first, p.second - 1);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) write(b[i][j]), putch(" \n"[j == m]);
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