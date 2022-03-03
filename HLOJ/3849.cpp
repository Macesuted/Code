/**
 * @file 3849.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-03
 *
 * @copyright Copyright (c) 2022
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

typedef pair<int, int> pii;

bool mem1;

vector<vector<int>> graph;
vector<int> col;

void dfs(int p, int c) {
    col[p] = c;
    for (auto i : graph[p])
        if (!col[i]) dfs(i, 3 - c);
    return;
}

void solve(void) {
    int n = read<int>();
    graph.resize(2 * n + 1), col.resize(2 * n + 1);
    vector<pii> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].first = read<int>(), a[i].second = read<int>();
        graph[a[i].first].push_back(a[i].second), graph[a[i].second].push_back(a[i].first);
    }
    for (int i = 1; i <= 2 * n; i += 2) graph[i].push_back(i + 1), graph[i + 1].push_back(i);
    for (int i = 1; i <= 2 * n; i++)
        if (!col[i]) dfs(i, 2);
    for (int i = 1; i <= 2 * n; i++) putch("XY"[col[i] - 1]);
    putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}