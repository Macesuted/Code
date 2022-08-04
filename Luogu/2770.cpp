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

template <typename flowType, typename costType>
class ZkwCostFlow {
#define INF 0x3f3f3f3f3f3f3f3f
   private:
    int S, T, n;
    vector<costType> h;
    vector<bool> vis;
    deque<int> que;

    bool bfs(void) {
        for (register int i = 1; i <= n; i++) vis[i] = false, h[i] = INF;
        que.push_back(T), vis[T] = true, h[T] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop_front();
            vis[p] = false;
            for (typename vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
                if (graph[i->to][i->rev].cap > graph[i->to][i->rev].flow && h[i->to] > h[p] - i->cost) {
                    h[i->to] = h[p] - i->cost;
                    if (!vis[i->to]) {
                        vis[i->to] = true;
                        (!que.empty() && h[que.front()] > h[i->to]) ? que.push_front(i->to) : que.push_back(i->to);
                    }
                }
        }
        return h[S] < INF;
    }
    flowType dfs(int p, flowType rest) {
        if (p == T || rest == 0) return rest;
        vis[p] = true;
        flowType flow = 0, use;
        for (typename vector<Edge>::iterator& i = cur[p]; i != graph[p].end() && rest > 0; i++)
            if (h[i->to] == h[p] - i->cost && !vis[i->to] && (use = dfs(i->to, min(rest, i->cap - i->flow))))
                flow += use, rest -= use, minCost += use * i->cost, i->flow += use, graph[i->to][i->rev].flow -= use;
        return flow;
    }

   public:
    struct Edge {
        int to;
        flowType cap, flow;
        costType cost;
        int rev;
        bool real;
    };
    vector<vector<Edge> > graph;
    vector<typename vector<Edge>::iterator> cur;

    costType minCost;

    void clear(void) {
        graph.clear(), cur.clear(), vis.clear(), h.clear();
        return;
    }
    void resize(int _n) {
        n = _n;
        clear();
        graph.resize(n + 1), cur.resize(n + 1), vis.resize(n + 1), h.resize(n + 1);
        return;
    }
    void addEdge(int from, int to, flowType cap, costType cost) {
        graph[from].push_back((Edge){to, cap, 0, cost, (int)graph[to].size(), true});
        graph[to].push_back((Edge){from, 0, 0, -cost, (int)graph[from].size() - 1, false});
        return;
    }
    flowType maxFlow(int _S, int _T) {
        S = _S, T = _T;
        flowType maxFlow = minCost = 0;
        while (bfs()) {
            for (register int i = 1; i <= n; i++) cur[i] = graph[i].begin();
            maxFlow += dfs(S, INF);
        }
        return maxFlow;
    }
#undef INF
};

#define maxn 105

ZkwCostFlow<long long, long long> flow;
map<string, int> record;
string str[maxn];
vector<int> answer[3];
int n, S, T;

void dfs(int p, int id) {
    if (p == T) return;
    answer[id].push_back(p);
    for (vector<ZkwCostFlow<long long, long long>::Edge>::iterator i = flow.graph[p + n].begin();
         i != flow.graph[p + n].end(); i++)
        if (i->real && i->flow) dfs(i->to, id);
    return;
}

int main() {
    n = read<int>(), S = 2 * n + 1, T = S + 1;
    int m = read<int>();
    flow.resize(T);
    for (register int i = 1; i <= n; i++) record[str[i] = getstr()] = i;
    flow.addEdge(S, 1, 2, 0), flow.addEdge(n + n, T, 2, 0);
    for (register int i = 1; i <= n; i++) flow.addEdge(i, n + i, 1 + (i == 1 || i == n), -1);
    for (register int i = 1; i <= m; i++) {
        int x = record[getstr()], y = record[getstr()];
        if (x > y) swap(x, y);
        flow.addEdge(x + n, y, 1, 0);
    }
    int ret = flow.maxFlow(S, T), ans = -flow.minCost;
    if (ret == 0) return putstr("No Solution!\n"), 0;
    int cnt = 0;
    for (vector<ZkwCostFlow<long long, long long>::Edge>::iterator i = flow.graph[1 + n].begin();
         i != flow.graph[1 + n].end(); i++)
        if (i->real && i->flow) dfs(i->to, ++cnt);
    if (ret == 1) {
        write(ans), putch('\n');
        putstr(str[1]), putch('\n');
        for (vector<int>::iterator i = answer[1].begin(); i != answer[1].end(); i++) putstr(str[*i]), putch('\n');
        putstr(str[1]), putch('\n');
        return 0;
    }
    write(ans - 2), putch('\n');
    putstr(str[1]), putch('\n');
    for (vector<int>::iterator i = answer[1].begin(); i != answer[1].end(); i++) putstr(str[*i]), putch('\n');
    for (vector<int>::reverse_iterator i = answer[2].rbegin() + 1; i != answer[2].rend(); i++)
        putstr(str[*i]), putch('\n');
    putstr(str[1]), putch('\n');
    return 0;
}