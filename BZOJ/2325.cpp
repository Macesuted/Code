/**
 * @file 2325.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
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

bool mem1;

#define maxn 50005

typedef pair<int, int> pii;

class SegmentTree {
   public:
    struct Node {
        int sum[2][2], lans[2], rans[2];
        Node(void) { sum[0][0] = -1; }
        Node(int v) {
            sum[0][0] = sum[0][1] = sum[1][0] = sum[1][1] = 0;
            if (v & 1) sum[0][0] = 1;
            if (v >> 1 & 1) sum[1][1] = 1;
            if (v == 3) sum[1][0] = sum[0][1] = 2;
            lans[0] = rans[0] = max(sum[0][0], sum[0][1]), lans[1] = rans[1] = max(sum[1][0], sum[1][1]);
        }
        inline Node operator+(const Node& oth) const {
            if (this->sum[0][0] == -1) return oth;
            if (oth.sum[0][0] == -1) return *this;
            Node ans = Node(0);
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                        if (this->sum[i][j] && oth.sum[j][k])
                            ans.sum[i][k] = max(ans.sum[i][k], this->sum[i][j] + oth.sum[j][k]);
            for (int i = 0; i < 2; i++) {
                ans.lans[i] = this->lans[i], ans.rans[i] = oth.rans[i];
                for (int j = 0; j < 2; j++) {
                    if (this->sum[i][j]) ans.lans[i] = max(ans.lans[i], this->sum[i][j] + oth.lans[j]);
                    if (oth.sum[j][i]) ans.rans[i] = max(ans.rans[i], this->rans[j] + oth.sum[j][i]);
                }
            }
            return ans;
        }
    };

   private:
    Node tree[maxn << 2];
    int n;

    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = Node(v), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    inline void resize(int _n) { return n = _n, void(); }
    inline void update(int p, int v) { return update(1, 1, n, p, v); }
    inline Node query(int l, int r) { return query(1, 1, n, l, r); }
};

SegmentTree SGT;

vector<vector<int>> graph;

int dfni[maxn], dfno[maxn], dep[maxn], siz[maxn], top[maxn], son[maxn], fa[maxn];

void dfs1(int p) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != fa[p]) {
            dep[i] = dep[p] + 1, fa[i] = p;
            dfs1(i);
            siz[p] += siz[i];
            if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
int tim = 0;
void dfs2(int p, int _top) {
    dfni[p] = ++tim, top[p] = _top;
    if (son[p]) dfs2(son[p], _top);
    for (auto i : graph[p])
        if (i != fa[p] && i != son[p])
            dfs2(i, i);
    dfno[p] = tim;
    return;
}
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int query(int x, int y) {
    int lca = LCA(x, y);
    SegmentTree::Node answer;
    while (top[x] != top[lca]) {
        answer = SGT.query(dfni[top[x]], dfni[x]) + answer;
        x = fa[top[x]];
    }
    answer = SGT.query(dfni[lca], dfni[x]) + answer;
    swap(answer.sum[0][1], answer.sum[1][0]);
    swap(answer.lans[0], answer.rans[0]), swap(answer.lans[1], answer.rans[1]);
    stack<pii> cache;
    while (top[y] != top[lca]) {
        cache.push({dfni[top[y]], dfni[y]});
        y = fa[top[y]];
    }
    if (lca != y) cache.push({dfni[lca] + 1, dfni[y]});
    while (!cache.empty()) {
        int l, r;
        tie(l, r) = cache.top(), cache.pop();
        answer = answer + SGT.query(l, r);
    }
    return max(answer.lans[0], answer.lans[1]);
}
void solve(void) {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1), dfs2(1, 1);
    SGT.resize(n);
    for (int i = 1; i <= n; i++) {
        string s = getstr();
        SGT.update(dfni[i], (s[0] == '.') << 1 | (s[1] == '.'));
    }
    while (m--) {
        char opt = getstr()[0];
        if (opt == 'C') {
            int p = read<int>();
            string s = getstr();
            SGT.update(dfni[p], (s[0] == '.') << 1 | (s[1] == '.'));
        } else {
            int x = read<int>(), y = read<int>();
            write(query(x, y)), putch('\n');
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
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}