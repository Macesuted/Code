/**
 * @file 100712H.cpp
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

#define maxn 100005

typedef pair<int, int> pii;

vector<vector<int>> graph, tree;

int dfn[maxn], low[maxn], bel[maxn];
bool inStack[maxn];
stack<int> S;

int tim = 0;
void tarjan(int p, int pre = -1) {
    dfn[p] = low[p] = ++tim;
    S.push(p), inStack[p] = true;
    for (auto i : graph[p])
        if (!dfn[i])
            tarjan(i, p), low[p] = min(low[p], low[i]);
        else if (i != pre && inStack[i])
            low[p] = min(low[p], dfn[i]);
    if (low[p] == dfn[p]) {
        while (S.top() != p) bel[S.top()] = p, inStack[S.top()] = false, S.pop();
        bel[p] = p, inStack[p] = false, S.pop();
    }
    return;
}
pii dfs(int p, int pre = -1) {
    pii ans = {0, p};
    for (auto i : tree[p])
        if (i != pre) ans = max(ans, dfs(i, p));
    return {ans.first + 1, ans.second};
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1), tree.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) {
        x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) dfn[i] = 0, inStack[i] = false;
    tarjan(1);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (bel[i] == i) cnt++;
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (i < j && bel[i] != bel[j]) tree[bel[i]].push_back(bel[j]), tree[bel[j]].push_back(bel[i]);
    write(cnt - dfs(dfs(1).second).first), putch('\n');
    graph.clear(), tree.clear();
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = read<int>();
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << t2 - t1 << "ms" << endl;
    return 0;
}