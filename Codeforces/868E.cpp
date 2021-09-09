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

#define maxn 55
#define maxm 105

struct Edge {
    int to, dist, id, rev;
};

int f[maxn][maxm][maxn], siz[maxn];

vector<vector<Edge> > graph;

void dfs(int p, int pre = -1) {
    for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->to != pre) dfs(i->to, p), siz[p] += siz[i->to];
    return;
}

int F(int n, Edge* edge, int k) {
    if (k == 0) return 0;
    if (f[n][edge->id][k]) return f[n][edge->id][k];
    int p = edge->to;
    if ((int)graph[p].size() == 1) return f[n][edge->id][k] = edge->dist + F(n - k, &graph[p][edge->rev], n - k);
    int g[maxn];
    memset(g, 0, sizeof(g));
    g[0] = 0x3f3f3f3f;
    for (vector<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->id != (edge->id ^ 1))
            for (register int j = k; j; j--)
                for (register int s = j; ~s; s--)
                    g[j] = max(g[j], min(g[j - s], F(n, &*i, s)));
    return f[n][edge->id][k] = edge->dist + g[k];
}

int main() {
    int n = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), d = read<int>();
        graph[x].push_back((Edge){y, d, 2 * i - 2, (int)graph[y].size()});
        graph[y].push_back((Edge){x, d, 2 * i - 1, (int)graph[x].size() - 1});
    }
    int root = read<int>(), m = read<int>();
    for (register int i = 1; i <= m; i++) siz[read<int>()]++;
    dfs(root);
    int answer = 0x3f3f3f3f;
    for (vector<Edge>::iterator i = graph[root].begin(); i != graph[root].end(); i++)
        if (siz[i->to]) answer = min(answer, F(m, &*i, siz[i->to]));
    write(answer), putch('\n');
    return 0;
}