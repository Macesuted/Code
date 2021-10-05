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

template <size_t maxn>
class ZkwCostFlow {
#define INF 0x3f3f3f3f3f3f3f3f

   private:
    long long dist[maxn];
    bool vis[maxn];
    int n, S, T;
    deque<int> que;

    bool SPFA(void) {
        memset(vis, 0, sizeof(vis));
        for (register int i = 1; i <= n; i++) dist[i] = INF;
        que.clear(), que.push_back(T), dist[T] = 0, vis[T] = true;
        while (!que.empty()) {
            int p = que.front();
            que.pop_front();
            for (typename vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
                if (graph[i->to][i->rev].cap > graph[i->to][i->rev].flow && dist[i->to] > dist[p] - i->cost) {
                    dist[i->to] = dist[p] - i->cost;
                    if (!vis[i->to]) {
                        vis[i->to] = true;
                        (!que.empty() && dist[i->to] < dist[que.front()])
                            ? que.push_front(i->to)
                            : que.push_back(i->to);
                    }
                }
            vis[p] = false;
        }
        return dist[S] < INF;
    }
    long long DFS(int p, long long rest) {
        vis[p] = true;
        if (p == T) return rest;
        long long flow = 0;
        for (typename vector<Edge>::iterator& i = cur[p]; i != graph[p].end(); i++)
            if (!vis[i->to] && i->cap > i->flow && dist[p] - i->cost == dist[i->to]) {
                long long ret = DFS(i->to, min(i->cap - i->flow, rest));
                if (!ret) continue;
                answer += ret * i->cost, i->flow += ret, graph[i->to][i->rev].flow -= ret, flow += ret, rest -= ret;
                if (!rest) break;
            }
        return flow;
    }

   public:
    struct Edge {
        int to;
        long long cap, flow, cost;
        int rev;
        bool real;
    };

    vector<vector<Edge> > graph;
    typename vector<Edge>::iterator cur[maxn];
    long long answer;

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
    void addEdge(int from, int to, long long cap, long long cost) {
        graph[from].push_back((Edge){to, cap, 0, cost, (int)graph[to].size(), true});
        graph[to].push_back((Edge){from, 0, 0, -cost, (int)graph[from].size() - 1, false});
        return;
    }
    long long minCostFlow(int tS, int tT) {
        S = tS, T = tT, answer = 0;
        long long flow = 0;
        while (SPFA()) {
            for (register int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            flow += DFS(S, INF);
        }
        return flow;
    }

#undef INF
};

#define INF 0x3f3f3f3f3f3f3f3f
#define turn(i, j) ((i - 1) * n + j)
#define maxn 105

ZkwCostFlow<200005> web;

int a[maxn][maxn];

int main() {
    int n = read<int>(), K = read<int>(), A = read<int>(), B = read<int>(), C = read<int>(),
        S = n * n * (K + 1) + 1, T = S + 1;
    web.INIT(T);
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            a[i][j] = read<int>();
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++) {
            if (a[i][j])
                for (register int k = 0; k < K; k++) web.addEdge(k * n * n + turn(i, j), K * n * n + turn(i, j), 1, A);
            for (register int k = K; k; k--) {
                if (a[i][j] && k < K) break;
                if (i != n) web.addEdge(k * n * n + turn(i, j), (k - 1) * n * n + turn(i + 1, j), 1, 0);
                if (j != n) web.addEdge(k * n * n + turn(i, j), (k - 1) * n * n + turn(i, j + 1), 1, 0);
                if (i != 1) web.addEdge(k * n * n + turn(i, j), (k - 1) * n * n + turn(i - 1, j), 1, B);
                if (j != 1) web.addEdge(k * n * n + turn(i, j), (k - 1) * n * n + turn(i, j - 1), 1, B);
            }
            web.addEdge(turn(i, j), K * n * n + turn(i, j), 1, A + C);
        }
    web.addEdge(S, K * n * n + turn(1, 1), 1, 0);
    for (register int i = 0; i <= K; i++) web.addEdge(i * n * n + turn(n, n), T, 1, 0);
    web.minCostFlow(S, T);
    write(web.answer), putch('\n');
    return 0;
}