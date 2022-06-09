/**
 * @file 191D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

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

#define maxn 100005

vector<int> graph[maxn], tree[maxn << 1];
int n, tn, dfn[maxn], low[maxn];
bool bel[maxn];

stack<int> S;
int dfnt = 0;
void tarjan(int p) {
    dfn[p] = low[p] = ++dfnt, S.push(p);
    for (auto i : graph[p])
        if (!dfn[i]) {
            tarjan(i), low[p] = min(low[p], low[i]);
            if (low[i] == dfn[p]) {
                vector<int> cache;
                while (S.top() != i) cache.push_back(S.top()), S.pop();
                cache.push_back(S.top()), S.pop();
                if (cache.size() == 1)
                    tree[p].push_back(i), tree[i].push_back(p);
                else {
                    tree[p].push_back(++tn), tree[tn].push_back(p), bel[p] = true;
                    for (auto i : cache) tree[tn].push_back(i), tree[i].push_back(tn), bel[i] = true;
                }
            }
        } else
            low[p] = min(low[p], dfn[i]);
    return;
}
int dfs(int p, int pre = -1) {
    int ans = 0, cnt = 0;
    for (auto i : tree[p])
        if (i != pre) ans += dfs(i, p);
    if (p <= n) {
        if (~pre && pre <= n) ans++;
        return ans - ((int)tree[p].size() - bel[p]) / 2;
    }
    for (auto i : tree[p]) cnt += (tree[i].size() >= 2);
    if (cnt < 2) ans++;
    return ans;
}

void solve(void) {
    n = tn = read();
    int m = read();
    for (int i = 1, x, y; i <= m; i++) x = read(), y = read(), graph[x].push_back(y), graph[y].push_back(x);
    tarjan(1), write(dfs(1)), putch(' '), write(m), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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