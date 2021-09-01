/**
 * @author Macesuted (macesuted@outlook.com)
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

#define maxn 100005
#define maxVal 15
#define maxStatu (1 << maxVal)

int a[maxn], f[maxStatu], val[maxStatu], cnt[maxVal];

int main() {
    int n = read<int>(), answer = 0;
    for (register int i = 1, from, to, dist; i < n; i++) {
        from = read<int>(), to = read<int>(), dist = read<int>();
        a[from] ^= dist, a[to] ^= dist;
    }
    for (register int i = 0; i < n; i++)
        if (a[i]) cnt[a[i] - 1]++;
    int S = 0;
    for (register int i = 0; i < maxVal; i++) answer += cnt[i] >> 1, S |= (cnt[i] & 1) << i;
    for (register int i = 0; i < maxStatu; i++)
        for (register int j = 0; j < maxVal; j++)
            if ((i >> j & 1) && cnt[j]) val[i] ^= j + 1;
    for (register int i = 1; i <= S; i++) f[i] = f[i >> 1] + (i & 1);
    for (register int i = 1; i <= S; i++) f[i]--;
    for (register int i = 1; i <= S; i++)
        if (!val[i])
            for (register int j = (i - 1) & i; j; j = (j - 1) & i)
                if (!val[j]) f[i] = min(f[i], f[j] + f[i ^ j]);
    write(answer + f[S]), putch('\n');
    return 0;
}