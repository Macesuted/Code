/**
 * @file 3790.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-19
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

const int maxn = 1505;
const int mod = 1e9 + 7;
const double PI = acos(-1);

struct Node {
    int x, y, p;
    double fv;
};

long long f[maxn];
Node P[maxn], Q[maxn];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n = read<int>();
    if (n == 1) return cout << 0 << endl, void();
    for (int i = 1; i <= n; i++) P[i].p = read<int>(), P[i].x = read<int>(), P[i].y = read<int>();
    long long ans = 0;
    auto func = [](Node a, Node p) { return atan2(a.y - p.y, a.x - p.x); };
    auto in = [](double p, double l, double r) {
        while (p < l && p + 2 * PI <= r) p += 2 * PI;
        while (p > r && p - 2 * PI >= l) p -= 2 * PI;
        return l <= p && p <= r;
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1, k = 1; j <= n; j++)
            if (i != j) Q[k] = P[j], Q[k].fv = func(Q[k], P[i]), k++;
        sort(Q + 1, Q + n, [](Node a, Node b) { return a.fv < b.fv; });
        long long p = 0;
        for (int l = 1, r = 1; l < n; l++) {
            p = p * Pow(mod + 1 - Q[l].p, mod - 2) % mod;
            if (l == r) r = l % (n - 1) + 1, p = 1;
            while (r != l && Q[r].p != 1 && in(Q[r].fv, Q[l].fv, Q[l].fv + PI))
                p = p * (mod + 1 - Q[r].p) % mod, r = r % (n - 1) + 1;
            if (r != l && Q[r].p == 1 && in(Q[r].fv, Q[l].fv, Q[l].fv + PI))
                continue;
            ans = (ans + p * Q[l].p % mod * P[i].p) % mod;
        }
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j; j--)
            f[j] = (f[j] * (mod + 1 - P[i].p) + f[j - 1] * P[i].p) % mod;
        f[0] = f[0] * (mod + 1 - P[i].p) % mod;
    }
    long long ans2 = 0;
    for (int i = 1; i <= n; i++) ans2 = (ans2 + f[i] * i) % mod;
    ans = (ans + mod - f[0] * 3 % mod) % mod;
    cout << ((ans2 - 1) % mod * 3LL + mod - ans) % mod << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("point.in", "r", stdin), freopen("point.out", "w", stdout);
#endif
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
