/**
 * @file 1391E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-31
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

typedef pair<int, int> pii;

vector<vector<int>> graph;

int dfni[maxn], dfno[maxn], fa[maxn], dep[maxn];
bool vis[maxn];
vector<int> record[maxn];

int tim;

void dfs(int p) {
    vis[p] = true;
    dfni[p] = ++tim;
    for (auto i : graph[p])
        if (!vis[i]) fa[i] = p, dep[i] = dep[p] + 1, dfs(i);
    dfno[p] = tim;
    return;
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) vis[i] = false;
    tim = 0, dep[1] = 1, dfs(1);
    int maxDep = 1;
    for (int i = 1; i <= n; i++) maxDep = max(maxDep, dep[i]);
    if (maxDep * 2 >= n) {
        int p = 0;
        for (int i = 1; i <= n; i++)
            if (dep[i] == maxDep) {
                p = i;
                break;
            }
        putstr("PATH\n");
        write(dep[p]), putch('\n');
        while (p) write(p), putch(' '), p = fa[p];
        putch('\n');
    } else {
        static queue<pii> answer;
        while (!answer.empty()) answer.pop();
        for (int i = 1; i <= n; i++) record[dep[i]].push_back(i);
        for (int i = 1; i <= n; i++) {
            while (record[i].size() > 1) {
                int p = record[i].back();
                record[i].pop_back();
                int q = record[i].back();
                record[i].pop_back();
                answer.emplace(p, q);
            }
            record[i].clear();
        }
        putstr("PAIRING\n");
        write((int)answer.size()), putch('\n');
        while (!answer.empty()) write(answer.front().first), putch(' '), write(answer.front().second), putch('\n'), answer.pop();
    }
    graph.clear();
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = read<int>();
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}