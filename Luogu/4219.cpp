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

#define maxn 100005

struct Ask {
    int op, x, y;
};

Ask ask[maxn];

vector<vector<int> > graph;

int son[maxn], top[maxn], siz[maxn], dep[maxn], fa[maxn], dfn[maxn];

void dfs1(int p, int pre = 0) {
    cerr << p << ' ' << pre << "!" << endl;
    fa[p] = pre, dep[p] = dep[pre] + 1, siz[p] = 1;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            dfs1(*i, p);
            if (!son[p] || siz[*i] > siz[son[p]]) son[p] = *i;
            siz[p] += siz[*i];
        }
    return;
}
int tim = 0;
void dfs2(int p, int t) {
    dfn[p] = ++tim;
    top[p] = t;
    if (son[p]) dfs2(son[p], t);
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != fa[p] && *i != son[p]) dfs2(*i, *i);
    return;
}

int f[maxn];
int getfa(int p) { return f[p] == p ? p : f[p] = getfa(f[p]); }

long long tree[maxn];
void add(int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
    return;
}
long long sum(int p) {
    long long sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

int main() {
    int n = read<int>(), q = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= q; i++) ask[i].op = (getstr()[0] == 'Q'), ask[i].x = read<int>(), ask[i].y = read<int>();
    for (register int i = 0; i <= n; i++) f[i] = i;
    for (register int i = 1; i <= q; i++)
        if (!ask[i].op) {
            graph[ask[i].x].push_back(ask[i].y), graph[ask[i].y].push_back(ask[i].x);
            f[getfa(ask[i].x)] = getfa(ask[i].y);
        }
    for (register int i = 1; i <= n; i++)
        if (getfa(i) != getfa(0)) graph[0].push_back(i), graph[i].push_back(0), f[getfa(i)] = getfa(0);
    dfs1(0), dfs2(0, 0);
    for (register int i = 1; i <= n; i++) f[i] = i;
    add(1, 1);
    // for (register int i = 1; i <= n; i++) printf("%d ", dfn[i]);
    // puts("");
    for (register int i = 1; i <= q; i++) {
        cerr << i << endl;
        if (ask[i].op) {
            if (dep[ask[i].x] < dep[ask[i].y]) swap(ask[i].x, ask[i].y);
            write(1LL * sum(dfn[ask[i].x]) * (sum(dfn[getfa(ask[i].x)]) - sum(dfn[ask[i].x]))), putch('\n');
        } else {
            if (dep[ask[i].x] < dep[ask[i].y]) swap(ask[i].x, ask[i].y);
            int p = ask[i].y, to = getfa(ask[i].y), delta = sum(dfn[ask[i].x]);
            while (top[p] != top[to]) add(dfn[top[p]], delta), add(dfn[p] + 1, -delta), p = fa[top[p]];
            add(dfn[to], delta), add(dfn[p] + 1, -delta);
            f[ask[i].x] = to;
        }
        // for (register int i = 1; i <= n + 1; i++) printf("%lld ", sum(i));
        // puts("");
    }
    return 0;
}