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

#define maxn 500005

typedef pair<int, int> pii;

int col[maxn], dist[maxn];

vector<vector<pii> > graph;

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1, from, to; i <= m; i++) {
        from = read<int>(), to = read<int>();
        graph[to].push_back((pii){from, read<int>()});
    }
    memset(col, -1, sizeof(col)), memset(dist, 0x3f, sizeof(dist));
    static queue<int> que;
    while (!que.empty()) que.pop();
    que.push(n), dist[n] = 0;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
            if (col[i->first] == -1)
                col[i->first] = !i->second;
            else if (col[i->first] == i->second && dist[i->first] > dist[p] + 1)
                dist[i->first] = dist[p] + 1, que.push(i->first);
    }
    if (dist[1] == 0x3f3f3f3f)
        putstr("-1\n");
    else
        write(dist[1]), putch('\n');
    for (register int i = 1; i <= n; i++) write(max(col[i], 0));
    putch('\n');
    return 0;
}