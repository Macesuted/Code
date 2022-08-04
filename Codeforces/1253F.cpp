/**
 * @file 1253F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-12-29
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

#define maxn 100005
#define maxlgn 20

typedef pair<int, long long> pil;
typedef pair<long long, int> pli;

struct Edge {
    int from, to;
    long long dist;
    bool operator<(const Edge& oth) const { return this->dist < oth.dist; }
};

vector<vector<pil>> graph, tree;
vector<Edge> edges;

long long dist[maxn];
bool vis[maxn];
int fa[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

int dep[maxn], f[maxn][maxlgn];
long long g[maxn][maxlgn];

void dfs(int p, int pre = 0) {
    for (int i = 1; i < maxlgn; i++) f[p][i] = f[f[p][i - 1]][i - 1], g[p][i] = max(g[p][i - 1], g[f[p][i - 1]][i - 1]);
    for (auto i : tree[p])
        if (i.first != pre) dep[i.first] = dep[p] + 1, f[i.first][0] = p, g[i.first][0] = i.second, dfs(i.first, p);
    return;
}

long long maxDist(int x, int y) {
    long long maxDist = 0;
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[f[x][i]] >= dep[y]) maxDist = max(maxDist, g[x][i]), x = f[x][i];
    if (x == y) return maxDist;
    for (int i = maxlgn - 1; ~i; i--)
        if (f[x][i] != f[y][i]) maxDist = max({maxDist, g[x][i], g[y][i]}), x = f[x][i], y = f[y][i];
    return max({maxDist, g[x][0], g[y][0]});
}

void solve(void) {
    int n = read<int>(), m = read<int>(), k = read<int>(), q = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), w = read<int>();
        graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);
    }

    memset(dist, 0x3f, sizeof(dist));
    static priority_queue<pli, vector<pli>, greater<pli>> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= k; i++) que.emplace(dist[i] = 0, i);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
    }

    edges.clear();
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (i < j.first) edges.push_back(Edge{i, j.first, dist[i] + j.second + dist[j.first]});
    sort(edges.begin(), edges.end());
    tree.resize(n + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (auto i : edges) {
        if (getfa(i.from) == getfa(i.to)) continue;
        int x = getfa(i.from), y = getfa(i.to);
        fa[y] = x;
        tree[i.from].emplace_back(i.to, i.dist), tree[i.to].emplace_back(i.from, i.dist);
    }
    dfs(1);

    while (q--) write(maxDist(read<int>(), read<int>())), putch('\n');

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
