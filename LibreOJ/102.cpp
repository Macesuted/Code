/**
 * @file 101.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

class Dinic {
   private:
    struct Edge {
        int to, cap, flow, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<int> dist;
    vector<vector<Edge>::iterator> cur;
    vector<bool> vis;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = numeric_limits<int>::max(), cur[i] = graph[i].begin(), vis[i] = false;
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            vis[p] = false;
            for (auto i : graph[p])
                if (i.cap > i.flow && dist[i.to] > dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) vis[i.to] = true, que.push(i.to);
                }
        }
        return dist[T] != numeric_limits<int>::max();
    }
    int dfs(int p, int rest) {
        if (p == T || rest == 0) return rest;
        vis[p] = true;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && use < rest; i++) {
            cur[p] = i;
            if (i->cap == i->flow || dist[i->to] != dist[p] + i->cost || vis[i->to]) continue;
            if ((c = dfs(i->to, min(rest - use, i->cap - i->flow))) == 0) dist[i->to] = 0;
            use += c, i->flow += c, graph[i->to][i->rev].flow -= c;
        }
        vis[p] = false;
        return use;
    }

   public:
    int cost;

    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1); }
    void addEdge(int from, int to, int cost, int cap) {
        return graph[from].push_back({to, cap, 0, cost, (int)graph[to].size()}),
               graph[to].push_back({from, cap, cap, -cost, (int)graph[from].size() - 1});
    }
    int maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int ans = cost = 0;
        while (bfs()) {
            int c = dfs(S, numeric_limits<int>::max());
            ans += c;
            cost += c * dist[T];
        }
        return ans;
    }
} net;

void solve(void) {
    int n = read<int>(), m = read<int>();
    net.resize(n);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), c = read<int>(), w = read<int>();
        net.addEdge(x, y, w, c);
    }
    write(net.maxFlow(1, n)), putch(' '), write(net.cost), putch('\n');
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