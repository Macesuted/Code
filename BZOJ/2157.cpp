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

bool mem1;

#define maxn 20005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        int sum, maxV, minV;
        bool rev;
        inline Node operator+(const Node& oth) const {
            return Node({this->sum + oth.sum, max(this->maxV, oth.maxV), min(this->minV, oth.minV), false});
        }
    };

    Node tree[maxn << 2];
    int n;

    inline void reverseNode(int p) {
        tree[p].rev ^= true, tree[p].sum *= -1;
        tie(tree[p].maxV, tree[p].minV) = make_tuple(-tree[p].minV, -tree[p].maxV);
        return;
    }
    inline void pushDown(int p) {
        if (!tree[p].rev) return;
        reverseNode(p << 1), reverseNode(p << 1 | 1);
        tree[p].rev = false;
        return;
    }
    void build(int p, int l, int r, int v[]) {
        if (l == r) return tree[p] = Node({v[l], v[l], v[l]}), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, v), build(p << 1 | 1, mid + 1, r, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = Node({v, v, v}), void();
        pushDown(p);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void reverse(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return reverseNode(p);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) reverse(p << 1, l, mid, ql, qr);
        if (qr > mid) reverse(p << 1 | 1, mid + 1, r, ql, qr);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(int v[]) { return build(1, 1, n, v); }
    inline void update(int p, int v) { return update(1, 1, n, p, v); }
    inline void reverse(int l, int r) { return reverse(1, 1, n, l, r); }
    inline Node query(int l, int r) { return query(1, 1, n, l, r); }
};

SegmentTree SGT;

struct Edge {
    int x, y, dist;
};

int v[maxn], siz[maxn], son[maxn], dep[maxn], top[maxn], fa[maxn], dfni[maxn], dfno[maxn];

vector<vector<pii>> graph;
vector<Edge> edges;

void dfs1(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i.first != pre) {
            dep[i.first] = dep[p] + 1;
            dfs1(i.first, fa[i.first] = p);
            siz[p] += siz[i.first];
            if (!son[p] || siz[i.first] > siz[son[p]]) son[p] = i.first;
        }
    return;
}
int tim = 0;
void dfs2(int p, int _top) {
    dfni[p] = ++tim;
    top[p] = _top;
    if (son[p]) dfs2(son[p], _top);
    for (auto i : graph[p])
        if (i.first != fa[p] && i.first != son[p])
            dfs2(i.first, i.first);
    dfno[p] = tim;
    return;
}

void solve(void) {
    int n = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>() + 1, y = read<int>() + 1, d = read<int>();
        graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
        edges.push_back((Edge){x, y, d});
    }
    dfs1(1), dfs2(1, 1);
    for (auto& i : edges) {
        if (dep[i.x] < dep[i.y]) swap(i.x, i.y);
        v[dfni[i.x]] = i.dist;
    }
    SGT.resize(n), SGT.build(v);
    int m = read<int>();
    while (m--) {
        string opt = getstr();
        if (opt == "C") {
            int p = read<int>() - 1;
            SGT.update(dfni[edges[p].x], read<int>());
        } else if (opt == "N") {
            int x = read<int>() + 1, y = read<int>() + 1;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                SGT.reverse(dfni[top[x]], dfni[x]);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            if (x != y) SGT.reverse(dfni[x] + 1, dfni[y]);
        } else if (opt == "SUM") {
            int x = read<int>() + 1, y = read<int>() + 1, ans = 0;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans += SGT.query(dfni[top[x]], dfni[x]).sum;
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            if (x != y) ans += SGT.query(dfni[x] + 1, dfni[y]).sum;
            write(ans), putch('\n');
        } else if (opt == "MAX") {
            int x = read<int>() + 1, y = read<int>() + 1, ans = -0x3f3f3f3f;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans = max(ans, SGT.query(dfni[top[x]], dfni[x]).maxV);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            if (x != y) ans = max(ans, SGT.query(dfni[x] + 1, dfni[y]).maxV);
            write(ans), putch('\n');
        } else if (opt == "MIN") {
            int x = read<int>() + 1, y = read<int>() + 1, ans = 0x3f3f3f3f;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans = min(ans, SGT.query(dfni[top[x]], dfni[x]).minV);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            if (x != y) ans = min(ans, SGT.query(dfni[x] + 1, dfni[y]).minV);
            write(ans), putch('\n');
        }
    }
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << t2 - t1 << "ms" << endl;
    return 0;
}