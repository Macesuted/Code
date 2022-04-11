/**
 * @file 10058.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-11
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

class UnionSet {
   private:
    int fa[maxn];

   public:
    int siz[maxn];

    void reset(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
        return;
    }
    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    bool merge(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return false;
        return fa[fx] = fy, siz[fy] += siz[fx], true;
    }
} US[5];

vector<pii> edge;
vector<int> graph[maxn];

int choo[4];
bool ali[4], onr[4], vis[maxn];

void solve(void) {
    int n = read(), q = read(), ans = n;
    for (int i = 0; i < 5; i++) US[i].reset(n);
    while (q--) {
        int x = read();
        if (!~x)
            write(ans), putch('\n');
        else {
            int y = read();
            x++, y++, graph[x].push_back(y), graph[y].push_back(x), edge.emplace_back(x, y);
            if (graph[x].size() < graph[y].size()) swap(x, y);
            if (graph[x].size() == 3U) {
                choo[0] = graph[x][0], choo[1] = graph[x][1], choo[2] = graph[x][2], choo[3] = x;
                break;
            }
            if (US[4].merge(x, y)) continue;
            ans = (ans == n ? US[4].siz[US[4].getfa(x)] : 0);
        }
    }
    if (!~q) return;
    for (int i = 0; i < 4; i++) {
        ali[i] = true;
        for (auto j : edge)
            if (ali[i] && j.first != choo[i] && j.second != choo[i] && !US[i].merge(j.first, j.second)) ali[i] = false;
    }
    while (q--) {
        int x = read();
        if (!~x)
            write(ali[0] + ali[1] + ali[2] + ali[3]), putch('\n');
        else {
            int y = read();
            x++, y++, graph[x].push_back(y), graph[y].push_back(x);
            auto check = [&](int x) {
                if (graph[x].size() == 3U) {
                    vis[x] = true;
                    for (auto i : graph[x]) vis[i] = true;
                    for (int i = 0; i < 4; i++) ali[i] &= vis[choo[i]];
                    for (auto i : graph[x]) vis[i] = false;
                    vis[x] = false;
                }
                if (graph[x].size() == 4U)
                    for (int i = 0; i < 4; i++) ali[i] &= (choo[i] == x);
            };
            check(x), check(y);
            for (int i = 0; i < 4; i++)
                if (ali[i] && x != choo[i] && y != choo[i] && !US[i].merge(x, y)) ali[i] = false;
        }
    }
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("rings.in", "r", stdin), freopen("rings.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}