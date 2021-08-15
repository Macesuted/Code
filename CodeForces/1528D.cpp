/**
 * @author Macesuted (macesuted@qq.com)
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

#define maxn 605

typedef pair<int, int> pii;

long long dist[maxn];
bool vis[maxn];

vector<vector<pii> > graph;

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= m; i++) {
        int from = read<int>() + 1, to = read<int>() + 1, dist = read<int>();
        graph[from].push_back((pii){to, dist});
    }
    for (register int i = 1; i <= n; i++) {
        memset(dist, 0x3f, sizeof(dist)), memset(vis, 0, sizeof(vis));
        for (vector<pii>::iterator j = graph[i].begin(); j != graph[i].end(); j++) dist[j->first] = min(dist[j->first], 1LL * j->second);
        for (register int _ = n; _; _--) {
            int p = 0;
            for (register int i = 1; i <= n; i++)
                if (!vis[i] && dist[i] < dist[p]) p = i;
            vis[p] = true;
            int t = p % n + 1;
            dist[t] = min(dist[t], dist[p] + 1);
            for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
                int t = (i->first - 1 + dist[p]) % n + 1;
                dist[t] = min(dist[t], dist[p] + i->second);
            }
        }
        dist[i] = 0;
        for (register int j = 1; j <= n; j++) write(dist[j]), putch(" \n"[j == n]);
    }
    return 0;
}