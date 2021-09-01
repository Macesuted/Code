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

template <size_t maxn>
class Dinic {
#define INF 0x3f3f3f3f3f3f3f3f

   private:
    int h[maxn];
    int n, S, T;
    queue<int> que;

    bool BFS(void) {
        memset(vis, 0, sizeof(vis));
        while (!que.empty()) que.pop();
        que.push(S), vis[S] = true, h[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (typename vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
                if (!vis[i->to] && i->cap > i->flow)
                    que.push(i->to), vis[i->to] = true, h[i->to] = h[p] + 1;
        }
        return vis[T];
    }
    long long DFS(int p, long long rest) {
        if (p == T || !rest) return rest;
        long long flow = 0, use = 0;
        for (typename vector<Edge>::iterator& i = cur[p]; i != graph[p].end(); i++)
            if (h[p] + 1 == h[i->to] && (use = DFS(i->to, min(rest, i->cap - i->flow))) > 0) {
                i->flow += use, graph[i->to][i->rev].flow -= use, flow += use, rest -= use;
                if (!rest) break;
            }
        return flow;
    }

   public:
    struct Edge {
        int to;
        long long cap, flow;
        int rev;
        bool real;
    };

    bool vis[maxn];
    vector<vector<Edge> > graph;
    typename vector<Edge>::iterator cur[maxn];

    void INIT(int tn) {
        n = tn;
        clear();
        graph.resize(n + 1);
        return;
    }
    void clear(void) {
        graph.clear();
        return;
    }
    void addEdge(int from, int to, long long cap) {
        graph[from].push_back((Edge){to, cap, 0, (int)graph[to].size(), true});
        graph[to].push_back((Edge){from, 0, 0, (int)graph[from].size() - 1, false});
        return;
    }
    long long maxFlow(int tS, int tT) {
        S = tS, T = tT;
        long long flow = 0;
        while (BFS()) {
            for (register int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            flow += DFS(S, INF);
        }
        return flow;
    }

#undef INF
};

#define INF 0x3f3f3f3f3f3f3f3f

const int way[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}};

Dinic<50005> dinic;

int n, m;

inline int turn(int x, int y) { return (x - 1) * m + y; }

int main() {
    n = read<int>(), m = read<int>();
    int area = n * m, S = area * 5 + 1, T = S + 1, sum = 0;
    dinic.INIT(T);
    for (register int i = 1, t; i <= n; i++)
        for (register int j = 1; j <= m; j++)
            dinic.addEdge(S, turn(i, j), t = read<int>()), sum += t;
    for (register int i = 1, t; i <= n; i++)
        for (register int j = 1; j <= m; j++)
            dinic.addEdge(turn(i, j), T, t = read<int>()), sum += t;
    for (register int i = 1, t; i < n; i++)
        for (register int j = 1; j <= m; j++) {
            dinic.addEdge(S, turn(i, j) + area * 1, t = read<int>()), sum += t;
            dinic.addEdge(turn(i, j) + area * 1, turn(i, j), INF);
            dinic.addEdge(turn(i, j) + area * 1, turn(i + 1, j), INF);
        }
    for (register int i = 1, t; i < n; i++)
        for (register int j = 1; j <= m; j++) {
            dinic.addEdge(turn(i, j) + area * 2, T, t = read<int>()), sum += t;
            dinic.addEdge(turn(i, j), turn(i, j) + area * 2, INF);
            dinic.addEdge(turn(i + 1, j), turn(i, j) + area * 2, INF);
        }
    for (register int i = 1, t; i <= n; i++)
        for (register int j = 1; j < m; j++) {
            dinic.addEdge(S, turn(i, j) + area * 3, t = read<int>()), sum += t;
            dinic.addEdge(turn(i, j) + area * 3, turn(i, j), INF);
            dinic.addEdge(turn(i, j) + area * 3, turn(i, j + 1), INF);
        }
    for (register int i = 1, t; i <= n; i++)
        for (register int j = 1; j < m; j++) {
            dinic.addEdge(turn(i, j) + area * 4, T, t = read<int>()), sum += t;
            dinic.addEdge(turn(i, j), turn(i, j) + area * 4, INF);
            dinic.addEdge(turn(i, j + 1), turn(i, j) + area * 4, INF);
        }
    write(sum - dinic.maxFlow(S, T)), putch('\n');
    return 0;
}