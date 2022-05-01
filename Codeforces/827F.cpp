/**
 * @file 827F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-03
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/cf827f
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 500005

typedef tuple<int, int, int> tiii;

vector<vector<tiii>> graph;
vector<vector<tiii>::iterator> cur;
int dist[maxn];

void addEdge(int x, int y, int l, int r) {
    return l <= r &&
               (graph[x].emplace_back(l + (l & 1), r - (r & 1), y), graph[y].emplace_back(l + !(l & 1), r - !(r & 1), x), 1),
           void();
}

void solve(void) {
    int n = read(), m = read();
    graph.resize(2 * n + 1), cur.resize(2 * n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read(), y = read(), l = read(), r = read() - 1;
        addEdge(x, y + n, l, r), addEdge(y, x + n, l, r);
    }
    for (int i = 1; i <= 2 * n; i++) sort(cur[i] = graph[i].begin(), graph[i].end());
    memset(dist, 0x3f, sizeof(dist)), dist[1] = 0;
    static priority_queue<tiii, vector<tiii>, greater<tiii>> que;
    while (!que.empty()) que.pop();
    while (cur[1] != graph[1].end() && get<0>(*cur[1]) == 0) que.emplace(1, get<1>(*cur[1]) + 1, get<2>(*cur[1])), cur[1]++;
    while (!que.empty()) {
        auto [l, r, x] = que.top();
        que.pop(), dist[(x - 1) % n + 1] = min(dist[(x - 1) % n + 1], l);
        for (auto& i = cur[x]; i != graph[x].end() && get<0>(*i) <= r; i++)
            if (get<1>(*i) >= l) que.emplace(max(l, get<0>(*i)) + 1, get<1>(*i) + 1, get<2>(*i));
    }
    return write(dist[n] == 0x3f3f3f3f ? -1 : dist[n]), putch('\n');
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
