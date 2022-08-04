/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Solution: https://macesuted.moe/article/h1034
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

#define maxn 100005

class SegmentTree {
   public:
    struct Node {
        unsigned long long l0, l1, r0, r1;
        Node(void) { l0 = 0, l1 = ~0, r0 = 0, r1 = ~0; }
        Node operator+(const Node& b) const {
            Node a = *this, ans;
            ans.l0 = (a.l0 & b.l1) | (~a.l0 & b.l0);
            ans.l1 = (a.l1 & b.l1) | (~a.l1 & b.l0);
            ans.r0 = (b.r0 & a.r1) | (~b.r0 & a.r0);
            ans.r1 = (b.r1 & a.r1) | (~b.r1 & a.r0);
            return ans;
        }
    };
    Node tree[maxn << 2];
    int n;

    void update(int p, int l, int r, int qp, int opt, unsigned long long val) {
        if (l == r) {
            if (opt == 1)
                tree[p].l0 = tree[p].r0 = 0, tree[p].l1 = tree[p].r1 = val;
            else if (opt == 2)
                tree[p].l0 = tree[p].r0 = val, tree[p].l1 = tree[p].r1 = ~0;
            else
                tree[p].l0 = tree[p].r0 = val, tree[p].l1 = tree[p].r1 = ~val;
            return;
        }
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, opt, val) : update(p << 1 | 1, mid + 1, r, qp, opt, val);
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
        return;
    }
    Node merge(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        Node answer;
        if (ql <= mid) answer = answer + merge(p << 1, l, mid, ql, qr);
        if (qr > mid) answer = answer + merge(p << 1 | 1, mid + 1, r, ql, qr);
        return answer;
    }
    inline void resize(int tn) { return n = tn, void(); }
    inline void update(int p, int opt, unsigned long long val) { return update(1, 1, n, p, opt, val); }
    inline Node merge(int l, int r) { return merge(1, 1, n, l, r); }
};

SegmentTree tree;

int opt[maxn];
unsigned long long val[maxn];

vector<vector<int> > graph;

int dep[maxn], siz[maxn], son[maxn], top[maxn], fa[maxn], dfn[maxn];

void dfs1(int p, int pre = 0) {
    dep[p] = dep[pre] + 1, fa[p] = pre, siz[p] = 1;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            dfs1(*i, p);
            if (!son[p] || siz[*i] > siz[son[p]]) son[p] = *i;
            siz[p] += siz[*i];
        }
    return;
}
int tim = 0;
void dfs2(int p, int t) {
    dfn[p] = ++tim, top[p] = t;
    if (son[p]) dfs2(son[p], t);
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != fa[p] && *i != son[p]) dfs2(*i, *i);
    return;
}
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int main() {
    int n = read<int>(), m = read<int>(), k = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= n; i++) opt[i] = read<int>(), val[i] = read<unsigned long long>();
    for (register int i = 1, from, to; i < n; i++) {
        from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs1(1), dfs2(1, 1);
    tree.resize(n);
    for (register int i = 1; i <= n; i++) tree.update(dfn[i], opt[i], val[i]);
    while (m--)
        if (read<int>() == 1) {
            int x = read<int>(), y = read<int>(), t = lca(x, y);
            unsigned long long z = read<unsigned long long>();
            SegmentTree::Node record1, record2;
            while (top[x] != top[t]) record1 = tree.merge(dfn[top[x]], dfn[x]) + record1, x = fa[top[x]];
            record1 = tree.merge(dfn[t], dfn[x]) + record1;
            while (top[y] != top[t]) record2 = tree.merge(dfn[top[y]], dfn[y]) + record2, y = fa[top[y]];
            if (y != t) record2 = tree.merge(dfn[t] + 1, dfn[y]) + record2;
            swap(record1.l0, record1.r0), swap(record1.l1, record1.r1);
            SegmentTree::Node record = record1 + record2;
            bool up = true;
            unsigned long long answer = 0;
            for (register int i = k - 1; ~i; i--) {
                unsigned long long l0 = (record.l0 >> i & 1), l1 = (record.l1 >> i & 1), t = (z >> i & 1);
                if (!up)
                    answer |= max(l0, l1) << i;
                else if (t == 0)
                    answer |= l0 << i;
                else if (l0 >= l1)
                    answer |= l0 << i, up = false;
                else
                    answer |= l1 << i;
            }
            cout << answer << endl;
        } else {
            int p = read<int>(), opt = read<int>();
            unsigned long long val = read<unsigned long long>();
            tree.update(dfn[p], opt, val);
        }
    return 0;
}