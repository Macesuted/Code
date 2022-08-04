/**
 * @file 2127.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-06
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

class Network {
   private:
    struct Edge {
        int to;
        long long cap, flow;
        int rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<long long> dist;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) cur[i] = graph[i].begin(), dist[i] = 0;
        que.push(S), dist[S] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (!dist[i.to] && i.cap > i.flow) que.push(i.to), dist[i.to] = dist[p] + 1;
        }
        return dist[T];
    }
    long long dfs(int p, long long flow) {
        if (p == T) return flow;
        long long rest = flow, ret;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (i->cap == i->flow || dist[i->to] != dist[p] + 1) continue;
            if (!(ret = dfs(i->to, min(rest, i->cap - i->flow)))) dist[i->to] = 0;
            rest -= ret, i->flow += ret, graph[i->to][i->rev].flow -= ret;
        }
        return flow - rest;
    }

   public:
    inline void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1); }
    inline void addEdge(int from, int to, long long cap) {
        return graph[from].push_back(Edge{to, cap, 0, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, cap, cap, (int)graph[from].size() - 1});
    }
    inline long long maxFlow(int _S, int _T) {
        S = _S, T = _T;
        long long ans = 0;
        while (bfs()) ans += dfs(S, numeric_limits<long long>::max());
        return ans;
    }
} net;

void solve(void) {
    int n = read<int>(), m = read<int>(), a = n * m, S = 5 * a + 1, T = S + 1;
    net.resize(T);
#define turn(x, y) (((x)-1) * m + (y))
#define INF (numeric_limits<long long>::max())
    long long ans = 0;
    for (int i = 1, d; i <= n; i++)
        for (int j = 1; j <= m; j++) net.addEdge(S, turn(i, j), d = read<long long>()), ans += d;
    for (int i = 1, d; i <= n; i++)
        for (int j = 1; j <= m; j++) net.addEdge(turn(i, j), T, d = read<long long>()), ans += d;
    for (int i = 1, d; i < n; i++)
        for (int j = 1; j <= m; j++) {
            int x = turn(i, j) + a;
            net.addEdge(S, x, d = read<long long>()), net.addEdge(x, turn(i, j), INF),
                net.addEdge(x, turn(i + 1, j), INF);
            ans += d;
        }
    for (int i = 1, d; i < n; i++)
        for (int j = 1; j <= m; j++) {
            int x = turn(i, j) + 2 * a;
            net.addEdge(turn(i, j), x, INF), net.addEdge(turn(i + 1, j), x, INF),
                net.addEdge(x, T, d = read<long long>());
            ans += d;
        }
    for (int i = 1, d; i <= n; i++)
        for (int j = 1; j < m; j++) {
            int x = turn(i, j) + 3 * a;
            net.addEdge(S, x, d = read<long long>()), net.addEdge(x, turn(i, j), INF),
                net.addEdge(x, turn(i, j + 1), INF);
            ans += d;
        }
    for (int i = 1, d; i <= n; i++)
        for (int j = 1; j < m; j++) {
            int x = turn(i, j) + 4 * a;
            net.addEdge(turn(i, j), x, INF), net.addEdge(turn(i, j + 1), x, INF),
                net.addEdge(x, T, d = read<long long>());
            ans += d;
        }
    write(ans - net.maxFlow(S, T)), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}