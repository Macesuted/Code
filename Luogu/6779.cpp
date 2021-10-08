/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://macesuted.moe/article/lg6779
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
#define maxsqrtn 405
#define INF 0x3f3f3f3f3f3f3f3f

typedef pair<int, int> pii;

vector<vector<pii> > graph;

long long dist[maxn];
int dep[maxn], top[maxn], fa[maxn], siz[maxn], son[maxn];
int rec[maxn], dfn[maxn];

void dfs1(int p, int pre = 0) {
    dep[p] = dep[fa[p] = pre] + 1, siz[p] = 1;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->first != pre) {
            dist[i->first] = dist[p] + i->second, dfs1(i->first, p), siz[p] += siz[i->first];
            if (!son[p] || siz[son[p]] < siz[i->first]) son[p] = i->first;
        }
    return;
}
int tim = 0;
void dfs2(int p, int _top) {
    rec[dfn[p] = ++tim] = p;
    top[p] = _top;
    if (son[p]) dfs2(son[p], _top);
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->first != fa[p] && i->first != son[p]) dfs2(i->first, i->first);
    return;
}

int a[maxn];
int L[maxsqrtn], R[maxsqrtn], bel[maxn], lazy[maxsqrtn];
long long ans[maxsqrtn];
bitset<maxn> vis[maxsqrtn];
vector<int> S[maxsqrtn];
int cache[maxn], tail = 0;
int n, m, root;

int jump(int p, int step) {
    if (p == root) return p;
    while (step) {
        int t = min(step, dfn[p] - dfn[top[p]]);
        p = rec[dfn[p] - t], step -= t;
        if (!step) break;
        p = fa[p], step--;
    }
    return p;
}
void recalc(int t) {
    if (!lazy[t]) return;
    for (register int i = L[t]; i <= R[t]; i++) a[i] = jump(a[i], lazy[t]);
    lazy[t] = 0;
    return;
}
void rebuild(int t) {
    ans[t] = INF;
    S[t].resize(R[t] - L[t] + 1);
    for (register int i = L[t]; i <= R[t]; i++) S[t][i - L[t]] = a[i], ans[t] = min(ans[t], dist[a[i]]);
    return;
}

int main() {
    n = read<int>(), m = read<int>(), root = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>(), dist = read<int>();
        graph[from].push_back((pii){to, dist}), graph[to].push_back((pii){from, dist});
    }
    dfs1(root), dfs2(root, root), fa[root] = root;
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int blockLen = sqrt(n) * 1.2, blockCnt = n / blockLen;
    for (register int i = 1; i <= blockCnt; i++) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + blockLen;
    if (R[blockCnt] < n) blockCnt++, L[blockCnt] = R[blockCnt - 1] + 1, R[blockCnt] = n;
    for (register int i = 1; i <= blockCnt; i++) {
        for (register int j = L[i]; j <= R[i]; j++) bel[j] = i;
        rebuild(i);
    }
    while (m--) {
        int opt = read<int>(), l = read<int>(), r = read<int>();
        if (opt == 1) {
            if (bel[l] == bel[r]) {
                recalc(bel[l]);
                for (register int i = l; i <= r; i++) a[i] = fa[a[i]];
                rebuild(bel[l]);
            } else {
                recalc(bel[l]);
                for (register int i = l; i <= R[bel[l]]; i++) a[i] = fa[a[i]];
                rebuild(bel[l]);
                for (register int i = bel[l] + 1; i < bel[r]; i++) {
                    lazy[i]++;
                    if (!ans[i]) continue;
                    tail = 0;
                    for (vector<int>::iterator j = S[i].begin(); j != S[i].end(); j++) {
                        *j = fa[*j];
                        ans[i] = min(ans[i], dist[*j]);
                        if (vis[i][*j]) continue;
                        vis[i][*j] = true;
                        cache[++tail] = *j;
                    }
                    S[i].resize(tail);
                    for (register int j = 1; j <= tail; j++) S[i][j - 1] = cache[j];
                }
                recalc(bel[r]);
                for (register int i = L[bel[r]]; i <= r; i++) a[i] = fa[a[i]];
                rebuild(bel[r]);
            }
        } else {
            long long answer = INF;
            if (bel[l] == bel[r]) {
                recalc(bel[l]);
                for (register int i = l; i <= r; i++) answer = min(answer, dist[a[i]]);
                rebuild(bel[l]);
            } else {
                recalc(bel[l]);
                for (register int i = l; i <= R[bel[l]]; i++) answer = min(answer, dist[a[i]]);
                rebuild(bel[l]);
                if (!answer) goto awa;
                for (register int i = bel[l] + 1; i < bel[r]; i++) answer = min(answer, ans[i]);
                if (!answer) goto awa;
                recalc(bel[r]);
                for (register int i = L[bel[r]]; i <= r; i++) answer = min(answer, dist[a[i]]);
                rebuild(bel[r]);
            }
        awa:
            write(answer), putch('\n');
        }
    }
    return 0;
}