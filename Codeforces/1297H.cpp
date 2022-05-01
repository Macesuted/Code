/**
 * @file 1297H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

string f[maxn][maxn], g[maxn][maxn];

void solve(void) {
    string a = getstr();
    int n = a.size();
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) f[i][j] = a;
    string ans = a, ansg = string(n, 'R');
    f[1][0] = string(1, a[0]), g[1][0] = "R";
    auto smin = [](const string& a, const string& b) {
        for (int i = 0; i < (int)min(a.size(), b.size()); i++)
            if (a[i] != b[i]) return a[i] < b[i] ? a : b;
        return a.size() < b.size() ? a : b;
    };
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            if (f[i][j] == a) continue;
            if (a[i] < f[i][j][j] && smin(ans, f[i][j]) != ans) {
                ans = f[i][j], ansg = g[i][j];
                while ((int)ansg.size() < n) ansg.push_back('B');
            }
            if (a[i] == f[i][j][j] && smin(f[i][j], f[i + 1][j + 1]) == f[i][j])
                f[i + 1][j + 1] = f[i][j], g[i + 1][j + 1] = g[i][j], g[i + 1][j + 1].push_back('B');
            f[i][j].push_back(a[i]);
            if (a[i] >= f[i][j][j] && smin(f[i + 1][j], f[i][j]) != f[i + 1][j])
                f[i + 1][j] = f[i][j], g[i + 1][j] = g[i][j], g[i + 1][j].push_back('R');
            f[i][j].pop_back();
        }
    for (int i = 0; i <= n; i++)
        if (smin(ans, f[n][i]) != ans) ans = f[n][i], ansg = g[n][i];
    putstr(ansg), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
