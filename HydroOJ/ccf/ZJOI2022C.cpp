/**
 * @file ZJOI2022C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

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

#define maxn 1200005
#define maxlgn 22
#define mod 998244353

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef pair<int64_t, int64_t> pll;

vector<int> nodes[maxn], tree[maxn];
vector<pii> graph[maxn], cache[maxn];
map<int, int> cbel[maxn];
map<int, int64_t> dist[maxn][2];
vector<tiii> edge, edges[maxn];
int64_t rsum[maxn];
pll td[maxn][maxlgn];
int bcnt = 0, n, dfn[maxn], low[maxn], dd[maxn][2], rcnt[maxn], fa[maxn][maxlgn], dep[maxn];
queue<int> que;

stack<int> ts;
int dfnt = 0;
void tarjan(int p, int pre = -1) {
    ts.push(p);
    dfn[p] = low[p] = ++dfnt;
    for (auto i : graph[p])
        if (!dfn[i.first]) {
            tarjan(i.first), low[p] = min(low[p], low[i.first]);
            if (low[i.first] >= dfn[p]) {
                nodes[++bcnt].push_back(p), tree[p].push_back(n + bcnt);
                while (ts.top() != i.first) nodes[bcnt].push_back(ts.top()), tree[n + bcnt].push_back(ts.top()), ts.pop();
                nodes[bcnt].push_back(ts.top()), tree[n + bcnt].push_back(ts.top()), ts.pop();
            }
        } else if (i.first != pre)
            low[p] = min(low[p], dfn[i.first]);
    return;
}

pll path(int x, int y, int t) {
    bool tx = (x == dd[t][0] || x == dd[t][1]), ty = (y == dd[t][0] || y == dd[t][1]);
    if (tx && ty) return {rsum[t], rcnt[t]};
    if (tx) return {(rsum[t] + (rcnt[t] - 2) * dist[y][x == dd[t][0]][t]) % mod, rcnt[t]};
    if (ty) return {(rsum[t] + (rcnt[t] - 2) * dist[x][y == dd[t][0]][t]) % mod, rcnt[t]};
    if (cbel[x][t] == cbel[y][t])
        return {(rsum[t] + (rcnt[t] - 2) * (min(dist[x][0][t], dist[y][0][t]) + min(dist[x][1][t], dist[y][1][t]))) % mod,
                rcnt[t]};
    return {(2 * rsum[t] + (rcnt[t] - 3) * (dist[x][0][t] + dist[x][1][t] + dist[y][0][t] + dist[y][1][t])) % mod,
            2 * rcnt[t] - 2};
}
pll merge(pll a, pll b) { return {(a.first * b.second + b.first * a.second) % mod, a.second * b.second % mod}; }

void dfs1(int p, int pre = 0) {
    dep[p] = dep[pre] + 1, fa[p][0] = pre;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : tree[p]) dfs1(i, p);
    return;
}
void dfs2(int p) {
    td[p][0] = {0, 1}, td[p][1] = (fa[p][0] > n ? path(p, fa[p][1], fa[p][0] - n) : pll{0, 1});
    for (int i = 2; i < maxlgn; i++) td[p][i] = merge(td[p][i - 1], td[fa[p][i - 1]][i - 1]);
    for (auto i : tree[p]) dfs2(i);
    return;
}
int64_t LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    pll ans = {0, 1};
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) ans = merge(ans, td[x][i]), x = fa[x][i];
    if (x == y) return ans.first;
    for (int i = maxlgn - 1; i; i--)
        if (fa[x][i] != fa[y][i]) ans = merge(ans, merge(td[x][i], td[y][i])), x = fa[x][i], y = fa[y][i];
    if (fa[x][0] == fa[y][0]) return merge(ans, path(x, y, fa[x][0] - n)).first;
    return merge(ans, merge(td[x][1], td[y][1])).first;
}

void solve(void) {
    n = read();
    int m = read(), q = read();
    for (int i = 1, u, v, w; i <= m; i++) {
        u = read(), v = read(), w = read();
        graph[u].emplace_back(v, w), graph[v].emplace_back(u, w), edge.emplace_back(u, v, w);
    }
    tarjan(1), dfs1(1);
    for (auto i : edge) {
        int x, y, d;
        tie(x, y, d) = i;
        edges[fa[dep[x] > dep[y] ? x : y][0] - n].push_back(i);
    }
    for (int c = 1; c <= bcnt; c++) {
        for (auto i : edges[c])
            cache[get<0>(i)].emplace_back(get<1>(i), get<2>(i)), cache[get<1>(i)].emplace_back(get<0>(i), get<2>(i));
        int maxDeg = 0;
        for (auto i : nodes[c]) maxDeg = max(maxDeg, int(cache[i].size()));
        rcnt[c] = maxDeg;
        vector<int> pp;
        if (maxDeg > 2)
            for (auto i : nodes[c])
                if (maxDeg == int(cache[i].size())) pp.push_back(i);
        dd[c][0] = (pp.empty() ? nodes[c][0] : pp[0]), dd[c][1] = (pp.empty() ? nodes[c][1] : pp[1]);
        int chcnt = 0;
        vector<int> ch;
        for (auto i : cache[dd[c][0]]) {
            if (i.first == dd[c][1]) {
                rsum[c] = (rsum[c] + i.second) % mod;
                continue;
            }
            chcnt++, dist[i.first][0][c] = i.second, que.push(i.first);
            int lst = dd[c][0];
            while (!que.empty()) {
                int p = que.front();
                que.pop(), ch.push_back(p), cbel[p][c] = chcnt;
                for (auto i : cache[p])
                    if (i.first == dd[c][1])
                        dist[p][1][c] = i.second;
                    else if (i.first != dd[c][0] && i.first != lst)
                        dist[i.first][0][c] = dist[p][0][c] + i.second, que.push(i.first);
                lst = p;
            }
            int64_t len = dist[ch.back()][0][c] + dist[ch.back()][1][c];
            for (auto i : ch) dist[i][1][c] = len - dist[i][0][c];
            rsum[c] = (rsum[c] + len) % mod, ch.clear();
        }
        for (auto i : nodes[c]) cache[i].clear();
    }
    for (int i = 0; i < maxlgn; i++) td[0][i] = {0, 1};
    dfs2(1);
    while (q--) write(LCA(read(), read())), putch('\n');
    return;
}

bool mem2;

signed main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    freopen("simple.in", "r", stdin), freopen("simple.out", "w", stdout);
#endif
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