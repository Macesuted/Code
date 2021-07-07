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

#define maxn 100005
#define maxlgn 20

int dfn[maxn], fa[maxn][maxlgn], dep[maxn];
bool choose[maxn], rest[maxn];

vector<vector<int> > graph, virt;

int tim = 0;
void dfs1(int p, int pre = 0) {
    dfn[p] = ++tim;
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs1(*i, p);
    return;
}
bool check;
int dfs2(int p) {
    rest[p] = choose[p];
    int ans = 0, cnt = 0;
    for (vector<int>::iterator i = virt[p].begin(); i != virt[p].end(); i++) {
        ans += dfs2(*i), cnt += rest[*i];
        if (choose[p] && choose[*i] && dep[p] + 1 == dep[*i]) check = true;
    }
    if (choose[p])
        ans += cnt;
    else if (cnt > 1)
        rest[p] = false, ans++;
    else if (cnt == 1)
        rest[p] = true;
    return ans;
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

inline bool cmp(int x, int y) { return dfn[x] < dfn[y]; }

int main() {
    int n = read<int>();
    graph.resize(n + 1), virt.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs1(1);
    int q = read<int>();
    while (q--) {
        int k = read<int>();
        static vector<int> nodes;
        nodes.clear();
        for (register int i = 1, p; i <= k; i++) nodes.push_back(p = read<int>()), choose[p] = true;
        sort(nodes.begin(), nodes.end(), cmp);
        static deque<int> S;
        S.clear(), S.push_front(1), virt[1].clear();
        for (vector<int>::iterator i = nodes.begin(); i != nodes.end(); i++) {
            if (*i == 1) continue;
            int p = lca(S[0], *i);
            if (p != S[0]) {
                while (dfn[p] < dfn[S[1]]) virt[S[1]].push_back(S[0]), S.pop_front();
                if (p != S[1]) virt[p].clear();
                virt[p].push_back(S[0]), S.pop_front();
                if (p != S[0]) S.push_front(p);
            }
            S.push_front(*i), virt[*i].clear();
        }
        while (S.size() > 1) virt[S[1]].push_back(S[0]), S.pop_front();
        check = false;
        int ret = dfs2(1);
        write(check ? -1 : ret), putch('\n');
        for (vector<int>::iterator i = nodes.begin(); i != nodes.end(); i++) choose[*i] = false;
    }
    return 0;
}