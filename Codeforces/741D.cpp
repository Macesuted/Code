/**
 * @file 741D.cpp
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

#define maxn 500005
#define maxS (1 << 22)

int a[maxn], record[maxS], son[maxn], siz[maxn], ans[maxn], statu[maxn], dep[maxn];

vector<vector<int>> graph;

void mark(int p, int id) {
    record[statu[p]] = (id == +1) ? max(record[statu[p]], dep[p]) : 0;
    for (auto i : graph[p]) mark(i, id);
    return;
}
void dfs(int p, int root) {
    if (record[statu[p]]) ans[root] = max(ans[root], record[statu[p]] + dep[p] - 2 * dep[root]);
    for (int i = 0; i < 22; i++)
        if (record[statu[p] ^ (1 << i)]) ans[root] = max(ans[root], record[statu[p] ^ (1 << i)] + dep[p] - 2 * dep[root]);
    for (auto i : graph[p]) dfs(i, root);
    return;
}
void dsu(int p) {
    for (auto i : graph[p])
        if (i != son[p]) dsu(i), mark(i, -1), ans[p] = max(ans[p], ans[i]);
    if (son[p]) dsu(son[p]), ans[p] = max(ans[p], ans[son[p]]);
    if (record[statu[p]]) ans[p] = max(ans[p], record[statu[p]] - dep[p]);
    for (int i = 0; i < 22; i++)
        if (record[statu[p] ^ (1 << i)]) ans[p] = max(ans[p], record[statu[p] ^ (1 << i)] - dep[p]);
    record[statu[p]] = max(record[statu[p]], dep[p]);
    for (auto i : graph[p])
        if (i != son[p]) dfs(i, p), mark(i, +1);
    return;
}

void solve(void) {
    int n = read<int>();
    graph.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        graph[read<int>()].push_back(i);
        a[i] = getstr()[0] - 'a';
    }
    statu[1] = 0, dep[1] = 1;
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i]) statu[j] = statu[i] ^ (1 << a[j]), dep[j] = dep[i] + 1;
    for (int i = n; i; i--) {
        siz[i] = 1;
        for (auto j : graph[i]) {
            siz[i] += siz[j];
            if (!son[i] || siz[j] > siz[son[i]]) son[i] = j;
        }
    }
    memset(record, 0xcf, sizeof(record));
    dsu(1);
    for (int i = 1; i <= n; i++) write(ans[i]), putch(" \n"[i == n]);
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << t2 - t1 << "ms" << endl;
    return 0;
}