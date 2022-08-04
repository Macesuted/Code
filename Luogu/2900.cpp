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

#define maxn 50005

typedef pair<int, int> pii;

pii a[maxn];
long long f[maxn];

inline long long X(int p) { return a[p + 1].first; }
inline long long Y(int p) { return f[p]; }

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i].first = read<int>(), a[i].second = read<int>();
    sort(a + 1, a + n + 1, greater<pii>());
    int j = 0;
    for (register int i = 1; i <= n; i++)
        if (a[i].second > a[j].second) a[++j] = a[i];
    n = j;
    static deque<int> que;
    que.clear(), que.push_back(0);
#define px que[que.size() - 2]
#define py que[que.size() - 1]
    for (register int i = 1; i <= n; i++) {
        long long k = -a[i].second;
        while (que.size() > 1 && (Y(py) - Y(px)) > k * (X(py) - X(px))) que.pop_back();
        f[i] = f[py] + 1LL * a[py + 1].first * a[i].second;
        while (que.size() > 1 &&
               (Y(que[0]) - Y(i)) * (X(que[1]) - X(que[0])) >= (Y(que[1]) - Y(que[0])) * (X(que[0]) - X(i)))
            que.pop_front();
        que.push_front(i);
    }
#undef px
#undef py
    write(f[n]), putch('\n');
    return 0;
}