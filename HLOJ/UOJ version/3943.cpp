/**
 * @file 3943.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-24
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

#define maxn 200005

typedef pair<int, int> pii;

vector<int> graph[maxn];
int a[maxn], pos[maxn], v[maxn], siz[maxn], child[maxn];
set<pii> S;
int64_t sum = 0;

void insert(int p) {
    auto calc = [](pii x) { return int64_t(x.second - x.first + 2) * (x.second - x.first + 1) / 2; };
    int l = p, r = p;
    auto x = S.lower_bound({l, r});
    if (x != S.begin() && (--x)->second == p - 1) sum -= calc(*x), l = x->first, S.erase(x);
    x = S.lower_bound({l, r});
    if (x != S.end() && x->first == p + 1) sum -= calc(*x), r = x->second, S.erase(x);
    sum += calc({l, r}), S.emplace(l, r);
    return;
}
void dfs1(int p) {
    siz[p] = 1;
    for (auto i : graph[p]) {
        dfs1(i), siz[p] += siz[i];
        if (!child[p] || siz[child[p]] < siz[i]) child[p] = i;
    }
    return;
}
void add(int p) {
    insert(pos[p]);
    for (auto i : graph[p]) add(i);
    return;
}
int64_t dfs2(int p, int fa = 0) {
    int64_t ans = 0;
    for (auto i : graph[p])
        if (i != child[p]) ans += dfs2(i, p), S.clear(), sum = 0;
    if (child[p]) ans += dfs2(child[p], p);
    for (auto i : graph[p])
        if (i != child[p]) add(i);
    insert(pos[p]);
    return ans + (int64_t)(v[p] - v[fa]) * sum;
}

void solve(void) {
    int n = read();
    for (int i = 2; i <= n; i++) graph[read()].push_back(i);
    for (int i = 1; i <= n; i++) pos[a[i] = read()] = i;
    for (int i = 1; i <= n; i++) v[i] = read();
    dfs1(1);
    cout << dfs2(1) << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("sagittarius.in", "r", stdin), freopen("sagittarius.out", "w", stdout);
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
