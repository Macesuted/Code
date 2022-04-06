/**
 * @file 102803E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-06
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

#define maxn 5005

typedef pair<int, int> pii;

int sa[maxn], rk[maxn], h[maxn], fa[maxn];
bool vis[maxn];
char a[maxn];
vector<vector<pii>> graph;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n = read();
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) rk[sa[i] = read()] = fa[i] = i;
    for (int i = 1; i < n; i++) h[i] = read();
    for (int i = 1, j = 0; i <= n; i++) {
        if (j) j--;
        if (rk[i] == n) continue;
        while (j < h[rk[i]]) fa[getfa(i + j)] = getfa(sa[rk[i] + 1] + j), j++;
    }
    for (int i = 1; i < n; i++) {
        if (getfa(sa[i]) != getfa(sa[i + 1]))
            graph[getfa(sa[i])].emplace_back(getfa(sa[i + 1]), rk[sa[i] + 1] > rk[sa[i + 1] + 1]);
        if (h[i] != -1 && sa[i] + h[i] <= n && sa[i + 1] + h[i] <= n)
            graph[getfa(sa[i] + h[i])].emplace_back(getfa(sa[i + 1] + h[i]), 1);
    }
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; i++)
        if (getfa(i) == i) que.push(i), a[i] = 'a', vis[i] = true;
    while (!que.empty()) {
        int p = que.front();
        que.pop(), vis[p] = false;
        for (auto i : graph[p])
            if (a[i.first] < a[p] + i.second) {
                a[i.first] = a[p] + i.second;
                if (!vis[i.first]) que.push(i.first), vis[i.first] = true;
            }
    }
    for (int i = 1; i <= n; i++) putch(a[getfa(i)]);
    putch('\n');
    return;
}

bool mem2;

int main() {
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
