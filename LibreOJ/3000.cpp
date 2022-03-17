/**
 * @file 3000.cpp
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
#define maxq 300005

typedef tuple<int, int, int> tiii;

class UnionSet {
   private:
    int fa[maxn];

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

   public:
    void build(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
        return;
    }
    bool merge(int x, int y) {
        if (check(x, y)) return false;
        fa[getfa(y)] = getfa(x);
        return true;
    }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
} US;
class SegmentTree {
   private:
    int tree[maxn << 2], n;
    bool lazy[maxn << 2];

    void pushDown(int p) {
        if (!lazy[p]) return;
        return tree[p << 1] = tree[p << 1 | 1] = 0, lazy[p << 1] = lazy[p << 1 | 1] = true, lazy[p] = false, void();
    }
    void pushUp(int p) { return tree[p] = tree[p << 1] + tree[p << 1 | 1], void(); }
    void build(int p, int l, int r) {
        if (l == r) return tree[p] = 1, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p] = 0, lazy[p] = true, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int l, int r) { return update(1, 1, n, l, r); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

tiii ques[maxq];
int dfni[maxn], dfno[maxn], fa[maxn], top[maxn], dep[maxn], siz[maxn], son[maxn];
vector<vector<int>> graph;

void dfs1(int p) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != fa[p]) {
            fa[i] = p, dep[i] = dep[p] + 1, dfs1(i), siz[p] += siz[i];
            if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int top_) {
    dfni[p] = ++dfnt, top[p] = top_;
    if (son[p]) dfs2(son[p], top_);
    for (auto i : graph[p])
        if (i != fa[p] && i != son[p]) dfs2(i, i);
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n = read<int>(), q = read<int>();
    graph.resize(n + 1), US.build(n);
    for (int i = 1; i <= q; i++) {
        get<0>(ques[i]) = read<int>(), get<1>(ques[i]) = read<int>(), get<2>(ques[i]) = read<int>();
        if (get<0>(ques[i]) == 1 && US.merge(get<1>(ques[i]), get<2>(ques[i])))
            graph[get<1>(ques[i])].push_back(get<2>(ques[i])), graph[get<2>(ques[i])].push_back(get<1>(ques[i]));
    }
    for (int i = 1; i <= n; i++)
        if (!dfni[i]) dfs1(i), dfs2(i, i);
    US.build(n), ST.resize(n), ST.build();
    for (int i = 1; i <= q; i++) {
        int x = get<1>(ques[i]), y = get<2>(ques[i]);
        if (get<0>(ques[i]) == 1) {
            if (!US.merge(x, y)) {
                while (top[x] != top[y]) {
                    if (dep[top[x]] < dep[top[y]]) swap(x, y);
                    ST.update(dfni[top[x]], dfni[x]), x = fa[top[x]];
                }
                if (dep[x] > dep[y]) swap(x, y);
                if (x != y) ST.update(dfni[x] + 1, dfni[y]);
            }
        } else {
            if (US.check(x, y)) {
                int ans = 0;
                while (top[x] != top[y]) {
                    if (dep[top[x]] < dep[top[y]]) swap(x, y);
                    ans += ST.query(dfni[top[x]], dfni[x]), x = fa[top[x]];
                }
                if (dep[x] > dep[y]) swap(x, y);
                if (x != y) ans += ST.query(dfni[x] + 1, dfni[y]);
                write(ans), putch('\n');
            } else
                putstr("-1\n");
        }
    }
    return;
}

bool mem2;

int main() {
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
