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

int main() {
    int k = read<int>();
    if (!(k & 1)) return putstr("NO\n"), 0;
    putstr("YES\n");
    int n = 4 * k - 2, m = (4 * k - 2) * k / 2;
    write(n), putch(' '), write(m), putch('\n');
    int n2 = n / 2;
    for (register int i = 2; i <= k; i++) write(1), putch(' '), write(i), putch('\n');
    for (register int i = 2; i <= k; i++)
        for (register int j = k + 1; j <= 2 * k - 1; j++) write(i), putch(' '), write(j), putch('\n');
    for (register int i = k + 1; i <= 2 * k - 1; i += 2) write(i), putch(' '), write(i + 1), putch('\n');
    for (register int i = 2; i <= k; i++) write(n2 + 1), putch(' '), write(n2 + i), putch('\n');
    for (register int i = 2; i <= k; i++)
        for (register int j = k + 1; j <= 2 * k - 1; j++) write(n2 + i), putch(' '), write(n2 + j), putch('\n');
    for (register int i = k + 1; i <= 2 * k - 1; i += 2) write(n2 + i), putch(' '), write(n2 + i + 1), putch('\n');
    write(1), putch(' '), write(n2 + 1), putch('\n');
    return 0;
}