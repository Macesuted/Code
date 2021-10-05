/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

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

#define maxn 200005
#define maxlgn 20

typedef pair<int, int> pii;

struct Ask {
    int tim, from, to, id;
    inline bool operator<(const Ask& oth) const { return this->tim < oth.tim; }
};

vector<vector<int> > graph;

vector<Ask> ask;
vector<pii> changes;

class SegmentTree {
   private:
    long long tree[maxn << 2], lazy[maxn << 2];
    int n;

    void pushDown(int p, int l, int r) {
        if (!lazy[p]) return;
        int mid = (l + r) >> 1;
        tree[p << 1] += (mid - l + 1) * lazy[p], tree[p << 1 | 1] += (r - mid) * lazy[p];
        lazy[p << 1] += lazy[p], lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
        return;
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p] += r - l + 1, lazy[p]++, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
        return;
    }
    long long getVal(int p, int l, int r, int qp) {
        if (l == r) return tree[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        return qp <= mid ? getVal(p << 1, l, mid, qp) : getVal(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    inline void update(int l, int r) { return update(1, 1, n, l, r); }
    inline long long getVal(int p) { return getVal(1, 1, n, p); }
};

SegmentTree tree;

int ans1[maxn], ans2[maxn];
int dfni[maxn], dfno[maxn];
int fa[maxn][maxlgn], dep[maxn];

int tim = 0;
void dfs(int p, int pre = 0) {
    dfni[p] = ++tim;
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) dfs(*i, p);
    dfno[p] = tim;
    return;
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (register int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (register int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main() {
    int n = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= n; i++) graph[read<int>()].push_back(i);
    dfs(0);
    tree.resize(n + 1);
    int q = read<int>(), cnt = 0;
    for (register int i = 1; i <= q; i++)
        if (read<int>() == 1) {
            int from = read<int>(), to = read<int>(), c = read<int>();
            ask.push_back((Ask){i - c, from, to, ++cnt});
        } else
            changes.push_back((pii){i, read<int>()});
    sort(ask.begin(), ask.end());
    vector<pii>::iterator j = changes.begin();
    for (vector<Ask>::iterator i = ask.begin(); i != ask.end(); i++) {
        while (j != changes.end() && j->first < i->tim) tree.update(dfni[j->second], dfno[j->second]), j++;
        int t = lca(i->from, i->to);
        ans1[i->id] = dep[i->from] + dep[i->to] - dep[t] - dep[fa[t][0]];
        ans2[i->id] = tree.getVal(dfni[i->from]) + tree.getVal(dfni[i->to]) -
                      tree.getVal(dfni[t]) - tree.getVal(dfni[fa[t][0]]);
    }
    for (register int i = 1; i <= cnt; i++) write(ans1[i]), putch(' '), write(ans2[i]), putch('\n');
    return 0;
}