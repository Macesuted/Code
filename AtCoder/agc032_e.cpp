/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://www.macesuted.cn/article/agc032e/
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

#define maxn 200005

int a[maxn], n, m, ans = 0x3f3f3f3f;

bool check(int lim) {
    int maxVal = 0;
    for (register int i = 1, j = 2 * lim; i < j; i++, j--) maxVal = max(maxVal, a[i] + a[j]);
    for (register int i = 2 * lim + 1, j = 2 * n; i < j; i++, j--) {
        if (a[i] + a[j] < m) return false;
        maxVal = max(maxVal, a[i] + a[j] - m);
    }
    ans = min(ans, maxVal);
    return true;
}

int main() {
    n = read<int>(), m = read<int>();
    for (register int i = 1; i <= 2 * n; i++) a[i] = read<int>();
    sort(a + 1, a + 2 * n + 1);
    int l = 0, r = n;
    check(0);
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        check(mid) ? r = mid : l = mid;
    }
    check(r);
    write(ans), putch('\n');
    return 0;
}