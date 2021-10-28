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

#define maxn 200005

struct Ask {
    int from, to;
    long long dist;
    int id;
    inline bool operator<(const Ask& oth) const { return this->dist < oth.dist; }
};

struct Edge {
    int from, to;
    long long dist;
    inline bool operator<(const Edge& oth) const { return this->dist < oth.dist; }
};

typedef pair<long long, int> pli;

long long dist[maxn];
int from[maxn], fa[maxn];
bool vis[maxn], answer[maxn];
Ask asks[maxn];

vector<int> nodes;
vector<vector<pli> > graph;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

int main() {
    int n = read<int>(), s = read<int>(), m = read<int>();
    for (register int i = 1; i <= s; i++) nodes.push_back(read<int>());
    graph.resize(n + 1);
    for (register int i = 1, from, to, dist; i <= m; i++) {
        from = read<int>(), to = read<int>(), dist = read<int>();
        graph[from].push_back((pli){dist, to});
        graph[to].push_back((pli){dist, from});
    }
    static priority_queue<pli, vector<pli>, greater<pli> > que;
    while (!que.empty()) que.pop();
    memset(dist, 0x3f, sizeof(dist)), memset(vis, 0, sizeof(vis));
    for (vector<int>::iterator i = nodes.begin(); i != nodes.end(); i++) from[*i] = *i, que.push((pli){dist[*i] = 0, *i});
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (vector<pli>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
            if (dist[i->second] > dist[p] + i->first)
                from[i->second] = from[p], que.push((pli){dist[i->second] = dist[p] + i->first, i->second});
    }
    static vector<Edge> edges;
    edges.clear();
    for (register int i = 1; i <= n; i++)
        for (vector<pli>::iterator j = graph[i].begin(); j != graph[i].end(); j++)
            if (i < j->second) edges.push_back((Edge){from[i], from[j->second], j->first + dist[i] + dist[j->second]});
    int q = read<int>();
    for (register int i = 1; i <= q; i++)
        asks[i].from = read<int>(), asks[i].to = read<int>(), asks[i].dist = read<int>(), asks[i].id = i;
    sort(edges.begin(), edges.end()), sort(asks + 1, asks + q + 1);
    for (register int i = 1; i <= n; i++) fa[i] = i;
    vector<Edge>::iterator j = edges.begin();
    for (register int i = 1; i <= q; i++) {
        while (j != edges.end() && j->dist <= asks[i].dist) {
            if (getfa(j->from) != getfa(j->to)) fa[getfa(j->from)] = getfa(j->to);
            j++;
        }
        answer[asks[i].id] = (getfa(asks[i].from) == getfa(asks[i].to));
    }
    for (register int i = 1; i <= q; i++) putstr(answer[i] ? "TAK" : "NIE"), putch('\n');
    return 0;
}