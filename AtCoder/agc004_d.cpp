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

#define maxn 100005

vector<vector<int> > graph;

int fa[maxn], k, answer = 0;

int dfs1(int p, int deep) {
    int maxDep = deep;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) maxDep = max(maxDep, dfs1(*i, deep + 1));
    if (maxDep - deep == k - 1 && fa[p] != 1) return answer++, 0;
    return maxDep;
}

int main() {
    int n = read<int>();
    k = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= n; i++) fa[i] = read<int>();
    if (fa[1] != 1) answer++, fa[1] = 1;
    for (register int i = 2; i <= n; i++) graph[fa[i]].push_back(i);
    dfs1(1, 0);
    write(answer), putch('\n');
    return 0;
}