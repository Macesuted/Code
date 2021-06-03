/**
 * @author Macesuted (macesuted@qq.com)
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

typedef pair<int, int> pii;

struct Edge {
    int x, y, dist;
};

vector<Edge> tree[maxn << 2];
map<pii, pii> S;
pii ask[maxn];
int answer[maxn], fa[maxn], siz[maxn];
bool vis[maxn];

void insert(int p, int l, int r, int ql, int qr, Edge edge) {
    if (ql <= l && r <= qr) return tree[p].push_back(edge);
    int mid = (l + r) >> 1;
    if (ql <= mid) insert(p << 1, l, mid, ql, qr, edge);
    if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, edge);
    return;
}

stack<pii> rec;
int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }
void insert(int x, int y) {
    x = getfa(x), y = getfa(y);
    if (x == y) return rec.push((pii){-1, -1});
    if (siz[x] < siz[y]) swap(x, y);
    fa[y] = x, siz[x] += siz[y];
    return rec.push((pii){x, y});
}
void rollback(void) {
    if (rec.top().first == -1 && rec.top().second == -1) return rec.pop();
    fa[rec.top().second] = rec.top().second, siz[rec.top().first] -= siz[rec.top().second];
    return rec.pop();
}
void dfs(int p, int l, int r, int lim) {
    for (vector<Edge>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
        if (i->dist <= lim) insert(i->x, i->y);
    if (l == r && vis[l] && answer[l] == -1 && getfa(ask[l].first) == getfa(ask[l].second))
        answer[l] = lim;
    int mid = (l + r) >> 1;
    if (l != r) dfs(p << 1, l, mid, lim), dfs(p << 1 | 1, mid + 1, r, lim);
    for (vector<Edge>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
        if (i->dist <= lim) rollback();
    return;
}

int main() {
    int n = read<int>(), q = read<int>();
    for (register int i = 1; i <= q; i++) {
        int opt = read<int>();
        if (opt == 0) {
            int x = read<int>(), y = read<int>(), dist = read<int>();
            if (x > y) swap(x, y);
            S[(pii){x, y}] = (pii){dist, i};
        } else if (opt == 1) {
            int x = read<int>(), y = read<int>();
            if (x > y) swap(x, y);
            insert(1, 1, q, S[(pii){x, y}].second, i, (Edge){x, y, S[(pii){x, y}].first});
            S.erase((pii){x, y});
        } else
            vis[i] = true, ask[i].first = read<int>(), ask[i].second = read<int>();
    }
    for (map<pii, pii>::iterator i = S.begin(); i != S.end(); i++)
        insert(1, 1, q, i->second.second, q, (Edge){i->first.first, i->first.second, i->second.first});
    memset(answer, -1, sizeof(answer));
    for (register int i = 0; i <= 10; i++) {
        for (register int j = 0; j < n; j++) fa[j] = j, siz[j] = 1;
        dfs(1, 1, q, i);
    }
    for (register int i = 1; i <= q; i++)
        if (vis[i]) write(answer[i]), putch('\n');
    return 0;
}
