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
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 300005

long long tim[maxn], cost[maxn];
int s;
long long f[maxn];

inline long double X(int p) { return cost[p]; }
inline long double Y(int p) { return f[p] - s * cost[p]; }
// (f[i]-s*cost[i])-(f[j]-s*cost[j])/(cost[i]-cost[j])<time[p]

int main() {
    int n = read<int>();
    s = read<int>();
    for (register int i = 1; i <= n; i++) tim[i] = read<int>() + tim[i - 1], cost[i] = read<int>() + cost[i - 1];
    static deque<int> que;
    que.clear();
    que.push_front(0);
    for (register int i = 1; i <= n; i++) {
        int l = 0, r = que.size() - 1;
        if (que.size() > 1 && (Y(que[1]) - Y(que[0])) / (X(que[1]) - X(que[0])) >= tim[i]) r = 0;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            ((Y(que[mid + 1]) - Y(que[mid])) / (X(que[mid + 1]) - X(que[mid])) < tim[i]) ? l = mid : r = mid;
        }
        f[i] = f[que[r]] + s * (cost[n] - cost[que[r]]) + tim[i] * (cost[i] - cost[que[r]]);
        while (que.size() > 1 &&
               (Y(que[que.size() - 2]) - Y(que[que.size() - 1])) * (X(que[que.size() - 1]) - X(i)) >=
                   (Y(que[que.size() - 1]) - Y(i)) * (X(que[que.size() - 2]) - X(que[que.size() - 1])))
            que.pop_back();
        que.push_back(i);
    }
    write(f[n]), putch('\n');
    return 0;
}