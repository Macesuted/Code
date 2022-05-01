/**
 * @file 2135.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-17
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

#define maxn 100005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        int siz;
        long long lazy, ans, c;
    };

    Node tree[maxn << 2];
    int n;

    void update(int p, long long v) { return tree[p].siz += v, tree[p].lazy += v, tree[p].ans += v * tree[p].c, void(); }
    void pushDown(int p) { return update(p << 1, tree[p].lazy), update(p << 1 | 1, tree[p].lazy), tree[p].lazy = 0, void(); }
    void pushUp(int p) {
        return tree[p].siz = max(tree[p << 1].siz, tree[p << 1 | 1].siz), tree[p].ans = tree[p << 1].ans + tree[p << 1 | 1].ans,
               tree[p].c = tree[p << 1].c + tree[p << 1 | 1].c, void();
    }
    void build(int p, int l, int r, int c[]) {
        if (l == r) return tree[p].c = c[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, c), build(p << 1 | 1, mid + 1, r, c);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return update(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    long long calc(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].ans;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return calc(p << 1, l, mid, ql, qr);
        if (ql > mid) return calc(p << 1 | 1, mid + 1, r, ql, qr);
        return calc(p << 1, l, mid, ql, qr) + calc(p << 1 | 1, mid + 1, r, ql, qr);
    }
    int find(int p, int l, int r, int v) {
        if (l == r) return l;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (tree[p << 1 | 1].siz >= v) return find(p << 1 | 1, mid + 1, r, v);
        return find(p << 1, l, mid, v);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(int c[]) { return build(1, 1, n, c); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    long long calc(int l, int r) { return calc(1, 1, n, l, r); }
    int find(int v) { return find(1, 1, n, v); }
} ST;

vector<vector<pii>> graph;

int siz[maxn], dep[maxn], dist[maxn], son[maxn], fa[maxn], top[maxn], dfni[maxn], dfno[maxn], nti[maxn], c[maxn];

void dfs1(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i.first != pre) {
            fa[i.first] = p, dep[i.first] = dep[p] + 1, dist[i.first] = dist[p] + i.second, dfs1(i.first, p),
            siz[p] += siz[i.first];
            if (!son[p] || siz[i.first] > siz[son[p]]) son[p] = i.first;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int top_) {
    top[p] = top_, dfni[p] = ++dfnt;
    if (son[p]) dfs2(son[p], top_);
    for (auto i : graph[p])
        if (i.first != fa[p] && i.first != son[p]) dfs2(i.first, i.first);
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n = read<int>(), Q = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), c = read<int>();
        graph[x].emplace_back(y, c), graph[y].emplace_back(x, c);
    }
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++) nti[dfni[i]] = i;
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i]) c[max(dfni[i], dfni[j.first])] = j.second;
    ST.resize(n), ST.build(c);
    long long sum = 0, tot = 0;
    for (int i = 1; i <= Q; i++) {
        int u = read<int>(), e = read<int>();
        tot += e, sum += 1LL * e * dist[u];
        while (u) ST.update(dfni[top[u]], dfni[u], e), u = fa[top[u]];
        int p = nti[ST.find((tot + 1) / 2)];
        long long ans = sum + dist[p] * tot;
        while (p) ans -= 2 * ST.calc(dfni[top[p]], dfni[p]), p = fa[top[p]];
        write(ans), putch('\n');
    }
    return;
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
