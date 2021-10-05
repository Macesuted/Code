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
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t')) s.push_back(c), c = getch();
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

typedef complex<double> Complex;

const double Pi = acos(-1.0);

vector<Complex> a, b;
vector<int> rev;

void DFT(vector<Complex>& a, int type) {
    int len = a.size();
    for (register int i = 0; i < len; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (register int block = 1; block < len; block <<= 1) {
        Complex Wn(cos(Pi / block), type * sin(Pi / block));
        for (register int l = 0; l < len; l += block << 1) {
            Complex W(1, 0);
            for (register int p = l; p < l + block; p++, W *= Wn) {
                Complex x = a[p], y = W * a[p + block];
                a[p] = x + y, a[p + block] = x - y;
            }
        }
    }
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    int len = 1, lgLen = 0;
    while (len <= n + m) len <<= 1, lgLen++;
    a.resize(len), b.resize(len), rev.resize(len);
    for (register int i = 0; i <= n; i++) a[i] = (Complex){(double)read<int>(), 0};
    for (register int i = 0; i <= m; i++) b[i] = (Complex){(double)read<int>(), 0};
    for (register int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lgLen - 1));
    DFT(a, 1), DFT(b, 1);
    for (register int i = 0; i < len; i++) a[i] *= b[i];
    DFT(a, -1);
    a.resize(n + m + 1);
    for (register int i = 0; i <= n + m; i++) write((int)(a[i].real() / len + 0.5)), putch(" \n"[i == n + m]);
    return 0;
}