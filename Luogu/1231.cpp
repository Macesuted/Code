/**
 * @author Macesuted (macesuted@qq.com)
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
    struct Edge {
        int to;
        long long cap, flow;
        int rev;
        bool real;
    };

    int h[maxn];
    bool vis[maxn];
    int n, S, T;
    typename vector<Edge>::iterator cur[maxn];
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
    vector<vector<Edge> > graph;

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

Dinic<40005> dinic;

int main() {
    int n2 = read<int>(), n1 = read<int>(), n3 = read<int>(), S = n1 + n2 * 2 + n3 + 1, T = n1 + n2 * 2 + n3 + 2;
    dinic.INIT(T);
    for (register int i = 1; i <= n1; i++) dinic.addEdge(S, i, 1);
    int m1 = read<int>();
    for (register int i = 1; i <= m1; i++) {
        int x = read<int>(), y = read<int>();
        dinic.addEdge(y, n1 + x, 1);
    }
    for (register int i = 1; i <= n2; i++) dinic.addEdge(n1 + i, n1 + n2 + i, 1);
    int m2 = read<int>();
    for (register int i = 1; i <= m2; i++) {
        int x = read<int>(), y = read<int>();
        dinic.addEdge(n1 + n2 + x, n1 + n2 * 2 + y, 1);
    }
    for (register int i = 1; i <= n3; i++) dinic.addEdge(n1 + n2 * 2 + i, T, 1);
    write(dinic.maxFlow(S, T)), putch('\n');
    return 0;
}