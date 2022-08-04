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

#define maxn 300005

typedef pair<int, int> pii;

vector<vector<int> > graph;
int fa[maxn], dis[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

pii dfs(int p, int pre) {
    pii answer = (pii){0, p};
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            pii ret = dfs(*i, p);
            ret.first++;
            if (ret.first > answer.first) answer = ret;
        }
    return answer;
}

int main() {
    int n = read<int>(), m = read<int>(), q = read<int>();
    for (register int i = 1; i <= n; i++) fa[i] = i;
    graph.resize(n + 1);
    for (register int i = 1, from, to; i <= m; i++) {
        from = read<int>(), to = read<int>();
        if (getfa(from) == getfa(to)) continue;
        graph[from].push_back(to), graph[to].push_back(from);
        fa[getfa(to)] = getfa(from);
    }
    for (register int i = 1; i <= n; i++)
        if (fa[i] == i) dis[i] = dfs(dfs(i, -1).second, -1).first;
    while (q--)
        if (read<int>() == 1)
            write(dis[getfa(read<int>())]), putch('\n');
        else {
            int x = getfa(read<int>()), y = getfa(read<int>());
            if (getfa(x) == getfa(y)) continue;
            fa[y] = x;
            dis[x] = max(max(dis[x], dis[y]), (dis[x] + 1) / 2 + (dis[y] + 1) / 2 + 1);
        }
    return 0;
}