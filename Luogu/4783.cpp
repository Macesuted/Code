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

#define maxn 405
#define mod 1000000007

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

class Matrix {
   private:
    long long matrix[maxn][maxn];

   public:
    int n, m;

    void resize(int _n, int _m) {
        n = _n, m = _m;
        return;
    }
    long long* operator[](int p) { return matrix[p]; }
    long long get(int i, int j) const { return matrix[i][j]; }
    bool getRev(void) {
        Matrix a = *this, b;
        assert(a.n == a.m);
        int n = a.n;
        b.resize(n, n);
        for (int i = 0; i < n; i++) b[i][i] = 1;
        for (int i = 0; i < n; i++) {
            int p = i;
            while (p < n && a[p][i] == 0) p++;
            if (p >= n) return false;
            for (int j = 0; j < n; j++) swap(a[p][j], a[i][j]), swap(b[p][j], b[i][j]);
            long long inv = Pow(a[i][i], mod - 2);
            for (int j = 0; j < n; j++) a[i][j] = a[i][j] * inv % mod, b[i][j] = b[i][j] * inv % mod;
            for (int j = 0; j < n; j++) {
                if (j == i || a[j][i] == 0) continue;
                long long mul = a[j][i] % mod;
                for (int k = 0; k < n; k++)
                    a[j][k] = (a[j][k] + mod - a[i][k] * mul % mod) % mod,
                    b[j][k] = (b[j][k] + mod - b[i][k] * mul % mod) % mod;
            }
        }
        *this = b;
        return true;
    }
};

int main() {
    int n = read<int>();
    Matrix m;
    m.resize(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) m[i][j] = read<int>();
    if (!m.getRev()) return putstr("No Solution\n"), 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) write(m[i][j]), putch(" \n"[j == n - 1]);
    return 0;
}