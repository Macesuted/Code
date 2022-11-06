/**
 * @file 2201.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-27
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
    __int128 fx = x;
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

#define maxn 100005
#define maxlgn 20

struct Info {
    int sumX, sumY, sumXX, sumYY, sumXY, len;
    Info(void) : sumX(0), sumY(0), sumXX(0), sumYY(0), sumXY(0), len(0) {}
    Info(int X, int Y) : sumX(X), sumY(Y), sumXX(X * X), sumYY(Y * Y), sumXY(X * Y), len(1) {}
    Info(int sumX_, int sumY_, int sumXX_, int sumYY_, int sumXY_, int len_)
        : sumX(sumX_), sumY(sumY_), sumXX(sumXX_), sumYY(sumYY_), sumXY(sumXY_), len(len_) {}
    Info operator+(const Info& o) const {
        return Info{sumX + o.sumX, sumY + o.sumY, sumXX + o.sumXX, sumYY + o.sumYY, sumXY + o.sumXY, len + o.len};
    }
    Info operator-(const Info& o) const {
        return Info{sumX - o.sumX, sumY - o.sumY, sumXX - o.sumXX, sumYY - o.sumYY, sumXY - o.sumXY, len - o.len};
    }
    double calc(void) const {
        double A = sumXX - 1. * sumX * sumX / len, B = 2. * sumX * sumY / len - 2 * sumXY, C = sumYY - 1. * sumY * sumY / len;
        return (A + C - sqrt((A - C) * (A - C) + B * B)) / 2;
    }
};

vector<int> ring;
int X[maxn], Y[maxn], in[maxn], fa[maxn][maxlgn], dep[maxn], id[maxn];
bool vis[maxn];
Info inf[maxn][maxlgn], pre[maxn], suf[maxn];

vector<vector<int>> graph;

stack<int> S;
bool dfs1(int p, int pre = -1) {
    vis[p] = true, S.push(p);
    for (auto i : graph[p]) {
        if (i == pre) continue;
        if (vis[i]) {
            while (S.top() != i) ring.push_back(S.top()), S.pop();
            ring.push_back(i);
            return true;
        } else if (dfs1(i, p))
            return true;
    }
    vis[p] = false, S.pop();
    return false;
}
void dfs2(int p, int top, int pre = 0) {
    dep[p] = dep[pre] + 1, fa[p][0] = pre, inf[p][0] = Info(X[p], Y[p]);
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1], inf[p][i] = inf[p][i - 1] + inf[fa[p][i - 1]][i - 1];
    in[p] = top;
    for (auto i : graph[p])
        if (i != pre && !vis[i]) dfs2(i, top, p);
    return;
}
Info path(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    Info ans;
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) ans = ans + inf[x][i], x = fa[x][i];
    if (x == y) return ans + Info(X[x], Y[x]);
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) ans = ans + inf[x][i] + inf[y][i], x = fa[x][i], y = fa[y][i];
    return ans + inf[x][0] + inf[y][0] + Info(X[fa[x][0]], Y[fa[x][0]]);
}

void solve(void) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) X[i] = read(), Y[i] = read();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read(), y = read();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    if (n == m) {
        dfs1(1);
        for (int i = 1; i <= n; i++) vis[i] = false;
        for (int i = 0; i < (int)ring.size(); i++) vis[ring[i]] = true, id[ring[i]] = i + 1;
        for (auto i : ring) dfs2(i, i);
        for (int i = 1; i <= (int)ring.size(); i++) pre[i] = pre[i - 1] + Info(X[ring[i - 1]], Y[ring[i - 1]]);
        for (int i = (int)ring.size(); i; i--) suf[i] = Info(X[ring[i - 1]], Y[ring[i - 1]]) + suf[i + 1];
    } else
        dfs2(1, 1);
    int q = read();
    while (q--) {
        int x = read(), y = read();
        if (in[x] == in[y])
            writeDouble(path(x, y).calc());
        else {
            int px = id[in[x]], py = id[in[y]];
            if (px > py) swap(px, py);
            writeDouble(min((path(x, in[x]) + pre[py - 1] - pre[px] + path(y, in[y])).calc(),
                            (path(x, in[x]) + pre[px - 1] + suf[py + 1] + path(y, in[y])).calc()));
        }
        putch('\n');
    }
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
