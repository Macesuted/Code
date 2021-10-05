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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

#define mod 1000000007

class Matrix {
   private:
    vector<vector<int>> a;

   public:
    int n, m;
    void resize(int _n, int _m) {
        n = _n, m = _m;
        a.resize(n + 1);
        for (register int i = 1; i <= n; i++) a[i].resize(m + 1);
        return;
    }
    vector<int>& operator[](int x) { return a[x]; }
    int get(int x, int y) const { return a[x][y]; }
    Matrix operator*(const Matrix& b) {
        Matrix ans;
        assert(this->m == b.n);
        int n = this->n, m = b.m;
        ans.resize(n, m);
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= m; j++)
                for (register int k = 1; k <= this->m; k++)
                    ans[i][j] = (ans[i][j] + (long long)a[i][k] * b.get(k, j)) % mod;
        return ans;
    }
    Matrix operator^(int x) {
        assert(this->n == this->m);
        Matrix ans, base = *this;
        int n = base.n;
        ans.resize(n, n);
        for (register int i = 1; i <= n; i++) ans[i][i] = 1;
        while (x) {
            if (x & 1) ans = ans * base;
            base = base * base;
            x >>= 1;
        }
        return ans;
    }
};

long long f[1 << 7], g[1 << 7], h[8];

int main() {
    h[0] = 1, h[1] = 2;
    for (register int i = 2; i <= 7; i++) {
        h[i] = 2;
        for (register int j = i - 2; ~j; j--) h[i] = (h[i] + h[j]) % mod;
    }
    for (register int t = 1; t <= 7; t++) {
        if (t == 1) {
            f[1] = 1;
        } else {
            for (register int i = 0; i < (1 << (t - 1)); i++) swap(f[i], f[1 << (t - 1) | i]);
        }
        int cnt = read<int>();
        for (register int i = 0; i < (1 << t); i++) {
            g[i] = 1;
            int l = (i & 1), r = t - (i >> (t - 1) & 1) - 1;
            int last = l;
            for (register int j = l + 1; j <= r; j++)
                if (j == r || !(i >> j & 1))
                    g[i] = g[i] * h[j - last] % mod, last = j;
        }
        if (t == 1) g[1] = 0;
        Matrix ans, base;
        ans.resize(1, 1 << t), base.resize(1 << t, 1 << t);
        for (register int i = 0; i < (1 << t); i++) ans[1][i + 1] = f[i];
        for (register int i = 0; i < (1 << t); i++)
            for (register int j = 0; j < (1 << t); j++)
                base[i + 1][j + 1] = g[i & j];
        ans = ans * (base ^ cnt);
        for (register int i = 0; i < (1 << t); i++) f[i] = ans[1][i + 1];
    }
    write(f[(1 << 7) - 1]), putch('\n');
    return 0;
}