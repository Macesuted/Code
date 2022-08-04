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

#define maxn 1000005

typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<pii> edges;

int fa[maxn], dep[maxn];
int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void dfs(int p) {
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (!dep[*i]) dep[*i] = dep[p] + 1, dfs(*i);
    return;
}

bool even[maxn];
int val[2][maxn], col[2][maxn];
vector<int> roots;
multiset<int> S[2][2], T[2];

void dfs2(int p, int fa = -1) {
    S[0][col[0][p]].insert(val[0][p]), S[1][col[1][p]].insert(val[1][p]);
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != fa) dfs2(*i, p);
    return;
}

bool work(void) {
    edges.clear(), graph.clear(), roots.clear();
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) fa[i] = i, dep[i] = 0, even[i] = false;
    graph.resize(n + 1);
    for (register int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        if (getfa(x) == getfa(y))
            edges.push_back((pii){x, y});
        else {
            graph[x].push_back(y), graph[y].push_back(x);
            fa[getfa(x)] = getfa(y);
        }
    }
    for (register int i = 1; i <= n; i++)
        if (!dep[i]) dep[i] = 1, dfs(i), roots.push_back(i);
    for (register int i = 1; i <= n; i++) val[0][i] = read<int>();
    for (register int i = 1; i <= n; i++) {
        char c = getch();
        while (c != 'R' && c != 'B') c = getch();
        col[0][i] = ((c == 'R') ^ (dep[i] & 1));
    }
    for (register int i = 1; i <= n; i++) val[1][i] = read<int>();
    for (register int i = 1; i <= n; i++) {
        char c = getch();
        while (c != 'R' && c != 'B') c = getch();
        col[1][i] = ((c == 'R') ^ (dep[i] & 1));
    }
    for (vector<pii>::iterator i = edges.begin(); i != edges.end(); i++)
        if ((dep[i->first] & 1) == (dep[i->second] & 1)) even[getfa(i->first)] = true;
    for (vector<int>::iterator root = roots.begin(); root != roots.end(); root++) {
        S[0][0].clear(), S[0][1].clear(), S[1][0].clear(), S[1][1].clear();
        dfs2(*root);
        T[0].clear(), T[1].clear();
        for (register int x = 0; x < 2; x++)
            for (register int y = 0; y < 2; y++)
                for (multiset<int>::iterator i = S[x][y].begin(); i != S[x][y].end(); i++) T[x].insert(*i);
        while (T[0].size()) {
            if (*T[0].begin() != *T[1].begin()) return false;
            T[0].erase(T[0].begin()), T[1].erase(T[1].begin());
        }
        if (S[0][0].size() != S[1][0].size() && !even[getfa(*root)]) return false;
        if (abs((int)S[0][0].size() - (int)S[1][0].size()) % 2 == 1 && even[getfa(*root)]) return false;
        if (even[getfa(*root)]) continue;
        int cnt = 0;
        for (multiset<int>::iterator i = S[0][0].begin(); i != S[0][0].end(); i++)
            if (S[1][0].find(*i) == S[1][0].end())
                return false;
            else
                S[1][0].erase(S[1][0].find(*i));
    }
    return true;
}

int main() {
    int _ = read<int>();
    while (_--) putstr(work() ? "YES" : "NO"), putch('\n');
    return 0;
}