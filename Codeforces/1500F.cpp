/**
 * @file 1500F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-03
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/cf1500f
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

#define maxn 1000005

typedef pair<long long, long long> pll;

long long a[maxn], d[maxn], w[maxn], v[maxn], limd[maxn];
set<pll> S;

void solve(void) {
    int n = read<int>();
    long long C = read<long long>();
    for (int i = 1; i < n; i++) limd[i] = numeric_limits<long long>::max();
    for (int i = 1; i <= n - 2; i++)
        w[i] = read<long long>(), limd[i] = min(limd[i], w[i]), limd[i + 1] = min(limd[i + 1], w[i]);
    S.emplace(0, limd[1]);
    long long A = +1, B = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (A == +1) {
            while (!S.empty() && S.rbegin()->first + B > limd[i]) S.erase(--S.end());
            if (!S.empty() && S.rbegin()->second + B > limd[i]) {
                int l = S.rbegin()->first;
                S.erase(--S.end()), S.emplace(l, limd[i] - B);
            }
        } else {
            while (!S.empty() && -S.begin()->second + B > limd[i]) S.erase(S.begin());
            if (!S.empty() && -S.begin()->second + B > limd[i]) {
                int r = S.begin()->second;
                S.erase(S.begin()), S.emplace(B - limd[i], r);
            }
        }
        long long tw = (w[i] - B) / A;
        auto p = S.lower_bound({tw + 1, tw + 1});
        if (p != S.begin() && (--p)->second >= tw) {
            v[i] = w[i];
            S.clear(), S.emplace(0, limd[i + 1]), A = +1, B = 0;
            continue;
        }
        if (S.empty()) return putstr("NO\n");
        v[i] = S.begin()->first * A + B;
        if (i == n - 1) break;
        A = -A, B = w[i] - B;
        tw = (w[i] - B) / A;
        p = S.lower_bound({tw + 1, tw + 1});
        if (p == S.begin() || (--p)->second < tw) S.emplace(tw, tw);
    }
    d[n - 1] = v[n - 1];
    putstr("YES\n");
    for (int i = n - 2; i; i--)
        if (v[i] == w[i])
            d[i] = w[i];
        else if (d[i + 1] == w[i])
            d[i] = v[i];
        else
            d[i] = abs(w[i] - d[i + 1]);
    long long minVal = 0, pre = 0;
    for (int i = 2, id = +1; i <= n - 1; i++) {
        if (abs(d[i - 1]) + abs(d[i]) != w[i - 1]) id = -id;
        d[i] *= id;
        minVal = min(minVal, pre += d[i]);
    }
    a[1] = -minVal;
    for (int i = 2; i <= n; i++) a[i] = a[i - 1] + d[i - 1];
    for (int i = 1; i <= n; i++) write(a[i]), putch(" \n"[i == n]);
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
