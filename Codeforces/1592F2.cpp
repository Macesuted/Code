/**
 * @file 1592F2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-25
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

#define maxn 505

class Dinic {
   private:
    struct Edge {
        int to, cap, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = 0, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (!dist[i.to] && i.cap) dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T];
    }
    int dfs(int p, int rest) {
        if (p == T || !rest) return rest;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && use < rest; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest - use, i->cap)))) dist[i->to] = -1;
            use += c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        return use;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1); }
    void addEdge(int from, int to, int cap) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1});
    }
    int maxFlow(int _S, int _T) {
        S = _S, T = _T;
        int flow = 0;
        while (bfs()) flow += dfs(S, numeric_limits<int>::max());
        return flow;
    }
} net;

int a[maxn][maxn], b[maxn][maxn];

void solve(void) {
    int n = read<int>(), m = read<int>(), S = n + m + 1, T = S + 1;
    net.resize(T);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = getch();
            while (c != 'W' && c != 'B') c = getch();
            a[i][j] = (c == 'B');
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) b[i][j] = a[i][j] ^ a[i][j + 1] ^ a[i + 1][j] ^ a[i + 1][j + 1];
    for (int i = 1; i <= n; i++) net.addEdge(S, i, 1);
    for (int i = 1; i <= m; i++) net.addEdge(n + i, T, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m - (i == n); j++) {
            ans += b[i][j];
            if (i != n && j != m && b[i][j] && b[i][m] && b[n][j]) net.addEdge(i, n + j, 1);
        }
    int flow = net.maxFlow(S, T);
    write(ans - flow + ((flow & 1) ^ b[n][m])), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
