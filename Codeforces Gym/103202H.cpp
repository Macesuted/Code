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

#define maxn 505
#define maxq 300005

typedef pair<int, int> pii;

long long f[maxq];
int d[maxn], k[maxn], c[maxn];
int belong[maxq], to[maxn];

inline long long Min(long long& x, long long y) { return x = (x < y ? x : y); }

int main() {
    int n = read<int>(), m = read<int>(), r = read<int>();
    for (register int i = 1; i <= n; i++) d[i] = read<int>(), k[i] = read<int>(), c[i] = read<int>();
    int sum = 0;
    for (register int i = 1; i <= m; i++) {
        int p = read<int>(), q = read<int>();
        for (register int j = sum + 1; j <= sum + q; j++) belong[j] = p;
        sum += q;
    }
    sort(belong + 1, belong + sum + 1);
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (register int i = 0; i < sum; i++) {
        if (i) Min(f[i], f[i - 1] + r);
        for (register int j = 1; j <= n; j++) {
            while (belong[to[j] + 1] < belong[i + 1] + d[j] && to[j] < i + k[j] && to[j] < sum) to[j]++;
            Min(f[to[j]], f[i] + c[j]);
        }
    }
    write(Min(f[sum], f[sum - 1] + r)), putch('\n');
    return 0;
}