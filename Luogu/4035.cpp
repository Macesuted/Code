/**
 * @author Macesuted
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

inline void flush(void) {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
    return;
}

inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
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
    x *= f;
    return x;
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
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 25

class Gauss {
   public:
    double a[maxn][maxn];
    int n, m;

    Gauss(void) { n = m = 0; }
    int work(void) {
        for (register int i = 1; i <= n; i++) {
            int pos = i;
            for (register int j = i + 1; j <= m; j++)
                if (fabs(a[j][i]) > fabs(a[pos][i])) pos = j;
            for (register int j = 0; j <= n; j++) swap(a[i][j], a[pos][j]);
            if (!a[i][i]) return 0;
            for (register int j = 1; j <= m; j++)
                if (j != i) {
                    double mul = a[j][i] / a[i][i];
                    for (register int k = i + 1; k <= n; k++) a[j][k] -= a[i][k] * mul;
                    a[j][0] -= a[i][0] * mul;
                }
        }
        for (register int i = 1; i <= m; i++) a[i][0] = a[i][0] / a[i][i], a[i][i] = 1;
        if (m > n) return 2;
        return 1;
    }
};

Gauss gauss;

double inp[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (register int i = 1; i <= n + 1; i++)
        for (register int j = 1; j <= n; j++) cin >> inp[i][j];
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            gauss.a[i][j] = 2 * (inp[i][j] - inp[i + 1][j]),
            gauss.a[i][0] += inp[i][j] * inp[i][j] - inp[i + 1][j] * inp[i + 1][j];
    gauss.n = gauss.m = n;
    gauss.work();
    for (register int i = 1; i <= n; i++) printf("%.3lf%c", gauss.a[i][0], " \n"[i == n]);
    return 0;
}