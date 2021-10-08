/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Solution: https://macesuted.moe/article/agc018f
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

vector<set<int> > graph;
int a[maxn], n;

void dfs(int p) {
    while (!graph[p].empty()) {
        int t = *graph[p].begin();
        graph[p].erase(t), graph[t].erase(p);
        if (p + n == t) a[p] = 1;
        if (t + n == p) a[t] = -1;
        dfs(t);
    }
    return;
}

int main() {
    n = read<int>();
    graph.resize(n * 2 + 1);
    for (register int i = 1; i <= n; i++) {
        int fa = read<int>();
        fa = (fa == -1 ? 0 : fa);
        graph[fa].insert(i), graph[i].insert(fa);
    }
    for (register int i = 1; i <= n; i++) {
        int fa = read<int>();
        fa = (fa == -1 ? 0 : fa + n);
        graph[fa].insert(i + n), graph[i + n].insert(fa);
    }
    for (register int i = 1; i <= n; i++)
        if (graph[i].size() % 2 != graph[i + n].size() % 2)
            return putstr("IMPOSSIBLE\n"), 0;
    putstr("POSSIBLE\n");
    for (register int i = 1; i <= n; i++)
        if (graph[i].size() % 2) graph[i].insert(i + n), graph[i + n].insert(i);
    dfs(1);
    for (register int i = 1; i <= n; i++) write(a[i]), putch(" \n"[i == n]);
    return 0;
}