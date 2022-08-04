/**
 * @file CSPS2021D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 22)
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

#define maxn 505

constexpr int INF = numeric_limits<int>::max() / 2;

typedef pair<int, int> pii;

vector<vector<pii>> graph;
vector<map<int, int>> extra;

int dist[maxn * maxn], f[maxn][maxn], g[maxn][maxn];
bool vis[maxn * maxn], choose[maxn * maxn];
int x[maxn * 4];
vector<pii> a;

#define Min(x, y) ((x) < (y) ? (x) : (y))

void Dijkstra(int S, int rest) {
    static priority_queue<pii, vector<pii>, greater<pii>> que;
    while (!que.empty()) que.pop();
    memset(dist, 0x3f, sizeof(dist)), memset(vis, 0, sizeof(vis));
    que.emplace(dist[S] = 0, S);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        rest -= choose[p];
        if (rest == 0) return;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
        for (auto i : extra[p])
            if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
    }
    return;
}
#define turn(x, y) ((x) * (m + 1) + (y))
void solve(void) {
    int n = read<int>(), m = read<int>(), q = read<int>();
    graph.resize((n + 1) * (m + 1));
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) {
            int d = read<int>();
            graph[turn(i, j - 1)].emplace_back(turn(i, j), d);
            graph[turn(i, j)].emplace_back(turn(i, j - 1), d);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) {
            int d = read<int>();
            graph[turn(i - 1, j)].emplace_back(turn(i, j), d);
            graph[turn(i, j)].emplace_back(turn(i - 1, j), d);
        }
    while (q--) {
        extra.resize((n + 1) * (m + 1)), a.clear();
        for (int i = 1; i <= m; i++)
            extra[turn(0, i - 1)][turn(0, i)] = extra[turn(0, i)][turn(0, i - 1)] = extra[turn(n, i - 1)][turn(n, i)] =
                extra[turn(n, i)][turn(n, i - 1)] = 0;
        for (int i = 1; i <= n; i++)
            extra[turn(i, 0)][turn(i - 1, 0)] = extra[turn(i - 1, 0)][turn(i, 0)] = extra[turn(i, m)][turn(i - 1, m)] =
                extra[turn(i - 1, m)][turn(i, m)] = 0;
        int k = read<int>();
        for (int i = 1; i <= k; i++) {
            int v = read<int>(), p = read<int>(), c = read<int>();
            a.emplace_back(p, c);
#define addEdge(x, y, d) extra[x][y] = extra[y][x] = (d)
            if (1 <= p && p <= m)
                addEdge(turn(0, p - 1), turn(0, p), v);
            else if (m + 1 <= p && p <= m + n)
                addEdge(turn(p - m - 1, m), turn(p - m, m), v);
            else if (m + n + 1 <= p && p <= 2 * m + n)
                addEdge(turn(n, m - (p - m - n)), turn(n, m - (p - m - n) + 1), v);
            else
                addEdge(turn(n - (p - 2 * m - n), 0), turn(n - (p - 2 * m - n) + 1, 0), v);
#undef addEdge
        }
        sort(a.begin(), a.end());
        int last = a.back().second, t = 0;
        for (auto i : a) {
            if (i.second != last) {
                int p = i.first;
                if (1 <= p && p <= m)
                    x[t++] = turn(0, p - 1);
                else if (m + 1 <= p && p <= m + n)
                    x[t++] = turn(p - m - 1, m);
                else if (m + n + 1 <= p && p <= 2 * m + n)
                    x[t++] = turn(n, m - (p - m - n) + 1);
                else
                    x[t++] = turn(n - (p - 2 * m - n) + 1, 0);
            }
            last = i.second;
        }
        if (t <= 1) {
            write(0), putch('\n');
            continue;
        }
        for (int i = 0; i < t; i++) choose[x[i]] = true;
        for (int i = 0; i < t; i++) {
            Dijkstra(x[i], t);
            for (int j = 0; j < t; j++) f[i][j] = dist[x[j]];
        }
        for (int i = 0; i < t; i++) choose[x[i]] = false;
        for (int i = 0; i < 2 * t; i++)
            for (int j = t; j < 2 * t; j++) f[i][j] = f[j][i] = f[i][j - t];
        for (int i = 0; i < t; i++) x[i + t] = x[i];
        for (int i = 0; i < 2 * t; i++)
            for (int j = 0; j < 2 * t; j++) g[i][j] = INF;
        for (int i = 1; i < 2 * t; i++) g[i - 1][i] = f[i - 1][i];
        for (int len = 4; len <= t; len += 2)
            for (int l = 0, r = len - 1; r < 2 * t; l++, r++) {
                g[l][r] = g[l + 1][r - 1] + f[l][r];
                for (int p = l + 1; p <= r; p += 2) g[l][r] = Min(g[l][r], g[l][p] + g[p + 1][r]);
            }
        int answer = INF;
        for (int i = 0; i < t; i++) answer = Min(answer, g[i][i + t - 1]);
        write(answer), putch('\n');
        extra.clear();
    }
    return;
}
#undef turn

bool mem2;

int main() {
#ifndef LOCAL
    freopen("traffic.in", "r", stdin), freopen("traffic.out", "w", stdout);
#endif
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}