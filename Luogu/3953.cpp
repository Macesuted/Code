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

#define maxn 100005
#define maxm 200005

typedef pair<int, int> pii;

vector<vector<pii> > graph;

int dist[maxn], f[55][maxn], mod;
bool vis[maxn], inStack[55][maxn], err;
int from[maxm], to[maxm], dis[maxm];
int n, m, k;

void Dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist)), memset(vis, 0, sizeof(vis));
    static priority_queue<pii, vector<pii>, greater<pii> > que;
    while (!que.empty()) que.pop();
    que.push((pii){dist[start] = 0, start});
    while (!que.empty()) {
        pii p = que.top();
        que.pop();
        if (vis[p.second]) continue;
        vis[p.second] = true;
        for (vector<pii>::iterator i = graph[p.second].begin(); i != graph[p.second].end(); i++)
            if (dist[i->first] > dist[p.second] + i->second)
                que.push((pii){dist[i->first] = dist[p.second] + i->second, i->first});
    }
    return;
}
int dfs(int d, int p) {
    if (d < 0) return 0;
    if (f[d][p] != -1) return f[d][p];
    if (inStack[d][p] || err) {
        err = true;
        return 0;
    }
    int answer = 0;
    inStack[d][p] = true;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        answer = (answer + dfs(d - (dist[i->first] + i->second - dist[p]), i->first)) % mod;
    inStack[d][p] = false;
    if (d == 0 && p == n) return f[d][p] = 1;
    return f[d][p] = answer;
}

int main() {
    int _ = read<int>();
    while (_--) {
        n = read<int>(), m = read<int>(), k = read<int>();
        mod = read<int>();
        graph.resize(n + 1);
        for (register int i = 1; i <= m; i++) {
            from[i] = read<int>(), to[i] = read<int>(), dis[i] = read<int>();
            graph[to[i]].push_back((pii){from[i], dis[i]});
        }
        Dijkstra(n);
        graph.clear();
        graph.resize(n + 1);
        for (register int i = 1; i <= m; i++) graph[from[i]].push_back((pii){to[i], dis[i]});
        memset(f, -1, sizeof(f));
        err = false;
        int answer = 0;
        for (register int i = 0; i <= k; i++) answer = (answer + dfs(i, 1)) % mod;
        if (err) answer = -1;
        write(answer), putch('\n');
        graph.clear();
    }
    return 0;
}