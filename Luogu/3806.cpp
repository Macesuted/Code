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

#define maxn 10005
#define maxv 10000005

typedef pair<int, int> pii;

vector<vector<pii> > graph;
int f[maxn], siz[maxn];
bool g[maxv];
bool vis[maxn];
deque<int> used;
queue<int> cache;

void calcSize(int p, int fa = -1) {
    siz[p] = 1;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->first != fa && !vis[i->first]) calcSize(i->first, p), siz[p] += siz[i->first];
    return;
}
int root;
int getRoot(int p, int all, int fa = -1) {
    f[p] = 0;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->first != fa && !vis[i->first]) getRoot(i->first, all, p), f[p] = max(f[p], siz[i->first]);
    f[p] = max(f[p], all - siz[p]);
    if (root == 0 || f[p] < f[root]) root = p;
    return root;
}

bool dfs2(int p, int k, int fa = -1, int dist = 0) {
    if (dist > k) return false;
    if (g[k - dist]) return true;
    cache.push(dist);
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->first != fa && !vis[i->first] && dfs2(i->first, k, p, dist + i->second))
            return true;
    return false;
}
bool dfs1(int p, int k) {
    vis[p] = true;
    g[0] = true, used.push_back(0);
    bool check = false;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (!vis[i->first]) {
            check = dfs2(i->first, k, p, i->second);
            if (check) break;
            while (!cache.empty()) {
                int p = cache.front();
                cache.pop();
                if (g[p]) continue;
                g[p] = true, used.push_back(p);
            }
        }
    for (deque<int>::iterator i = used.begin(); i != used.end(); i++) g[*i] = false;
    used.clear();
    if (check) return true;
    for (vector<pii>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (!vis[i->first]) {
            calcSize(i->first), root = 0, getRoot(i->first, siz[i->first]);
            if (dfs1(root, k)) return true;
        }
    return false;
}

int main() {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>(), dist = read<int>();
        graph[from].push_back((pii){to, dist});
        graph[to].push_back((pii){from, dist});
    }
    while (m--) {
        memset(vis, 0, sizeof(vis));
        calcSize(1), root = 0, getRoot(1, siz[1]);
        putstr(dfs1(root, read<int>()) ? "AYE" : "NAY"), putch('\n');
    }
    return 0;
}