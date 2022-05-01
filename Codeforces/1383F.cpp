/**
 * @file 1383F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-21
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

#define maxk 11
#define maxn 10005

int cmin(int x, int y) { return x > y ? y : x; }

int que[maxn], flo[maxn], pre[maxn], ql, qr;

class Network {
   private:
    struct Edge {
        int from, to, cap, nxt;
    };

    Edge graph[maxn * 2];
    int head[maxn], tail;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) flo[i] = 0;
        ql = 0, qr = 0;
        que[qr++] = S, flo[S] = 0x7fffffff;
        while (ql < qr) {
            int p = que[ql++];
            for (int i = head[p]; i; i = graph[i].nxt)
                if (graph[i].cap > 0 && flo[graph[i].to] == 0) {
                    flo[graph[i].to] = cmin(flo[p], graph[i].cap), pre[graph[i].to] = i, que[qr++] = graph[i].to;
                    if (graph[i].to == T) goto out;
                }
        }
        return false;
    out:
        int p = T;
        while (p != S) graph[pre[p]].cap -= flo[T], graph[pre[p] ^ 1].cap += flo[T], p = graph[pre[p]].from;
        return true;
    }
    void addEdge_(int from, int to, int cap) {
        return graph[tail] = {from, to, cap, head[from]}, head[from] = tail++, void();
    }

   public:
    int flow;

    Network(void) { flow = 0, memset(head, 0, sizeof(head)), tail = 2; }
    void resize(int _n) { return n = _n, void(); }
    void addEdge(int from, int to, int cap) { return addEdge_(from, to, cap), addEdge_(to, from, 0); }
    void maxFlow(int _S, int _T) {
        S = _S, T = _T;
        while (bfs()) flow += flo[T];
        return;
    }
};

Network net[maxk];

int a[1 << maxk], f[1 << maxk], g[1 << maxk], lowb[1 << maxk], preb[1 << maxk];

pair<int, int> edges[maxn];

void dfs(int p, int id, int n, int k) {
    if (id == k) return g[p] = net[id - 1].flow, void();
    if (id) net[id] = net[id - 1];
    dfs(p | (1 << id), id + 1, n, k);
    net[id].addEdge(edges[id].first, edges[id].second, 25), net[id].maxFlow(1, n);
    dfs(p, id + 1, n, k);
    return;
}

void solve(void) {
    int n = read<int>(), m = read<int>(), k = read<int>(), q = read<int>();
    net[0].resize(n);
    for (int i = 0, c; i < m; i++) {
        edges[i].first = read<int>(), edges[i].second = read<int>(), c = read<int>();
        if (i >= k) net[0].addEdge(edges[i].first, edges[i].second, c);
    }
    net[0].maxFlow(1, n), dfs(0, 0, n, k);
    for (int i = 0; i < (1 << k); i++) lowb[i] = (i & -i), preb[i] = (i ^ lowb[i]);
    while (q--) {
        for (int i = 0; i < k; i++) a[1 << i] = read<int>();
        int ans = 0x7fffffff;
        f[0] = 0;
        for (int i = 0; i < (1 << k); i++) ans = cmin(ans, (f[i] = f[preb[i]] + a[lowb[i]]) + g[i]);
        write(ans), putch('\n');
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
