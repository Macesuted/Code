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

template <size_t maxn>
class Dinic {
#define INF 0x3f3f3f3f3f3f3f3f
#define eps 1e-10

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
                if (!vis[i->to] && i->cap - i->flow > eps) que.push(i->to), vis[i->to] = true, h[i->to] = h[p] + 1;
        }
        return vis[T];
    }
    double DFS(int p, double rest) {
        if (p == T || !rest) return rest;
        double flow = 0;
        for (typename vector<Edge>::iterator& i = cur[p]; i != graph[p].end(); i++)
            if (h[p] + 1 == h[i->to] && i->cap - i->flow > eps) {
                double use = DFS(i->to, min(i->cap - i->flow, rest));
                i->flow += use, graph[i->to][i->rev].flow -= use, flow += use, rest -= use;
                if (rest < eps) break;
            }
        return flow;
    }

   public:
    struct Edge {
        int to;
        double cap, flow;
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
    void addEdge(int from, int to, double cap) {
        graph[from].push_back((Edge){to, cap, 0, (int)graph[to].size(), true});
        graph[to].push_back((Edge){from, 0, 0, (int)graph[from].size() - 1, false});
        return;
    }
    double maxFlow(int tS, int tT) {
        S = tS, T = tT;
        double flow = 0;
        while (BFS()) {
            for (register int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            flow += DFS(S, INF);
            if (flow > INF) return flow;
        }
        return flow;
    }

#undef INF
};

#define maxn 85
#define INF 0x3f3f3f3f3f3f3f3f

#define turn(i, j) ((i - 1) * n + j)

Dinic<7005> dinic;

int c[maxn];

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n, m, p, y;
        scanf("%d%d%d%d", &n, &m, &p, &y);
        for (register int i = 1; i <= p; i++) scanf("%d", c + i);
        int S = n * (m + 1) + 1, T = S + 1;
        dinic.INIT(T);
        for (register int j = 1; j <= m; j++)
            for (register int i = 1; i <= n; i++) {
                double f = 0, t = 1, x;
                for (register int k = 1; k <= p; k++) {
                    scanf("%lf", &x);
                    f += (t *= x) * c[k];
                }
                dinic.addEdge((i - 1) * (m + 1) + j, (i - 1) * (m + 1) + j + 1, f);
                dinic.addEdge((i - 1) * (m + 1) + j + 1, (i - 1) * (m + 1) + j, INF);
            }
        for (register int i = 1; i <= n; i++)
            dinic.addEdge(S, (i - 1) * (m + 1) + 1, INF), dinic.addEdge(i * (m + 1), T, INF);
        for (register int t = 1; t <= y; t++) {
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            for (register int i = 1; i <= m; i++)
                if (1 <= i + k && i + k <= m + 1) dinic.addEdge((y - 1) * (m + 1) + i, (x - 1) * (m + 1) + i + k, INF);
        }
        double ans = dinic.maxFlow(S, T);
        (ans >= INF) ? puts("-1") : printf("%.4lf\n", ans);
    }
    return 0;
}