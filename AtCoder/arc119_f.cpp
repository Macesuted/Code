/**
 * @file arc119_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-03
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

#define maxn 4005
#define mod 1000000007

long long f[2][maxn][maxn][2];

long long Plus(long long& a, long long b) { return a = (a + b >= mod ? a + b - mod : a + b); }

void solve(void) {
    int n = read<int>() - 1, K = read<int>();
    string a = " " + getstr();
    if (a[1] != 'B') f[1][1][0][0] = 1;
    if (a[1] != 'A') f[1][0][1][1] = 1;
    for (int i = 1; i < n; i++) {
        bool thi = i & 1, tha = !thi;
        for (int j = 0; j <= K + 2; j++)
            for (int k = max(0, j - 2); k <= j + 2; k++) {
                if (a[i + 1] != 'B') Plus(f[tha][min(j + 1, k + 2)][k][0], f[thi][j][k][0]);              // AA
                if (a[i + 1] != 'A') Plus(f[tha][min(j, k + 2)][min(j + 1, k + 1)][1], f[thi][j][k][0]);  // AB
                if (a[i + 1] != 'B') Plus(f[tha][min(j + 1, k + 1)][min(j + 2, k)][0], f[thi][j][k][1]);  // BA
                if (a[i + 1] != 'A') Plus(f[tha][j][min(j + 2, k + 1)][1], f[thi][j][k][1]);              // BB
                f[thi][j][k][0] = f[thi][j][k][1] = 0;
            }
    }
    long long ans = 0;
    for (int i = 0; i <= K + 2; i++)
        for (int j = max(0, i - 2); j <= i + 2; j++)
            if (min(i, j) < K) Plus(ans, (f[n & 1][i][j][0] + f[n & 1][i][j][1]) % mod);
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
