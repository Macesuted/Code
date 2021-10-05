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

vector<vector<int> > graph;
int from[maxn], to[maxn], vis[maxn], dfn[maxn], low[maxn], sign[maxn];

int tim, cnt1, cnt2;
void tarjan(int p) {
    dfn[p] = low[p] = ++tim;
    vis[p] = 1;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (!vis[*i]) {
            tarjan(*i);
            low[p] = min(low[p], low[*i]);
            if (dfn[p] <= low[*i]) vis[p]++;
        } else
            low[p] = min(low[p], dfn[*i]);
    vis[p] = ((p == 1 && vis[p] > 2) || (p != 1 && vis[p] > 1)) ? 2 : 1;
    return;
}
void dfs(int p) {
    vis[p] = 3, cnt2++;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (vis[*i] == 1)
            dfs(*i);
        else if (vis[*i] == 2 && sign[*i] != tim)
            sign[*i] = tim, cnt1++;
    return;
}

int main() {
    int m = read<int>(), test = 0;
    while (m) {
        int n = 0;
        for (register int i = 1; i <= m; i++) from[i] = read<int>(), to[i] = read<int>(), n = max(n, max(from[i], to[i]));
        graph.resize(n + 1);
        for (register int i = 1; i <= m; i++) graph[from[i]].push_back(to[i]), graph[to[i]].push_back(from[i]);
        for (register int i = 1; i <= n; i++) vis[i] = sign[i] = 0;
        tim = 0;
        for (register int i = 1; i <= n; i++)
            if (!vis[i]) tarjan(i);
        tim = 0;
        long long answer1 = 0, answer2 = 1;
        for (register int i = 1; i <= n; i++)
            if (vis[i] == 1) {
                tim++;
                cnt1 = cnt2 = 0;
                dfs(i);
                if (cnt1 == 1) answer1++, answer2 *= cnt2;
            }
        if (!answer1) answer1 = 2, answer2 = 1LL * n * (n - 1) / 2;
        putstr("Case "), write(++test), putstr(": "), write(answer1), putch(' '), write(answer2), putch('\n');
        graph.clear();
        m = read<int>();
    }
    return 0;
}