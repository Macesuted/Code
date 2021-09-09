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
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t')) s.push_back(c), c = getch();
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

typedef pair<int, int> pii;

pii a[maxn];
int ans[maxn];

int main() {
    int _ = read<int>();
    while (_--) {
        int n = read<int>(), m = read<int>(), x = read<int>();
        for (register int i = 1; i <= n; i++) a[i].first = read<int>(), a[i].second = i;
        sort(a + 1, a + n + 1, greater<pii>());
        static priority_queue<pii, vector<pii>, greater<pii> > que;
        while (!que.empty()) que.pop();
        for (register int i = 1; i <= m; i++) que.push((pii){0, i});
        for (register int i = 1; i <= n; i++) {
            pii p = que.top();
            que.pop();
            ans[a[i].second] = p.second;
            que.push((pii){p.first + a[i].first, p.second});
        }
        int beg = que.top().first, en = que.top().first;
        while (!que.empty()) en = que.top().first, que.pop();
        if (beg - en <= x) {
            putstr("YES\n");
            for (register int i = 1; i <= n; i++) write(ans[i]), putch(" \n"[i == n]);
        } else
            putstr("NO\n");
    }
    return 0;
}