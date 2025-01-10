/**
 * @file 884F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-24
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

#define maxn 105

class Dinic {
   private:
    struct Edge {
        int to, cap, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    vector<bool> vis;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) cur[i] = graph[i].begin(), dist[i] = numeric_limits<int>::max(), vis[i] = false;
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            vis[p] = false;
            for (auto i : graph[p])
                if (i.cap && dist[i.to] > dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) vis[i.to] = true, que.push(i.to);
                }
        }
        return dist[T] != numeric_limits<int>::max();
    }
    int dfs(int p, int rest) {
        if (p == T || !rest) return rest;
        vis[p] = true;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && use < rest; i++) {
            cur[p] = i;
            if (vis[i->to] || !i->cap || dist[i->to] != dist[p] + i->cost) continue;
            if (!(c = dfs(i->to, min(rest - use, i->cap)))) dist[i->to] = -1;
            use += c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        vis[p] = false;
        return use;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1); }
    void addEdge(int from, int to, int cap, int cost) {
        return graph[from].push_back(Edge{to, cap, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, -cost, (int)graph[from].size() - 1});
    }
    pair<int, int> maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int flow = 0, cost = 0;
        while (bfs()) {
            int c = dfs(S, numeric_limits<int>::max());
            flow += c, cost += c * dist[T];
        }
        return {flow, cost};
    }
} net;

int a[maxn], cnt[27], b[maxn];

void solve(void) {
    int n = read<int>();
    int S = n + 26 + (n / 2) * 26 + 1, T = S + 1;
    net.resize(T);
    for (int i = 1; i <= n; i++) {
        char c = getch();
        while (!('a' <= c && c <= 'z')) c = getch();
        cnt[a[i] = c - 'a']++;
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += (b[i] = read<int>());
    for (int i = 1; i <= 26; i++) net.addEdge(S, n + i, cnt[i - 1], 0);
    for (int i = 1, cnt = n + 26; i <= 26; i++)
        for (int j = 1; j + j <= n; j++)
            net.addEdge(n + i, ++cnt, 1, 0), net.addEdge(cnt, j, 1, (a[j] + 1 != i) * b[j]),
                net.addEdge(cnt, n - j + 1, 1, (a[n - j + 1] + 1 != i) * b[n - j + 1]);
    for (int i = 1; i <= n; i++) net.addEdge(i, T, 1, 0);
    write(sum - net.maxFlow(S, T).second), putch('\n');
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
