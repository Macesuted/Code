/**
 * @file 12930.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-28
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
    __int128 fx = x;
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

#define maxn 500005
#define maxlgn 20

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        int v1, v2, v3, v12, v23, v123, cnt;
        Node(void) { v1 = v2 = v3 = v12 = v23 = -1e8, v123 = cnt = 0; }
        Node(int dis) { v1 = v3 = dis, v2 = -2 * dis, v12 = v23 = -dis, v123 = cnt = 0; }
        Node(int v1_, int v2_, int v3_, int v12_, int v23_, int v123_, int cnt_) {
            v1 = v1_, v2 = v2_, v3 = v3_, v12 = v12_, v23 = v23_, v123 = v123_, cnt = cnt_;
        }
        Node operator+(const Node& o) const {
            return Node{max(v1, o.v1),
                        max(v2, o.v2),
                        max(v3, o.v3),
                        max({v12, v1 + o.v2, o.v12}),
                        max({v23, v2 + o.v3, o.v23}),
                        max({v123, v12 + o.v3, v1 + o.v23, o.v123}),
                        0};
        }
    };

    Node tree[maxn << 3], minV;
    int n;
    stack<pii> sta;

    Node getVal(int p) { return (tree[p].cnt == 0) ? tree[p] : minV; }
    void pushUp(int p) { return (!tree[p].cnt) && (tree[p] = getVal(p << 1) + getVal(p << 1 | 1), 1), void(); }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return tree[p] = Node(a[l]), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void ban(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return tree[p].cnt += v, void();
        int mid = (l + r) >> 1;
        if (ql <= mid) ban(p << 1, l, mid, ql, qr, v);
        if (qr > mid) ban(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (tree[p].cnt) return minV;
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    SegmentTree(void) { minV.v123 = -1e8; }
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(1, 1, n, a); }
    void ban(int l, int r) { return sta.emplace(l, r), ban(1, 1, n, l, r, +1); }
    void fallback(void) { return ban(1, 1, n, sta.top().first, sta.top().second, -1), sta.pop(); }
    int query(int l, int r) { return query(1, 1, n, l, r).v123; }
} ST;
class FenwickTree {
   private:
    int tree[maxn * 2];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn * 2; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

vector<vector<int>> graph;
int dfndep[maxn * 2], dep[maxn], dfni[maxn], dfno[maxn], dfn[maxn * 2], dfncnt = 0, K, f[maxn], fa[maxn][maxlgn];
vector<int> init[maxn];

int query(int p) { return ST.query(dfni[p], dfno[p]) + 1; }
void dfs1(int p, int pre = -1) {
    dfn[dfni[p] = ++dfncnt] = p;
    for (auto i : graph[p])
        if (i != pre) dep[i] = dep[p] + 1, dfs1(i, p), dfn[++dfncnt] = p;
    dfno[p] = dfncnt;
    return;
}
void dfs2(int p, int pre = 0) {
    fa[p][0] = pre;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p])
        if (i != pre) dfs2(i, p), f[p] = max(f[p], f[i]);
    int r = query(p) / K;
    for (int i = f[p] + 1; i <= r; i++) init[i].push_back(p);
    f[p] = max(f[p], r);
    return;
}

void solve(void) {
    int n = read<int>();
    K = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1), ST.resize(dfncnt);
    for (int i = 1; i <= dfncnt; i++) dfndep[i] = dep[dfn[i]];
    ST.build(dfndep), dfs2(1);
    for (int x = K, ix = 1, lastans = 0; x <= n; x += K, ix++) {
        if (read<int>() == 1) {
            int x = (read<int>() ^ lastans) % n + 1;
            ST.ban(dfni[x], dfno[x]);
        } else
            ST.fallback();
        static queue<int> que;
        while (!que.empty()) que.pop();
        for (auto i : init[ix]) que.push(i), FT.add(dfni[i], +1);
        int ans = 0;
        while (!que.empty()) {
            int p = que.front();
            que.pop(), FT.add(dfni[p], -1);
            if (query(p) >= x) ST.ban(dfni[p], dfno[p]), ans++;
            for (int i = maxlgn - 1; ~i; i--)
                if (fa[p][i] && query(fa[p][i]) < x) p = fa[p][i];
            p = fa[p][0];
            if (p && query(p) >= x && FT.sum(dfni[p]) == FT.sum(dfno[p])) que.push(p), FT.add(dfni[p], +1);
        }
        for (int i = 1; i <= ans; i++) ST.fallback();
        write(lastans = ans), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
#endif
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
