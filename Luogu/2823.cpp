/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief My Solution: https://www.macesuted.cn/article/lg2823/
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
        for (register int i = 1; i <= n; i++)
            for (typename vector<Edge>::iterator j = graph[i].begin(); j != graph[i].end(); j++)
                j->flow = 0;
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
#define maxn 75

Dinic<20005> dinic;

int f[maxn][maxn], g[maxn][maxn];

int main() {
    int _ = read<int>();
    while (_--) {
        int P = read<int>(), D = read<int>(), H = read<int>(), N = read<int>();
        int S = P + 2 * P * D + D * H + 1, T = S + 1;
        dinic.INIT(T);
        for (register int i = 1; i <= P; i++) dinic.addEdge(S, i, read<int>());
        int tl = read<int>(), tr = read<int>();
        long long tot = 0;
        for (register int i = 1; i <= D; i++)
            for (register int j = 1, t; j <= H; j++)
                dinic.addEdge(P + 2 * P * D + (i - 1) * H + j, T, t = read<int>()), tot += t;
        for (register int k = 1; k <= P; k++)
            for (register int i = 1; i <= D; i++) {
                f[k][i] = g[k][i] = 0;
                for (register int j = 1; j <= H; j++)
                    if (read<int>()) {
                        if (tl <= j && j <= tr)
                            dinic.addEdge(P + P * D + (k - 1) * D + i, P + 2 * P * D + (i - 1) * H + j, 1), g[k][i]++;
                        else
                            dinic.addEdge(P + (k - 1) * D + i, P + 2 * P * D + (i - 1) * H + j, 1);
                    } else
                        f[k][i]++;
            }
        bool flag = false;
        for (register int i = 1; i <= P; i++)
            for (register int j = 1; j <= D; j++) {
                dinic.addEdge(i, P + (i - 1) * D + j, N - f[i][j]);
                if (N - f[i][j] < 0) flag = true;
            }
        for (register int i = 1; i <= P; i++)
            for (register int j = 1; j <= D; j++) {
                dinic.addEdge(P + (i - 1) * D + j, P + P * D + (i - 1) * D + j, g[i][j] - 1);
                if (g[i][j] - 1 < 0) flag = true;
            }
        putstr((!flag && dinic.maxFlow(S, T) == tot) ? "Yes" : "No"), putch('\n');
    }
    return 0;
}