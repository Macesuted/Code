/**
 * @file 3061.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
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

#define maxn 1000005

typedef pair<int, int> pii;

vector<vector<int>> graph;
vector<pii> ans, cache;
int fa[maxn];
bool robot[maxn], vis[maxn], inr[maxn];

void dfs(int p, int dep = 0) {
    vis[p] = true;
    if (robot[p]) cache.emplace_back(p, dep);
    for (auto i : graph[p])
        if (!inr[i]) dfs(i, dep + 1);
    return;
}

void solve(void) {
    int r = read(), c = read(), g = read(), n = r * c;
    graph.resize(n + 1);
    auto turn = [&](int x, int y) { return (x - 1) * c + y; };
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) {
            char c = getch();
            while (IO::isspace(c)) c = getch();
            if (c == 'n' || c == 'N') graph[fa[turn(i, j)] = turn(i - 1, j)].push_back(turn(i, j));
            if (c == 's' || c == 'S') graph[fa[turn(i, j)] = turn(i + 1, j)].push_back(turn(i, j));
            if (c == 'w' || c == 'W') graph[fa[turn(i, j)] = turn(i, j - 1)].push_back(turn(i, j));
            if (c == 'e' || c == 'E') graph[fa[turn(i, j)] = turn(i, j + 1)].push_back(turn(i, j));
            if ('A' <= c && c <= 'Z') robot[turn(i, j)] = true;
        }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        deque<int> ring;
        int p = i;
        while (!inr[p]) inr[p] = true, ring.push_back(p), p = fa[p];
        while (ring.front() != p) inr[ring.front()] = false, ring.pop_front();
        int base = n - 1, cnt = 0;
        for (auto i : ring) {
            cache.clear(), dfs(i), base++;
            while (!cache.empty() && cnt < (int)ring.size())
                ans.emplace_back(cache.back().first, base + cnt++ - cache.back().second), cache.pop_back();
        }
    }
    write(ans.size()), putch('\n');
    if (!g) return;
    for (auto i : ans)
        write((i.first - 1) / c + 1), putch(' '), write((i.first - 1) % c + 1), putch(' '), write(i.second), putch('\n');
    return;
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