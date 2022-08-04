/**
 * @file 1616G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-22
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/cf1616g
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

#define maxn 150005

bool cons[maxn], vis[2][maxn * 2];

vector<vector<int>> graph, g, gr;

void dfs(int p, vector<vector<int>>& graph, int id) {
    vis[id][p] = true;
    for (auto i : graph[p])
        if (!vis[id][i]) dfs(i, graph, id);
    return;
}

void solve(void) {
    int n = read<int>() + 2, m = read<int>();
    graph.clear(), g.clear(), gr.clear(), graph.resize(n + 1), g.resize(2 * n + 1), gr.resize(2 * n + 1);
    for (int i = 1; i <= n; i++) cons[i] = false, vis[0][i] = vis[1][i] = vis[0][n + i] = vis[1][n + i] = false;
    for (int i = 3; i < n; i++) graph[1].push_back(i), graph[i - 1].push_back(n);
    cons[1] = cons[n - 1] = true;
    for (int i = 1; i <= m; i++) {
        int x = read<int>() + 1, y = read<int>() + 1;
        if (x + 1 == y)
            cons[x] = true;
        else
            graph[x].push_back(y);
    }
    int p = 0, l = 0, r = 0;
    for (int i = 1; i < n; i++)
        if (!cons[i]) {
            if (!p) p = l = i;
            r = i;
        }
    if (p == 0) return write(1LL * (n - 2) * (n - 3) / 2), putch('\n');
    for (int i = n, r = n; i > 1; i--) {
        if (!cons[i]) r = i;
        for (auto j : graph[i - 1])
            if (j <= r + 1)
                g[i - 1].push_back(n + j), g[n + i].push_back(j - 1), gr[n + j].push_back(i - 1),
                    gr[j - 1].push_back(n + i);
    }
    dfs(p, g, 0), dfs(p, gr, 0), dfs(n + p + 1, g, 1), dfs(n + p + 1, gr, 1);
    long long ans = 0, cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= l; i++) cnt1 += vis[0][i];
    for (int i = r; i < n; i++) cnt2 += vis[0][i];
    ans += cnt1 * cnt2, cnt1 = cnt2 = 0;
    for (int i = 1; i <= l; i++) cnt1 += vis[1][i];
    for (int i = r; i < n; i++) cnt2 += vis[1][i];
    ans += cnt1 * cnt2, cnt1 = cnt2 = 0;
    for (int i = 1; i <= l; i++) cnt1 += (vis[0][i] & vis[1][i]);
    for (int i = r; i < n; i++) cnt2 += (vis[0][i] & vis[1][i]);
    ans -= cnt1 * cnt2;
    return write(ans - (l == r)), putch('\n');
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
