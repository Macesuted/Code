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

#define maxn 305
#define maxV 105

int tree[maxV][maxn][maxn];
int a[maxn][maxn];

void insert(int id, int x, int y, int val) {
    for (register int i = x; i < maxn; i += i & -i)
        for (register int j = y; j < maxn; j += j & -j)
            tree[id][i][j] += val;
    return;
}
int getSum(int id, int x, int y) {
    if (x == 0 || y == 0) return 0;
    int sum = 0;
    for (register int i = x; i; i -= i & -i)
        for (register int j = y; j; j -= j & -j)
            sum += tree[id][i][j];
    return sum;
}

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= m; j++)
            insert(a[i][j] = read<int>(), i, j, 1);
    int q = read<int>();
    while (q--)
        if (read<int>() == 1) {
            int x = read<int>(), y = read<int>(), c = read<int>();
            insert(a[x][y], x, y, -1), insert(a[x][y] = c, x, y, 1);
        } else {
            int X1 = read<int>(), X2 = read<int>(), Y1 = read<int>(), Y2 = read<int>(), c = read<int>();
            write(getSum(c, X2, Y2) - getSum(c, X1 - 1, Y2) - getSum(c, X2, Y1 - 1) + getSum(c, X1 - 1, Y1 - 1)), putch('\n');
        }
    return 0;
}