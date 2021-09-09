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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        int cover, cnt;
        Node(void) { cover = cnt = 0; }
    };
    Node tree[maxn << 2];

    int n;

    void pushUp(int p, int l, int r) {
        if (tree[p].cover)
            tree[p].cnt = r - l + 1;
        else
            tree[p].cnt = tree[p << 1].cnt + tree[p << 1 | 1].cnt;
        return;
    }
    void update(int p, int l, int r, int ql, int qr, int delta) {
        if (ql <= l && r <= qr) return tree[p].cover += delta, pushUp(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, delta);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, delta);
        return pushUp(p, l, r);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, int delta) { return update(1, 1, n, l, r, delta); }
    int query(void) { return tree[1].cnt; }
};

SegmentTree tree;

vector<vector<int>> graph;

pii ask[maxn];
int dfni[maxn], dfno[maxn], ans[maxn];
vector<int> mark[maxn];

int tim = 0;
void dfs(int p, int pre = -1) {
    dfni[p] = ++tim;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p);
    dfno[p] = tim;
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1), tree.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs(1);
    for (register int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        swap(x, y);
        ask[i] = {x, y};
        mark[dfni[x]].push_back(+i), mark[dfno[x] + 1].push_back(-i);
        mark[dfni[y]].push_back(+i), mark[dfno[y] + 1].push_back(-i);
    }
    for (register int i = 1; i <= n; i++) {
        for (auto j : mark[i])
            tree.update(dfni[ask[abs(j)].first], dfno[ask[abs(j)].first], j / abs(j)),
                tree.update(dfni[ask[abs(j)].second], dfno[ask[abs(j)].second], j / abs(j));
        ans[i] = max(0, tree.query() - 1);
    }
    for (register int i = 1; i <= n; i++) write(ans[dfni[i]]), putch(" \n"[i == n]);
    return 0;
}