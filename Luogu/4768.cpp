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

#define maxn 200005
#define maxlgn 20

typedef pair<long long, int> pli;

struct Edge {
    int from, to, dist, height;
    inline bool operator<(const Edge& oth) const { return this->height > oth.height; }
};

vector<Edge> edges;
vector<vector<pli> > graph;
vector<vector<int> > tree;

long long dist[maxn << 1];
int fa[maxn << 1];
bool vis[maxn << 1];
int val[maxn << 1], minn[maxn << 1];
int f[maxn << 1][maxlgn], dep[maxn << 1];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void Dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    static priority_queue<pli, vector<pli>, greater<pli> > que;
    while (!que.empty()) que.pop();
    que.push((pli){dist[start] = 0, start});
    while (!que.empty()) {
        pli p = que.top();
        que.pop();
        if (vis[p.second]) continue;
        vis[p.second] = true;
        for (vector<pli>::iterator i = graph[p.second].begin(); i != graph[p.second].end(); i++)
            if (dist[i->second] > dist[p.second] + i->first)
                que.push((pli){dist[i->second] = dist[p.second] + i->first, i->second});
    }
    return;
}
void dfs(int p, int pre = 0) {
    f[p][0] = pre, dep[p] = dep[pre] + 1;
    for (register int i = 1; i < maxlgn; i++) f[p][i] = f[f[p][i - 1]][i - 1];
    for (vector<int>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
        dfs(*i, p), dist[p] = min(dist[p], dist[*i]);
    return;
}

int main() {
    int _ = read<int>();
    while (_--) {
        int n = read<int>(), m = read<int>(), tn = n;
        graph.resize(n + 1), edges.resize(m), tree.resize(n << 1);
        for (register int i = 0; i < m; i++) {
            edges[i].from = read<int>(), edges[i].to = read<int>(), edges[i].dist = read<int>(),
            edges[i].height = read<int>();
            graph[edges[i].from].push_back((pli){edges[i].dist, edges[i].to});
            graph[edges[i].to].push_back((pli){edges[i].dist, edges[i].from});
        }
        Dijkstra(1);
        sort(edges.begin(), edges.end());
        memset(val, 0, sizeof(val));
        for (register int i = 1; i < (n << 1); i++) fa[i] = i;
        for (vector<Edge>::iterator i = edges.begin(); i != edges.end(); i++)
            if (getfa(i->from) != getfa(i->to)) {
                tn++;
                int x = getfa(i->from), y = getfa(i->to);
                fa[x] = fa[y] = tn;
                tree[tn].push_back(x), tree[tn].push_back(y);
                val[tn] = i->height;
            }
        dfs(tn);
        int q = read<int>(), k = read<int>(), s = read<int>(), lastans = 0;
        while (q--) {
            int v = read<int>(), p = read<int>();
            v = (v + k * lastans - 1) % n + 1, p = (p + k * lastans) % (s + 1);
            for (register int i = maxlgn - 1; ~i; i--)
                if (val[f[v][i]] > p) v = f[v][i];
            write(lastans = dist[v]), putch('\n');
        }
        graph.clear(), edges.clear(), tree.clear();
    }
    return 0;
}