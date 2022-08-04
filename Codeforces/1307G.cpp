/**
 * @file 1307G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/cf1307g
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

#define maxn 55
#define maxm 2505

typedef pair<long long, int> pli;

class Dinic {
   private:
    struct Edge {
        int to, cap, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<long long> dist;
    vector<int> pre;
    vector<bool> vis;
    queue<int> que;
    int n;

   public:
    void resize(int _n) {
        return n = _n, graph.resize(n + 1), vis.resize(n + 1), dist.resize(n + 1), pre.resize(n + 1);
    }
    void addEdge(int from, int to, int cap, int cost) {
        return graph[from].push_back(Edge{to, cap, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, -cost, (int)graph[from].size() - 1});
    }
    long long maxFlow(int S, int T) {
        for (int i = 1; i <= n; i++) dist[i] = numeric_limits<int>::max(), vis[i] = false;
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            vis[p] = false;
            for (auto i : graph[p])
                if (i.cap && dist[i.to] > dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost, pre[i.to] = i.rev;
                    if (!vis[i.to]) vis[i.to] = true, que.push(i.to);
                }
        }
        if (dist[T] == numeric_limits<int>::max()) return 0;
        int p = T;
        while (p != S) {
            int x = graph[p][pre[p]].to;
            graph[x][graph[p][pre[p]].rev].cap--, graph[p][pre[p]].cap++;
            p = x;
        }
        return dist[T];
    }
} net;

long long cost[maxm], lim[maxm];

void solve(void) {
    int n = read<int>(), m = read<int>();
    net.resize(n);
    for (int i = 1, x, y, c; i <= m; i++) {
        x = read<int>(), y = read<int>(), c = read<int>();
        net.addEdge(x, y, 1, c);
    }
    int flow = 0;
    long long ret = net.maxFlow(1, n);
    while (ret) cost[flow + 1] = cost[flow] + ret, flow++, ret = net.maxFlow(1, n);
    for (int i = 1; i < flow; i++) lim[i] = cost[i + 1] * i - cost[i] * (i + 1);
    cout << setprecision(8);
    int q = read<int>();
    while (q--) {
        int x = read<int>(), p = lower_bound(lim + 1, lim + flow, x) - lim;
        cout << 1. * (cost[p] + x) / p << endl;
    }
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
