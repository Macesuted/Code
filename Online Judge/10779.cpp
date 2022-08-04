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

#define maxGraphSiz 55

namespace HLPP {

#define INF 0x3f3f3f3f

struct Edge {
    int to, rev;
    int cap;
    bool real;
};

typedef pair<int, int> pii;

vector<vector<Edge>> graph;

int h[maxGraphSiz];
int gap[maxGraphSiz], n, S, T;
int rest[maxGraphSiz];
bool vis[maxGraphSiz];
bool bfs(int S, int T) {
    memset(h, 0x3f, sizeof(h));
    static queue<int> q;
    while (!q.empty()) q.pop();
    q.push(T), h[T] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
            if (i->cap == 0 && h[i->to] > h[p] + 1) h[i->to] = h[p] + 1, q.push(i->to);
    }
    return h[S] != INF;
}
priority_queue<pii, vector<pii>, greater<pii>> que;
bool push(int p, int S, int T) {
    for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end() && rest[p]; i++)
        if (i->cap && h[p] == h[i->to] + 1) {
            int flow = min(i->cap, rest[p]);
            rest[p] -= flow, rest[i->to] += flow;
            i->cap -= flow, graph[i->to][i->rev].cap += flow;
            if (i->to != S && i->to != T && !vis[i->to]) que.push((pii){h[i->to], i->to}), vis[i->to] = true;
        }
    return rest[p];
}
int relabel(int p) {
    h[p] = INF;
    for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->cap && h[i->to] < h[p]) h[p] = h[i->to];
    return ++h[p];
}
void clear(void) {
    graph.clear();
    return;
}
void INIT(int tn) {
    clear();
    graph.resize((n = tn) + 1);
    return;
}
void addEdge(int from, int to, int cap) {
    graph[from].push_back((Edge){to, (int)graph[to].size(), cap, true});
    graph[to].push_back((Edge){from, (int)graph[from].size() - 1, 0, false});
    return;
}
int work(int tS, int tT) {
    for (register int i = 1; i <= n; i++)
        for (vector<Edge>::iterator j = graph[i].begin(); j != graph[i].end(); j++)
            if (j->real) j->cap += graph[j->to][j->rev].cap, graph[j->to][j->rev].cap = 0;
    if (!bfs(S = tS, T = tT)) return 0;
    h[S] = n;
    while (!que.empty()) que.pop();
    memset(gap, 0, sizeof(gap)), memset(vis, 0, sizeof(vis)), memset(rest, 0, sizeof(rest));
    for (register int i = 1; i <= n; i++)
        if (h[i] != INF) gap[h[i]]++;
    for (vector<Edge>::iterator i = graph[S].begin(); i != graph[S].end(); i++) {
        if (i->cap) {
            rest[S] -= i->cap, rest[i->to] += i->cap;
            graph[i->to][i->rev].cap += i->cap, i->cap = 0;
            if (i->to != S && i->to != T && !vis[i->to]) que.push((pii){h[i->to], i->to}), vis[i->to] = true;
        }
    }
    while (!que.empty()) {
        int p = que.top().second;
        que.pop(), vis[p] = false;
        while (push(p, S, T)) {
            if (!--gap[h[p]])
                for (register int i = 1; i <= n; i++)
                    if (i != S && i != T && h[i] > h[p] && h[i] < n + 1) h[i] = n + 1;
            gap[relabel(p)]++;
        }
    }
    return rest[T];
}

#undef INF

}  // namespace HLPP

#define maxn 55

int cnt[maxn][maxn];

int main() {
    int _ = read<int>(), ccnt = 0;
    while (_--) {
        int n = read<int>(), m = read<int>(), S = 1, T = n + m + 1;
        memset(cnt, 0, sizeof(cnt));
        for (register int i = 1; i <= n; i++) {
            int c = read<int>();
            while (c--) cnt[i][read<int>()]++;
        }
        HLPP::INIT(n + m + 1);
        for (register int j = 1; j <= m; j++)
            if (cnt[S][j]) HLPP::addEdge(S, j + n, cnt[S][j]);
        for (register int i = 2; i <= n; i++)
            for (register int j = 1; j <= m; j++)
                if (cnt[i][j] > 1)
                    HLPP::addEdge(i, j + n, cnt[i][j] - 1);
                else if (cnt[i][j] == 0)
                    HLPP::addEdge(j + n, i, 1);
        for (register int i = 1; i <= m; i++) HLPP::addEdge(i + n, T, 1);
        putstr("Case #"), write(++ccnt), putstr(": "), write(HLPP::work(S, T)), putch('\n');
    }
    return 0;
}