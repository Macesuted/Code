/**
 * @file 367E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-09
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

#define maxn 100005
#define mod 1000000007

typedef pair<int, int> pii;

bool mem1;

void solve(void) {
    int n = read<int>(), m = read<int>(), x = read<int>();
    if (n > m) return putstr("0\n");
    vector<vector<vector<int>>> f(2, vector<vector<int>>(n + 1, vector<int>(n + 1, 0)));
    f[0][0][0] = 1;
    for (int i = 1; i <= m; i++) {
        bool thi = i & 1, tha = !thi;
        for (int j = 0; j <= min(n, i); j++)
            for (int k = 0; k <= min(n, i); k++)
                f[thi][j][k] = 0;
        for (int j = 0; j <= min(n, i - 1); j++)
            for (int k = 0; k <= min(j, i - 1); k++) {
                if (i != x) f[thi][j][k] = (f[thi][j][k] + f[tha][j][k]) % mod;
                if (j + 1 <= n) f[thi][j + 1][k + 1] = (f[thi][j + 1][k + 1] + f[tha][j][k]) % mod;
                if (j + 1 <= n) f[thi][j + 1][k] = (f[thi][j + 1][k] + f[tha][j][k]) % mod;
                if (j >= k + 1 && i != x) f[thi][j][k + 1] = (f[thi][j][k + 1] + f[tha][j][k]) % mod;
            }
    }
    long long answer = f[m & 1][n][n];
    for (int i = 1; i <= n; i++) answer = answer * i % mod;
    write(answer), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
