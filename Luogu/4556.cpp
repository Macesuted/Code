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
#define maxlgn 20

class SegmentTree {
   private:
    struct Node {
        int val, pos;
        Node *l, *r;
        Node(void) { l = r = NULL, val = pos = 0; }
    };

    Node* root;

    int n;

    inline void pushUp(Node* p) {
        if (p->l == NULL)
            p->val = p->r->val, p->pos = p->r->pos;
        else if (p->r == NULL)
            p->val = p->l->val, p->pos = p->l->pos;
        else if (p->l->val >= p->r->val)
            p->val = p->l->val, p->pos = p->l->pos;
        else
            p->val = p->r->val, p->pos = p->r->pos;
        return;
    }
    void update(Node*& p, int l, int r, int qp, int val) {
        if (p == NULL) p = new Node();
        if (l == r) return p->val += val, p->pos = l, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, val) : update(p->r, mid + 1, r, qp, val);
        return pushUp(p);
    }

    void merge(Node*& p, Node* tree, int l, int r) {
        if (tree == NULL) return;
        if (p == NULL) return p = tree, void();
        if (l == r) return p->val += tree->val, void();
        int mid = (l + r) >> 1;
        merge(p->l, tree->l, l, mid), merge(p->r, tree->r, mid + 1, r);
        return pushUp(p);
    }

   public:
    SegmentTree(void) { root = NULL, n = 1e5; }

    inline void update(int p, int val) { return update(root, 1, n, p, val); }
    inline int getMaxPos(void) { return (root == NULL || root->val == 0) ? 0 : root->pos; }
    inline SegmentTree& operator+=(const SegmentTree& tree) { return merge(root, tree.root, 1, n), *this; }
};

SegmentTree tree[maxn];

vector<vector<int> > graph;

int fa[maxn][maxlgn], dep[maxn], ans[maxn];

void dfs1(int p, int pre = 0) {
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs1(*i, p);
    return;
}
void dfs2(int p) {
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != fa[p][0]) dfs2(*i), tree[p] += tree[*i];
    ans[p] = tree[p].getMaxPos();
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
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1, from, to; i < n; i++) {
        from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs1(1);
    for (register int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>(), t = lca(x, y);
        tree[x].update(z, 1), tree[y].update(z, 1), tree[t].update(z, -1), tree[fa[t][0]].update(z, -1);
    }
    dfs2(1);
    for (register int i = 1; i <= n; i++) write(ans[i]), putch('\n');
    return 0;
}