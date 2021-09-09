/**
 * @author Macesuted (macesuted@outlook.com)
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

struct Edge {
    int from, to, dist;
};
struct pii {
    int first, second;
    inline bool operator<(const pii& oth) const {
        return this->first < oth.first || (this->first == oth.first && this->second < oth.second);
    }
};
struct pli {
    long long first;
    int second;
    int id;
    inline bool operator<(const pli& oth) const {
        return this->first < oth.first || (this->first == oth.first && this->second < oth.second);
    }
    inline bool operator>(const pli& oth) const {
        return this->first > oth.first || (this->first == oth.first && this->second > oth.second);
    }
};

vector<vector<pli> > graph;
vector<Edge> edges;
set<int> S;
deque<int> Snodes;
int pos[maxn];

class SegmentTree {
   private:
    long long tree[maxn << 2], lazy[maxn << 2];

    inline void pushDown(int p) {
        tree[p << 1] = min(tree[p << 1], lazy[p]), tree[p << 1 | 1] = min(tree[p << 1 | 1], lazy[p]);
        lazy[p << 1] = min(lazy[p << 1], lazy[p]), lazy[p << 1 | 1] = min(lazy[p << 1 | 1], lazy[p]);
        lazy[p] = 0x3f3f3f3f3f3f3f3f;
        return;
    }
    void build(int p, int l, int r) {
        tree[p] = lazy[p] = 0x3f3f3f3f3f3f3f3f;
        if (l == r) return;
        int mid = (l + r) >> 1;
        return build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    }
    void update(int p, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) return tree[p] = min(tree[p], val), lazy[p] = min(lazy[p], val), void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
        tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
        return;
    }
    long long get(int p, int l, int r, int qp) {
        if (l == r) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        return qp <= mid ? get(p << 1, l, mid, qp) : get(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    int n;

    inline void build(int tn) { return build(1, 1, n = tn); }
    inline void update(int l, int r, long long val) { return update(1, 1, n, l, r, val); }
    inline long long get(int p) { return get(1, 1, n, p); }
} sgtree;
class SPT {
   private:
    int fa[maxn][maxlgn], dep[maxn];
    int root;

    void dfs1(int p, int pre) {
        dep[p] = dep[pre] + 1, fa[p][0] = pre;
        for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
        for (vector<pli>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
            if (i->second != pre) dfs1(i->second, p);
        return;
    }
    bool dfs2(int p, int to) {
        if (p == to) return true;
        for (vector<pli>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
            if (i->second != fa[p][0] && dfs2(i->second, to))
                return Snodes.push_front(i->second), S.insert(i->id), true;
        return false;
    }

   public:
    vector<vector<pli> > tree;
    long long dist[maxn];
    int pre[maxn], pid[maxn];
    bool vis[maxn];

    void INIT(int start) {
        root = start;
        tree.resize(graph.size());
        static priority_queue<pli, vector<pli>, greater<pli> > que;
        while (!que.empty()) que.pop();
        memset(vis, 0, sizeof(vis));
        memset(dist, 0x3f, sizeof(dist));
        que.push((pli){dist[start] = 0, start});
        while (!que.empty()) {
            pli p = que.top();
            que.pop();
            if (vis[p.second]) continue;
            vis[p.second] = true;
            if (pre[p.second]) tree[pre[p.second]].push_back((pli){dist[p.second] - dist[pre[p.second]], p.second, pid[p.second]}),
                               tree[p.second].push_back((pli){dist[p.second] - dist[pre[p.second]], pre[p.second], pid[p.second]});
            for (vector<pli>::iterator i = graph[p.second].begin(); i != graph[p.second].end(); i++)
                if (dist[i->second] > dist[p.second] + i->first)
                    que.push((pli){dist[i->second] = dist[p.second] + i->first, i->second}),
                        pre[i->second] = p.second, pid[i->second] = i->id;
        }
        dfs1(root, 0);
        return;
    }
    inline void getShortest(int end) { return dfs2(root, end), Snodes.push_front(root); }
    int LCA(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (register int i = maxlgn - 1; ~i; i--)
            if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if (x == y) return x;
        for (register int i = maxlgn - 1; ~i; i--)
            if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
        return fa[x][0];
    }
} tree[2];

int n;
void work(int from, int to, int dist) {
    // printf("%d %d %d!\n", from, to, dist);
    int l = tree[0].LCA(from, n), r = tree[1].LCA(to, 1);
    // printf("$%d %d\n", l, r);
    if (pos[l] + 1 > pos[r]) return;
    // printf("#%d %d %lld\n", pos[l] + 1, pos[r], tree[0].dist[from] + dist + tree[1].dist[to]);
    sgtree.update(pos[l] + 1, pos[r], tree[0].dist[from] + dist + tree[1].dist[to]);
    return;
}

int main() {
    n = read<int>();
    int m = read<int>(), q = read<int>();
    graph.resize(n + 1), edges.resize(m + 1);
    for (register int i = 1; i <= m; i++) {
        register int from = read<int>(), to = read<int>(), dist = read<int>();
        graph[from].push_back((pli){dist, to, i}), graph[to].push_back((pli){dist, from, i});
        edges[i] = (Edge){from, to, dist};
    }
    tree[0].INIT(1), tree[1].INIT(n);
    tree[0].getShortest(n);
    for (register int i = 0; i < (int)Snodes.size(); i++) pos[Snodes[i]] = i;
    sgtree.build(n);
    for (register int i = 1; i <= m; i++)
        if (!S.count(i)) work(edges[i].from, edges[i].to, edges[i].dist),
                         work(edges[i].to, edges[i].from, edges[i].dist);
    // for (register int i = 0; i < (int)Snodes.size(); i++) printf("%d ", Snodes[i]);
    // puts("");
    // for (register int i = 1; i < (int)Snodes.size(); i++) printf("%lld ", sgtree.get(i));
    // puts("");
    while (q--) {
        int x = read<int>(), v = read<int>();
        long long answer;
        if (edges[x].dist >= v)
            answer = min(min(tree[0].dist[edges[x].from] + v + tree[1].dist[edges[x].to],
                             tree[0].dist[edges[x].to] + v + tree[1].dist[edges[x].from]),
                         tree[0].dist[n]);
        else if (S.count(x))
            answer = min(sgtree.get(max(pos[edges[x].from], pos[edges[x].to])),
                         min(tree[0].dist[edges[x].from] + v + tree[1].dist[edges[x].to],
                             tree[0].dist[edges[x].to] + v + tree[1].dist[edges[x].from]));
        // answer = -1;
        else
            answer = tree[0].dist[n];
        write(answer), putch('\n');
    }
    return 0;
}