/**
 * @file 101.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-02
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

template <typename flowType>
class Network {
   private:
    struct Edge {
        int to;
        flowType cap, flow;
        int rev;
    };

    vector<vector<Edge>> graph;
    vector<int> dist;
    vector<typename vector<Edge>::iterator> cur;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = 0, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (dist[i.to] == 0 && i.flow < i.cap)
                    dist[i.to] = dist[p] + 1, que.push(i.to);
        }
        return dist[T];
    }
    flowType dfs(int p, flowType flow) {
        if (p == T || flow == 0) return flow;
        flowType rest = flow, c;
        for (auto i = cur[p]; i != graph[p].end() && rest; i++) {
            cur[p] = i;
            if (i->cap == i->flow || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(rest, i->cap - i->flow)))) dist[i->to] = 0;
            i->flow += c, graph[i->to][i->rev].flow -= c, rest -= c;
        }
        return flow - rest;
    }

   public:
    inline void resize(int _n) { return n = _n, graph.resize(n + 1), dist.resize(n + 1), cur.resize(n + 1), void(); }
    inline void addEdge(int from, int to, flowType cap) {
        return graph[from].push_back(Edge{to, cap, (flowType)0, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, cap, cap, (int)graph[from].size() - 1});
    }
    inline flowType maxFlow(int _S, int _T) {
        S = _S, T = _T;
        flowType answer = 0;
        while (bfs()) answer += dfs(S, numeric_limits<flowType>::max());
        return answer;
    }
};

Network<long long> net;

void solve(void) {
    int n = read<int>(), m = read<int>(), S = read<int>(), T = read<int>();
    net.resize(n);
    for (int i = 1; i <= m; i++) {
        int from = read<int>(), to = read<int>(), dist = read<int>();
        net.addEdge(from, to, dist);
    }
    write(net.maxFlow(S, T)), putch('\n');
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}
