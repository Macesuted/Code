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

#define maxn 100005

typedef pair<int, int> pii;

struct Ask {
    int op, x, y;
};

vector<Ask> ask;
vector<vector<int> > graph;
vector<set<int> > oldgraph;
vector<pii> edges;

int tree[maxn << 2], n, m;
bool lazy[maxn << 2];
inline void pushDown(int p) {
    if (!lazy[p]) return;
    tree[p << 1] = tree[p << 1 | 1] = 0;
    lazy[p << 1] = lazy[p << 1 | 1] = true, lazy[p] = false;
    return;
}
void build(int p, int l, int r) {
    lazy[p] = false;
    if (l == r) return tree[p] = 1, void();
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
    return;
}
void update(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p] = 0, lazy[p] = true, void();
    pushDown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(p << 1, l, mid, ql, qr);
    if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
    return;
}
int getSum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    pushDown(p);
    int mid = (l + r) >> 1, answer = 0;
    if (ql <= mid) answer += getSum(p << 1, l, mid, ql, qr);
    if (qr > mid) answer += getSum(p << 1 | 1, mid + 1, r, ql, qr);
    return answer;
}

int dep[maxn], fa[maxn], siz[maxn], top[maxn], son[maxn], dfn[maxn];
bool vis[maxn];

void dfs(int p, int pre = -1) {
    vis[p] = true;
    for (set<int>::iterator i = oldgraph[p].begin(); i != oldgraph[p].end(); i++)
        if (!vis[*i])
            graph[p].push_back(*i), graph[*i].push_back(p), dfs(*i, p);
        else if (*i != pre && *i < p)
            edges.push_back((pii){*i, p});
    return;
}
void dfs1(int p, int pre) {
    dep[p] = dep[pre] + 1, fa[p] = pre, siz[p] = 1;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            dfs1(*i, p), siz[p] += siz[*i];
            if (siz[*i] > siz[son[p]]) son[p] = *i;
        }
    return;
}
int tim = 0;
void dfs2(int p, int t) {
    top[p] = t, dfn[p] = ++tim;
    if (son[p]) dfs2(son[p], t);
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != fa[p] && *i != son[p]) dfs2(*i, *i);
    return;
}

void addEdge(int from, int to) {
    while (top[from] != top[to]) {
        if (dep[top[from]] > dep[top[to]]) swap(from, to);
        update(1, 1, n, dfn[top[to]], dfn[to]);
        to = fa[top[to]];
    }
    if (dep[from] > dep[to]) swap(from, to);
    if (dfn[from] != dfn[to]) update(1, 1, n, dfn[from] + 1, dfn[to]);
    return;
}
int getAns(int from, int to) {
    int answer = 0;
    while (top[from] != top[to]) {
        if (dep[top[from]] > dep[top[to]]) swap(from, to);
        answer += getSum(1, 1, n, dfn[top[to]], dfn[to]);
        to = fa[top[to]];
    }
    if (dep[from] > dep[to]) swap(from, to);
    if (from != to) answer += getSum(1, 1, n, dfn[from] + 1, dfn[to]);
    return answer;
}

int main() {
    n = read<int>(), m = read<int>();
    oldgraph.resize(n + 1);
    for (register int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>();
        oldgraph[from].insert(to), oldgraph[to].insert(from);
    }
    while (true) {
        int op = read<int>();
        if (op == -1) break;
        int from = read<int>(), to = read<int>();
        if (op == 0) oldgraph[from].erase(to), oldgraph[to].erase(from);
        ask.push_back((Ask){op, from, to});
    }
    graph.resize(n + 1);
    dfs(1), dfs1(1, 0), dfs2(1, 1);
    build(1, 1, n);
    for (vector<pii>::iterator i = edges.begin(); i != edges.end(); i++) addEdge(i->first, i->second);
    static stack<int> answer;
    while (!answer.empty()) answer.pop();
    for (vector<Ask>::reverse_iterator i = ask.rbegin(); i != ask.rend(); i++)
        if (i->op == 0)
            addEdge(i->x, i->y);
        else
            answer.push(getAns(i->x, i->y));
    while (!answer.empty()) write(answer.top()), answer.pop(), putch('\n');
    return 0;
}