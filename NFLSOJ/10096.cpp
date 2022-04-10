/**
 * @file 10096.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-09
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

#define maxn 300005
#define maxlgn 20

typedef pair<int, int> pii;

vector<vector<int>> graph;
vector<pii> chain[maxn];
vector<int> cross[maxn];
pii choose[maxn];
int fa[maxn][maxlgn], dep[maxn], depl[maxn], depr[maxn], bel[maxn], last[maxn], cnt[maxn];
bool ban[maxn], ok[maxn], vis[maxn];

int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
void dfs1(int p, int pre = 0) {
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p])
        if (i != pre) dfs1(i, p);
    return;
}
void dfs2(int p, int pre = 0) {
    ban[p] = true;
    for (auto i : graph[p])
        if (i != pre && !ban[i]) dfs2(i, p);
    return;
}
void dfs3(int p, int pre = 0) {
    ok[p] = true;
    for (auto i : graph[p])
        if (i != pre) dfs3(i, p);
    for (auto i : chain[p])
        if (!ban[i.first] && !ban[i.second]) {
            choose[p] = i, dfs2(p, pre);
            int x = i.first, y = i.second;
            depl[p] = dep[x], depr[p] = dep[y];
            while (x != p) ok[x] = false, bel[x] = p, x = fa[x][0];
            while (y != p) ok[y] = false, bel[y] = maxn + p, y = fa[y][0];
            ok[p] = false, bel[p] = p;
            return;
        }
    return;
}
void dfs4(int p, int pre = 0) {
    cnt[p]++;
    for (auto i : graph[p])
        if (i != pre && cnt[i] < 2) dfs4(i, p);
    return;
}
void dfs5(int p, int last_ = 0, int pre = 0) {
    if (!ok[p]) last_ = p;
    last[p] = last_;
    for (auto i : graph[p])
        if (i != pre) dfs5(i, last_, p);
    if (choose[p] != pii{0, 0}) {
        for (auto i : chain[p]) {
            int t = cnt[i.first] + cnt[i.second];
            cross[p].push_back(-1);
            if (t != 0) continue;
            cross[p].back() = 0;
        }
        dfs4(p, pre);
    } else
        for (auto i : chain[p]) {
            int t = cnt[i.first] + cnt[i.second];
            cross[p].push_back(-1);
            if (t != 1) continue;
            cross[p].back() = last[cnt[i.first] ? i.first : i.second];
        }
    return;
}
void dfs6(int p, int pre = 0) {
    if (ok[p])
        for (auto i : cross[p])
            if (i != -1) {
                if (bel[i] < maxn)
                    depl[bel[i]] = min(depl[bel[i]], dep[i]), depr[bel[i]] = dep[bel[i]];
                else
                    depr[bel[i] - maxn] = min(depr[bel[i] - maxn], dep[i]), depl[bel[i] - maxn] = dep[bel[i] - maxn];
            }
    if (choose[p] != pii{0, 0}) {
        int x = choose[p].first, y = choose[p].second;
        for (int i = 0; i < (int)chain[p].size(); i++) {
            if (cross[p][i] == -1) continue;
            int a = last[chain[p][i].first], b = last[chain[p][i].second];
            depl[p] = min(depl[p], max(dep[LCA(x, a)], dep[LCA(x, b)])),
            depr[p] = min(depr[p], max(dep[LCA(y, a)], dep[LCA(y, b)]));
        }
        while (dep[x] > depl[p]) ok[x] = true, x = fa[x][0];
        while (dep[y] > depr[p]) ok[y] = true, y = fa[y][0];
    }
    for (auto i : graph[p])
        if (i != pre) dfs6(i, p);
    return;
}
int dfs7(int p, int pre = -1) {
    int ans = 1;
    vis[p] = true;
    for (auto i : graph[p])
        if (i != pre && ok[i]) ans += dfs7(i, p);
    return ans;
}

void solve(void) {
    int n = read(), m = read();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1);
    for (int i = 1; i <= m; i++) {
        int x = read(), y = read();
        chain[LCA(x, y)].emplace_back(x, y);
    }
    dfs3(1), dfs5(1), dfs6(1);
    auto sqr = [](int64_t x) { return x * x; };
    int64_t ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i] && ok[i]) ans += sqr(dfs7(i));
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("rose.in", "r", stdin), freopen("rose.out", "w", stdout);
#endif
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
