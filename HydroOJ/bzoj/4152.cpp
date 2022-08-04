/**
 * @file 4152.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-04
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

#define maxn 200005

typedef pair<int, int> pii;

struct Node {
    int x, y, id;
};

Node a[maxn];
int dist[maxn];
bool vis[maxn];

vector<vector<pii>> graph;

void solve(void) {
    int n = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) a[i].x = read<int>(), a[i].y = read<int>(), a[i].id = i;
    sort(a + 1, a + n + 1, [](Node a, Node b) { return a.x < b.x; });
    for (int i = 1; i < n; i++)
        graph[a[i].id].emplace_back(a[i + 1].id, a[i + 1].x - a[i].x),
            graph[a[i + 1].id].emplace_back(a[i].id, a[i + 1].x - a[i].x);
    sort(a + 1, a + n + 1, [](Node a, Node b) { return a.y < b.y; });
    for (int i = 1; i < n; i++)
        graph[a[i].id].emplace_back(a[i + 1].id, a[i + 1].y - a[i].y),
            graph[a[i + 1].id].emplace_back(a[i].id, a[i + 1].y - a[i].y);
    static priority_queue<pii, vector<pii>, greater<pii>> que;
    while (!que.empty()) que.pop();
    memset(dist, 0x3f, sizeof(dist));
    que.emplace(dist[1] = 0, 1);
    while (!que.empty()) {
        int p = que.top().second;
        que.pop();
        if (vis[p]) continue;
        vis[p] = true;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) que.emplace(dist[i.first] = dist[p] + i.second, i.first);
    }
    write(dist[n]), putch('\n');
    return;
}

bool mem2;

int main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}