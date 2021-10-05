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

#define maxn 20005

long long a[maxn], dis[maxn];

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<long long>(), dis[i] = read<long long>();
    for (register int i = 1; i <= n; i++) a[i] += a[i - 1];
    long long total = 0;
    for (register int i = 1; i <= n; i++) total += a[i] * dis[i];
    for (register int i = n; i; i--) dis[i] += dis[i + 1];
    static deque<int> que;
    que.clear(), que.push_back(n);
#define X(p) (dis[p])
#define Y(p) (dis[p] * a[p])
#define pf1 (que[0])
#define pf2 (que[1])
#define pb1 (que[que.size() - 2])
#define pb2 (que[que.size() - 1])
    long long answer = 0;
    for (register int i = n - 1; i; i--) {
        long long k = a[i];
        while (que.size() > 1 && (Y(pf2) - Y(pf1)) > (X(pf2) - X(pf1)) * k) que.pop_front();
        answer = max(answer, dis[pf1] * a[pf1] + (dis[i] - dis[pf1]) * a[i]);
        while (que.size() > 1 && (Y(pb2) - Y(pb1)) * (X(i) - X(pb2)) < (Y(i) - Y(pb2)) * (X(pb2) - X(pb1)))
            que.pop_back();
        que.push_back(i);
    }
    write(total - answer), putch('\n');
    return 0;
}