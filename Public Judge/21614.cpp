/**
 * @file 21614.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
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
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 305

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class UnionSet {
   private:
    int fa[maxn];

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

   public:
    void resize(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
        return;
    }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    bool merge(int x, int y) { return check(x, y) ? false : (fa[getfa(x)] = getfa(y), true); }
} US;
class Dinic {
   private:
    struct Edge {
        int to, cap, cost, rev;
    };

    vector<vector<Edge>> graph;
    vector<vector<Edge>::iterator> cur;
    vector<int64_t> dist;
    vector<bool> vis;
    queue<int> que;
    int n, S, T;

    bool bfs(void) {
        for (int i = 1; i <= n; i++) dist[i] = -1, vis[i] = false, cur[i] = graph[i].begin();
        que.push(S), dist[S] = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop(), vis[p] = false;
            for (auto i : graph[p])
                if (i.cap && dist[i.to] < dist[p] + i.cost) {
                    dist[i.to] = dist[p] + i.cost;
                    if (!vis[i.to]) que.push(i.to), vis[i.to] = true;
                }
        }
        return dist[T] >= 0;
    }
    int dfs(int p, int rest) {
        if (p == T) return rest;
        vis[p] = true;
        int use = 0, c;
        for (auto i = cur[p]; i != graph[p].end() && rest > use; i++) {
            cur[p] = i;
            if (!i->cap || dist[i->to] != dist[p] + i->cost || vis[i->to]) continue;
            if (!(c = dfs(i->to, min(rest - use, i->cap)))) dist[i->to] = -1;
            use += c, i->cap -= c, graph[i->to][i->rev].cap += c;
        }
        vis[p] = false;
        return use;
    }

   public:
    void resize(int _n) {
        return n = _n, graph.resize(n + 1), cur.resize(n + 1), dist.resize(n + 1), vis.resize(n + 1);
    }
    void addEdge(int from, int to, int cap, int cost) {
        return graph[from].push_back(Edge{to, cap, cost, (int)graph[to].size()}),
               graph[to].push_back(Edge{from, 0, -cost, (int)graph[from].size() - 1});
    }
    pii maxCost(int _S, int _T) {
        S = _S, T = _T;
        pii ans = {0, 0};
        while (bfs()) {
            int ret = dfs(S, numeric_limits<int>::max());
            ans.first += ret, ans.second += ret * dist[T];
        }
        return ans;
    }
} flow;

vector<tiii> edges;
vector<vector<pii>> tree;
int fa[maxn], fap[maxn];
bool vis[maxn];

void dfs(int p, int pre = -1) {
    vis[p] = true, fa[p] = pre;
    if (pre == -1) fap[p] = 1e7;
    for (auto i : tree[p])
        if (i.first != pre) fap[i.first] = i.second, dfs(i.first, p);
    return;
}

void solve(void) {
    int n = read(), m = read(), k = read(), S = k + 2 * n + 1, T = S + 1;
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        edges.emplace_back(w, u, v);
    }
    sort(edges.begin(), edges.end()), US.resize(n), flow.resize(T), tree.resize(n + 1);
    for (int i = 1; i <= k; i++) flow.addEdge(S, 2 * n + i, 1, 0);
    for (int i = 1; i <= k; i++) {
        int t = read();
        while (t--) flow.addEdge(2 * n + i, read(), 1, 0);
    }
    for (int i = 1; i <= n; i++) flow.addEdge(i, n + i, 1, 0);
    int tot = 0;
    for (auto i : edges) {
        auto [w, x, y] = i;
        if (US.merge(x, y)) tot += w, tree[x].emplace_back(y, w), tree[y].emplace_back(x, w);
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i), tot += 1e7;
    for (int i = 1; i <= n; i++) flow.addEdge(n + i, T, 1, fap[i]);
    for (int i = 1; i <= n; i++)
        if (fa[i] != -1) flow.addEdge(n + i, fa[i], 1, 0);
    pii ret = flow.maxCost(S, T);
    int ans = tot - ret.second;
    return write((ans >= 1e7 || ret.first < k) ? -1 : ans), putch('\n');
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
