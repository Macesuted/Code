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

#define maxn 105
#define INF 0x3f3f3f3f

namespace HLPP {

struct Edge {
    int to, rev;
    long long cap;
};

vector<vector<Edge> > graph;

int h[maxn];
int gap[maxn], n, S, T;
long long rest[maxn];
bool vis[maxn];
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
struct cmp {
    inline bool operator()(int x, int y) const { return h[x] < h[y]; }
};
priority_queue<int, vector<int>, cmp> que;
bool push(int p, int S, int T) {
    for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end() && rest[p]; i++)
        if (i->cap && h[p] == h[i->to] + 1) {
            long long flow = min(i->cap, rest[p]);
            rest[p] -= flow, rest[i->to] += flow;
            i->cap -= flow, graph[i->to][i->rev].cap += flow;
            if (i->to != S && i->to != T && !vis[i->to]) que.push(i->to), vis[i->to] = true;
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
void addEdge(int from, int to, long long cap) {
    graph[from].push_back((Edge){to, (int)graph[to].size(), cap});
    graph[to].push_back((Edge){from, (int)graph[from].size() - 1, 0});
    return;
}
long long work(int tS, int tT) {
    if (!bfs(S = tS, T = tT)) return 0;
    h[S] = n;
    while (!que.empty()) que.pop();
    memset(gap, 0, sizeof(gap)), memset(vis, 0, sizeof(vis)), memset(rest, 0, sizeof(rest));
    for (register int i = 1; i <= n; i++)
        if (h[i] != INF) gap[h[i]]++;
    for (vector<Edge>::iterator i = graph[S].begin(); i != graph[S].end(); i++)
        if (i->cap) {
            rest[S] -= i->cap, rest[i->to] += i->cap;
            graph[i->to][i->rev].cap += i->cap, i->cap = 0;
            if (i->to != S && i->to != T && !vis[i->to]) que.push(i->to), vis[i->to] = true;
        }
    while (!que.empty()) {
        int p = que.top();
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

}  // namespace HLPP

vector<vector<int> > record, answer;
char a[55][55];

int main() {
    ios::sync_with_stdio(false);
    int n, a1, a2, an, b1, b2, bn;
    while (cin >> n >> a1 >> a2 >> an >> b1 >> b2 >> bn) {
        a1++, a2++, b1++, b2++;
        int S = n + 1, T = n + 2;
        HLPP::INIT(n + 2);
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= n; j++) {
                cin >> a[i][j];
                if (a[i][j] == 'O') HLPP::addEdge(i, j, 2);
                if (a[i][j] == 'N') HLPP::addEdge(i, j, INF);
            }
        bool check = true;
        HLPP::addEdge(S, a1, 2 * an), HLPP::addEdge(a2, T, 2 * an);
        HLPP::addEdge(S, b1, 2 * bn), HLPP::addEdge(b2, T, 2 * bn);
        if (HLPP::work(S, T) != 2 * (an + bn)) check = false;
        HLPP::INIT(n + 2);
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= n; j++) {
                if (a[i][j] == 'O') HLPP::addEdge(i, j, 2);
                if (a[i][j] == 'N') HLPP::addEdge(i, j, INF);
            }
        HLPP::addEdge(S, a1, 2 * an), HLPP::addEdge(a2, T, 2 * an);
        HLPP::addEdge(S, b2, 2 * bn), HLPP::addEdge(b1, T, 2 * bn);
        if (HLPP::work(S, T) != 2 * (an + bn)) check = false;
        putstr(check ? "Yes" : "No"), putch('\n');
    }
    return 0;
}