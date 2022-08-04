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

#define maxn 100005

vector<vector<int> > graph;

int f[maxn], g[maxn];
int S, T;
bool odd = false;

void dfs1(int p, int pre = -1, int col = -1) {
    f[p] = col;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
        if (*i == pre) continue;
        if (f[*i] != 0) {
            if (f[*i] == f[p]) odd = true;
            S = p, T = *i;
            continue;
        }
        dfs1(*i, p, -col);
    }
    return;
}
void dfs2(int p, int pre = -1) {
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre && !((p == S && *i == T) || (p == T && *i == S))) dfs2(*i, p), f[p] += f[*i], g[p] += g[*i];
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1, from, to; i <= m; i++)
        from = read<int>(), to = read<int>(), graph[from].push_back(to), graph[to].push_back(from);
    dfs1(1);
    int sum = 0;
    for (register int i = 1; i <= n; i++) sum += f[i];
    if ((!odd && sum != 0) || (odd && (abs(sum) & 1))) return putstr("-1\n"), 0;
    if (odd) f[S] -= sum / 2, f[T] -= sum / 2;
    if (n == m && !odd) g[S] = 1, g[T] = -1;
    dfs2(1);
    long long answer = abs(sum / 2);
    for (register int i = 1; i <= n; i++)
        if (g[i] == 0) answer += abs(f[i]);
    if (n != m || odd) return write(answer), putch('\n'), 0;
    static vector<int> nodes;
    nodes.clear();
    nodes.push_back(0);
    for (register int i = 1; i <= n; i++)
        if (g[i] != 0) nodes.push_back(f[i] * g[i]);
    sort(nodes.begin(), nodes.end());
    int delta = nodes[(nodes.size() - 1) >> 1];
    for (vector<int>::iterator i = nodes.begin(); i != nodes.end(); i++) answer += abs(*i - delta);
    write(answer), putch('\n');
    return 0;
}