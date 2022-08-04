/**
 * @file 2125.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>
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
        long long flow;
        int rev;
    };

    vector<vector<Edge> > graph;
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
            for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
                if (!dist[i->to] && i->flow) dist[i->to] = dist[p] + 1, que.push(i->to);
        }
        return dist[T];
    }
    long long dfs(int p, long long rest) {
        if (p == T) return rest;
        long long flow = rest, c;
        for (vector<Edge>::iterator i = cur[p]; i != graph[p].end() && flow; i++) {
            cur[p] = i;
            if (!i->flow || dist[i->to] != dist[p] + 1) continue;
            if (!(c = dfs(i->to, min(flow, i->flow)))) dist[i->to] = 0;
            i->flow -= c, graph[i->to][i->rev].flow += c, flow -= c;
        }
        return rest - flow;
    }

   public:
    vector<bool> col;

    inline void resize(int _n) {
        return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1), col.resize(n + 1);
    }
    inline void addEdge(int from, int to, long long cap) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1});
    }
    long long maxFlow(int _S, int _T) {
        S = _S, T = _T;
        long long ans = 0;
        while (bfs()) ans += dfs(S, 0x3f3f3f3f);
        return ans;
    }
    void paint(int p) {
        col[p] = true;
        for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
            if (!col[i->to] && i->flow) paint(i->to);
        return;
    }
} net;

queue<int> answer;
void solve(void) {
    int n = read<int>(), m = read<int>(), S = 2 * n + 1, T = S + 1;
    net.resize(T);
    for (int i = 1; i <= n; i++) net.addEdge(i + n, T, read<int>());
    for (int i = 1; i <= n; i++) net.addEdge(S, i, read<int>());
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        net.addEdge(x, y + n, 0x3f3f3f3f);
    }
    write(net.maxFlow(S, T)), putch('\n');
    net.paint(S);
    for (int i = 1; i <= n; i++)
        if (!net.col[i]) answer.push(-i);
    for (int i = 1; i <= n; i++)
        if (net.col[i + n]) answer.push(+i);
    write((int)answer.size()), putch('\n');
    while (!answer.empty())
        write(abs(answer.front())), putch(' '), putch("-+"[answer.front() > 0]), putch('\n'), answer.pop();
    return;
}

bool mem2;

int main() {
    int _ = 1;
    while (_--) solve();
    return 0;
}