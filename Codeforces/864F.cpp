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

#define maxn 3005
#define maxlgn 15
#define maxq 400005

struct Ask {
    int to, k, id;
};

vector<vector<int> > graph;
vector<vector<Ask> > ask;

bool vis[maxn], inDfs[maxn], use[maxn];
int fa[maxn][maxlgn], dep[maxn];
int answer[maxq];
int ct[maxn];
int loop;

void dfs(int p) {
    if (!loop) use[p] = true;
    inDfs[p] = true;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
        if (inDfs[*i]) {
            ct[*i]++, loop++;
            continue;
        }
        if (vis[*i]) continue;
        fa[*i][0] = p;
        dep[*i] = dep[p] + 1, dfs(*i);
    }
    vis[p] = true;
    loop -= ct[p], ct[p] = 0;
    return inDfs[p] = false, void();
}
int jump(int p, int k) {
    for (register int i = maxlgn - 1; ~i; i--)
        if (k >> i & 1) p = fa[p][i];
    return p;
}

int main() {
    int n = read<int>(), m = read<int>(), q = read<int>();
    graph.resize(n + 1), ask.resize(n + 1);
    for (register int i = 1, from, to; i <= m; i++) from = read<int>(), to = read<int>(), graph[from].push_back(to);
    for (register int i = 1; i <= n; i++) sort(graph[i].begin(), graph[i].end());
    for (register int i = 1; i <= q; i++) {
        int from = read<int>(), to = read<int>(), k = read<int>();
        ask[from].push_back((Ask){to, k, i});
    }
    for (register int i = 1; i <= n; i++) {
        loop = 0;
        memset(fa, 0, sizeof(fa)), memset(dep, 0, sizeof(dep)), memset(ct, 0, sizeof(ct));
        memset(vis, 0, sizeof(vis)), memset(inDfs, 0, sizeof(inDfs)), memset(use, 0, sizeof(use));
        fa[i][0] = 0, dep[i] = 1;
        dfs(i);
        for (vector<Ask>::iterator j = ask[i].begin(); j != ask[i].end(); j++)
            answer[j->id] = (use[j->to] && (j->k <= dep[j->to])) ? jump(j->to, dep[j->to] - j->k) : -1;
    }
    for (register int i = 1; i <= q; i++) write(answer[i]), putch('\n');
    return 0;
}