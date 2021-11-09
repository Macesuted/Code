/**
 * @file 1208F.cpp
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

#define maxn 1000005
#define maxlgn 22

typedef pair<int, int> pii;

bool mem1;

int a[maxn];
pii f[1 << maxlgn];

inline void update(pii& x, int v) {
    if (v == x.first || v == x.second) return;
    if (v > x.first)
        x.second = x.first, x.first = v;
    else if (v > x.second)
        x.second = v;
    return;
}

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) update(f[a[i] = read<int>()], i);
    for (int i = (1 << maxlgn) - 1; ~i; i--)
        for (int j = 0; j < maxlgn; j++)
            if (i >> j & 1)
                update(f[i ^ (1 << j)], f[i].first), update(f[i ^ (1 << j)], f[i].second);
    int ans = 0;
    for (int i = 1; i <= n - 2; i++) {
        int t = 0;
        for (int j = maxlgn - 1; ~j; j--)
            if (!(a[i] >> j & 1) && f[t | (1 << j)].second > i)
                t ^= 1 << j;
        ans = max(ans, a[i] | t);
    }
    write(ans), putch('\n');
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
