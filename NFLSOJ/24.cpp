/**
 * @file 24.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
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
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 1000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class UnionSet {
   public:
    int fa[maxn];

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    void merge(int x, int y) {
        if (check(x, y)) return;
        fa[getfa(x)] = getfa(y);
        return;
    }
} US;

vector<vector<pii>> graph;
vector<tiii> edges, rec, mark[maxn];

int fa[maxn], siz[maxn], son[maxn], top[maxn], dep[maxn], f[maxn], ans[maxn];

void dfs1(int p) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i.first != fa[p]) {
            fa[i.first] = p, dep[i.first] = dep[p] + 1, dfs1(i.first), siz[p] += siz[i.first];
            if (!son[p] || siz[i.first] > siz[son[p]]) son[p] = i.first;
        }
    return;
}
void dfs2(int p, int top_) {
    top[p] = top_;
    if (son[p]) dfs2(son[p], top_);
    for (auto i : graph[p])
        if (i.first != fa[p] && i.first != son[p]) dfs2(i.first, i.first);
    return;
}
void dfs3(int p) {
    int minE = numeric_limits<int>::max();
    for (auto i : graph[p]) US.fa[i.first] = i.first, minE = min(minE, i.second);
    ans[p] = max(ans[p], minE);
    if (p != 1) {
        for (auto i : graph[p])
            if (i.first != fa[p] && f[i.first] != -1) mark[p].emplace_back(i.first, fa[p], f[i.first]);
    }
    sort(mark[p].begin(), mark[p].end(), [](tiii a, tiii b) { return get<2>(a) < get<2>(b); });
    for (auto i : mark[p]) {
        int x, y, d;
        tie(x, y, d) = i;
        if (US.check(x, y)) continue;
        ans[p] = max(ans[p], d), US.merge(x, y);
    }
    for (auto i : graph[p])
        if (!US.check(graph[p][0].first, i.first)) ans[p] = -1;
    for (auto i : graph[p])
        if (i.first != fa[p]) dfs3(i.first);
    return;
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int near(int x, int y) {
    if (x == y) return x;
    while (top[x] != top[y]) {
        if (y == fa[top[x]]) return top[x];
        x = fa[top[x]];
    }
    return son[y];
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), w = read<int>();
        edges.emplace_back(x, y, w);
    }
    sort(edges.begin(), edges.end(), [](tiii a, tiii b) { return get<2>(a) < get<2>(b); });
    for (int i = 1; i <= n; i++) US.fa[i] = i;
    graph.resize(n + 1);
    int ori = 0;
    for (auto i : edges) {
        int x, y, d;
        tie(x, y, d) = i;
        if (US.check(x, y)) continue;
        US.merge(x, y), ori = max(ori, d);
        graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
    }
    for (int i = 1; i <= n; i++)
        if (!US.check(1, i)) return write(-n), putch('\n');
    for (int i = 1; i <= n; i++) ans[i] = ori;
    dfs1(1), dfs2(1, 1);
    for (auto i : edges) {
        int x, y, d;
        tie(x, y, d) = i;
        int p = LCA(x, y);
        if (p != x && p != y) mark[p].emplace_back(near(x, p), near(y, p), d);
        rec.emplace_back(x, near(x, p), d), rec.emplace_back(y, near(y, p), d);
    }
    sort(rec.begin(), rec.end(), [](tiii a, tiii b) { return get<2>(a) < get<2>(b); });
    for (int i = 1; i <= n; i++) US.fa[i] = i, f[i] = -1;
    for (auto i : rec) {
        int p = get<0>(i), t = get<1>(i);
        if (US.getfa(p) != p) p = US.getfa(p);
        if (US.getfa(t) != t) t = US.getfa(t);
        while (p != t) f[p] = get<2>(i), US.merge(p, fa[p]), p = US.getfa(p);
    }
    dfs3(1);
    long long answer = 0;
    for (int i = 1; i <= n; i++) answer += ans[i];
    write(answer), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("vain.in", "r", stdin), freopen("vain.out", "w", stdout);
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
