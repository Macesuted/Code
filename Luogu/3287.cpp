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

#define maxV1 5505
#define maxV2 505

inline int fmax(int x, int y) { return x > y ? x : y; }

int tree[maxV1][maxV2];
void insert(int x, int y, int val) {
    for (register int i = x; i < maxV1; i += i & -i)
        for (register int j = y; j < maxV2; j += j & -j) tree[i][j] = fmax(tree[i][j], val);
    return;
}
int maxVal(int x, int y) {
    int ans = 0;
    for (register int i = x; i; i -= i & -i)
        for (register int j = y; j; j -= j & -j) ans = fmax(ans, tree[i][j]);
    return ans;
}

int main() {
    int n = read<int>(), k = read<int>();
    for (register int i = 1, a; i <= n; i++) {
        a = read<int>();
        for (register int j = k; ~j; j--) insert(a + j, j + 1, maxVal(a + j, j + 1) + 1);
    }
    write(maxVal(maxV1 - 1, maxV2 - 1)), putch('\n');
    return 0;
}