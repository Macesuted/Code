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

template <typename flowType>
class Dinic {
#define INF 0x3f3f3f3f3f3f3f3f
   private:
    struct Edge {
        int to;
        flowType cap, flow;
        int rev;
        bool real;
    };

    int S, T, n;

    vector<vector<Edge> > graph;
    vector<typename vector<Edge>::iterator> cur;
    vector<int> h;
    vector<bool> vis;
    queue<int> que;

    bool bfs(void) {
        vis.resize(n + 1, false);
        que.push(S), vis[S] = true, h[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (typename vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
                if (!vis[i->to] && i->cap > i->flow) vis[i->to] = true, h[i->to] = h[p] + 1, que.push(i->to);
        }
        bool ret = vis[T];
        vis.clear();
        return ret;
    }
    flowType dfs(int p, flowType rest) {
        if (p == T || rest == 0) return rest;
        flowType flow = 0, use;
        for (typename vector<Edge>::iterator& i = cur[p]; i != graph[p].end() && rest > 0; i++)
            if (h[i->to] == h[p] + 1 && (use = dfs(i->to, min(rest, i->cap - i->flow))) > 0)
                flow += use, rest -= use, i->flow += use, graph[i->to][i->rev].flow -= use;
        return flow;
    }

   public:
    void clear(void) {
        graph.clear(), h.clear(), cur.clear();
        return;
    }
    void resize(int _n) {
        n = _n;
        graph.resize(_n + 1), cur.resize(_n + 1), h.resize(_n + 1);
        return;
    }
    void addEdge(int from, int to, flowType cap) {
        graph[from].push_back((Edge){to, cap, 0, (int)graph[to].size(), true});
        graph[to].push_back((Edge){from, 0, 0, (int)graph[from].size() - 1, false});
        return;
    }
    flowType maxFlow(int _S, int _T) {
        S = _S, T = _T;
        flowType ans = 0;
        while (bfs()) {
            for (register int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            ans += dfs(S, INF);
        }
        return ans;
    }
#undef INF
};

Dinic<long long> dinic;

int main() {
    int n = read<int>(), m = read<int>(), S = read<int>(), T = read<int>();
    dinic.resize(n);
    for (register int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>();
        dinic.addEdge(from, to, read<long long>());
    }
    write(dinic.maxFlow(S, T)), putch('\n');
    return 0;
}