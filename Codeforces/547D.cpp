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

#define maxn 200005

typedef pair<int, int> pii;

bool ans[maxn];

vector<set<pii> > graph;

void dfs(int p, bool col) {
    while (!graph[p].empty()) {
        pii to = *graph[p].begin();
        graph[p].erase(graph[p].begin());
        graph[to.first].erase((pii){p, to.second});
        ans[to.second] = col;
        dfs(to.first, !col);
    }
    return;
}

int main() {
    int n = read<int>();
    graph.resize(maxn << 1);
    for (register int i = 1; i <= n; i++) {
        int from = read<int>(), to = read<int>();
        graph[from].insert((pii){to + maxn, i}), graph[to + maxn].insert((pii){from, i});
    }
    for (register int i = 1; i < (maxn << 1); i++)
        if (graph[i].size() & 1) graph[0].insert((pii){i, 0}), graph[i].insert((pii){0, 0});
    for (register int i = 0; i < (maxn << 1); i++)
        if (!graph[i].empty()) dfs(i, 0);
    for (register int i = 1; i <= n; i++) putch(ans[i] ? 'r' : 'b');
    putch('\n');
    return 0;
}