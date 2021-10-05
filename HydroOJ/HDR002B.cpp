/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://macesuted.cn/article/hdr002b/
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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

#define maxn 1000005
#define maxlgn 21

vector<vector<int>> graph;

int dep[maxn], siz[maxn], son[maxn], fa[maxn][maxlgn], top[maxn];
int a[maxn];

void dfs(int p, int pre) {
    dep[p] = dep[pre] + 1;
    siz[p] = 1;
    fa[p][0] = pre;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            dfs(*i, p);
            siz[p] += siz[*i];
            if (siz[*i] > siz[son[p]]) son[p] = *i;
        }
    return;
}
void dfs1(int p, int ftop) {
    top[p] = ftop;
    if (!son[p]) return;
    dfs1(son[p], ftop);
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != son[p] && *i != fa[p][0]) dfs1(*i, *i);
    return;
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]][0];
    }
    return dep[x] < dep[y] ? x : y;
}
inline int dist(int x, int y) { return dep[x] + dep[y] - (dep[LCA(x, y)] << 1); }
int jump(int p, int step) {
    int t = 0;
    while (step) {
        if (step & 1) p = fa[p][t];
        step >>= 1, t++;
    }
    return p;
}

int main() {
    int n = read<int>();
    graph.resize(n + 1);
    for (register int i = 1, from, to; i < n; i++) {
        from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs(1, 0), dfs1(1, 1);
    int q = read<int>();
    while (q--) {
        int k = read<int>();
        for (register int i = 1; i <= k; i++) a[i] = read<int>();
        int node1 = a[1];
        for (register int i = 2; i <= k; i++)
            if (dep[a[i]] > dep[node1]) node1 = a[i];
        int dis = 0, node2 = node1;
        for (register int i = 1; i <= k; i++) {
            register int cdis = dist(node1, a[i]);
            if (cdis > dis) dis = cdis, node2 = a[i];
        }
        if (dis & 1) {
            write(-1), putch('\n');
            continue;
        }
        int mid = jump(dep[node1] > dep[node2] ? node1 : node2, dis >>= 1);
        bool check = true;
        for (register int i = 1; i <= k; i++)
            if (dist(a[i], mid) != dis) {
                write(-1), putch('\n');
                check = false;
                break;
            }
        if (check) write(mid), putch(' '), write(dis), putch('\n');
    }
    return 0;
}