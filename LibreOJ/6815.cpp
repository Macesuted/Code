/**
 * @file 6815.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

class Dinic {
   private:
    struct Edge {
        int to;
        long long cap;
        int rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int> dist;
    queue<int> que;
    int n, S, T;

    bool BFS(void) {
        for (int i = 1; i <= n; i++) dist[i] = n + 1, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (i.cap && dist[i.to] > dist[p] + 1) que.push(i.to), dist[i.to] = dist[p] + 1;
        }
        return dist[T] != n + 1;
    }
    long long DFS(int p, long long rest) {
        if (p == T) return rest;
        long long use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest > use; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + 1) continue;
            if (!(c = DFS(i->to, min(rest - use, i->cap)))) dist[i->to] = -1;
            use += c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        return use;
    }

   public:
    void resize(int _n) { return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1); }
    void addEdge(int from, int to, long long cap) {
        return graph[from].push_back(Edge{to, cap, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, (int)graph[from].size() - 1});
    }
    long long maxFlow(int _S, int _T) {
        S = _S, T = _T;
        long long flow = 0;
        while (BFS()) flow += DFS(S, numeric_limits<long long>::max());
        return flow;
    }
} net;

int part(int x) { return (x & 1) ? x + 1 : x - 1; }

void solve(void) {
    int n = read<int>(), m = read<int>(), S = 3 * n + 1, T = S + 1;
    net.resize(T);
    for (int i = 1; i <= 2 * n; i++)
        net.addEdge(S, i, read<int>()), net.addEdge(i, T, read<int>()), net.addEdge(part(i), i, read<int>()),
            net.addEdge(i, 2 * n + ((i + 1) >> 1), numeric_limits<long long>::max());
    for (int i = 1; i <= m; i++) {
        int A = read<int>(), B = read<int>();
        net.addEdge(2 * n + ((A + 1) >> 1), B, read<int>()), net.addEdge(A, 2 * n + ((B + 1) >> 1), read<int>());
    }
    write(net.maxFlow(S, T)), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
