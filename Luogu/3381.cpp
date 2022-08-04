/**
 * @file 3381.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-21
 *
 * @copyright Copyright (c) 2021
 *
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

bool mem1;

template <typename flowType, typename costType>
class CostFlow {
#define INF 0x3f3f3f3f3f3f3f3f
   private:
    struct Edge {
        int to;
        flowType cap, flow;
        costType cost;
        int rev;
    };

    vector<vector<Edge>> graph;
    vector<typename vector<Edge>::iterator> cur;
    vector<bool> vis;
    vector<costType> dist;
    int S, T, n;
    costType minCost;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) vis[i] = false, dist[i] = INF;
        static queue<int> que;
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop(), vis[p] = false;
            for (auto& i : graph[p])
                if (i.cap > i.flow && dist[i.to] > dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) vis[i.to] = true, que.push(i.to);
                }
        }
        return dist[T] < INF;
    }
    flowType dfs(int p, flowType rest) {
        if (p == T || rest == 0) return rest;
        vis[p] = true;
        flowType flow = 0, use;
        for (auto& i = cur[p]; i != graph[p].end(); i++)
            if (dist[i->to] == dist[p] + i->cost && !vis[i->to] && (use = dfs(i->to, min(rest, i->cap - i->flow))))
                flow += use, rest -= use, minCost += use * i->cost, i->flow += use, graph[i->to][i->rev].flow -= use;
        return flow;
    }

   public:
    inline void resize(int _n) {
        return n = _n, graph.resize(n + 1), cur.resize(n + 1), vis.resize(n + 1), dist.resize(n + 1);
    }
    inline void addEdge(int from, int to, flowType cap, costType cost) {
        return graph[from].push_back(Edge{to, cap, 0, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, cap, cap, -cost, (int)graph[from].size() - 1});
    }
    tuple<flowType, costType> maxFlow(int _S, int _T) {
        S = _S, T = _T;
        flowType maxFlow = minCost = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            maxFlow += dfs(S, INF);
        }
        return make_tuple(maxFlow, minCost);
    }
#undef INF
};

CostFlow<long long, long long> flow;

void solve(void) {
    int n = read<int>(), m = read<int>(), S = read<int>(), T = read<int>();
    flow.resize(n);
    for (int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>(), cap = read<int>(), cost = read<int>();
        flow.addEdge(from, to, cap, cost);
    }
    long long maxFlow, minCost;
    tie(maxFlow, minCost) = flow.maxFlow(S, T);
    write(maxFlow), putch(' '), write(minCost), putch('\n');
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}