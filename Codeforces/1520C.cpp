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
inline void write(const T &t) {
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

#define maxn 105

int a[maxn][maxn];

int main() {
    int _ = read<int>();
    while (_--) {
        int n = read<int>();
        for (register int i = 0; i <= n + 1; i++)
            for (register int j = 0; j <= n + 1; j++) a[i][j] = 0;
        int ji = 1, ou = 2;
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= n; j++)
                if (ji <= n * n)
                    a[i][j] = ji, ji += 2;
                else if (ji > n * n)
                    a[i][j] = ou, ou += 2;
        bool flag = false;
        for (register int i = 1; i <= n; ++i)
            for (register int j = 1; j <= n; ++j) {
                if (abs(a[i][j] - a[i + 1][j]) == 1 && i + 1 <= n) flag = true;
                if (abs(a[i][j] - a[i - 1][j]) == 1 && i - 1 >= 1) flag = true;
                if (abs(a[i][j] - a[i][j + 1]) == 1 && j + 1 <= n) flag = true;
                if (abs(a[i][j] - a[i][j - 1]) == 1 && j - 1 >= 1) flag = true;
            }
        if (flag)
            putstr("-1\n");
        else
            for (register int i = 1; i <= n; i++)
                for (register int j = 1; j <= n; j++) write(a[i][j]), putch(" \n"[j == n]);
    }
    return 0;
}  // tat