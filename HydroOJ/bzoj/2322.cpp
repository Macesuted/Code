/**
 * @file 2322.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-05
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

#define maxn 5005
#define maxm 20005
#define maxlgv 61

typedef pair<int, int64_t> pil;
typedef tuple<int, int, int64_t> tiil;

class Base {
   private:
    int64_t a[maxlgv];

   public:
    int siz;

    Base(void) { memset(a, 0, sizeof(a)), siz = 0; }
    bool insert(int64_t v) {
        for (int i = maxlgv - 1; ~i; i--)
            if (v >> i & 1) {
                if (a[i])
                    v ^= a[i];
                else
                    return a[i] = v, siz++, true;
            }
        return false;
    }
    int64_t query(int64_t v) {
        for (int i = maxlgv - 1; ~i; i--)
            if ((v >> i & 1) && a[i]) v ^= a[i];
        return v;
    }
} base;

tiil edges[maxm];
bool era[maxm], vis[maxn];
int ques[maxm];
int64_t dep[maxn], ans[maxm];
vector<vector<pil>> graph;
set<int64_t> S, T;

void insert(int64_t v) {
    if (!base.insert(v)) return;
    T = S, S.clear();
    for (auto i : T) S.insert(base.query(i));
    return T.clear();
}
void dfs(int p) {
    if (!vis[p]) S.insert(base.query(dep[p]));
    vis[p] = true;
    for (auto i : graph[p])
        if (!vis[i.first])
            dep[i.first] = dep[p] ^ i.second, dfs(i.first);
        else
            insert(dep[i.first] ^ dep[p] ^ i.second);
    return;
}

void solve(void) {
    int n = read(), m = read(), q = read();
    for (int i = 1; i <= m; i++)
        get<0>(edges[i]) = read(), get<1>(edges[i]) = read(), get<2>(edges[i]) = read<int64_t>();
    for (int i = 1; i <= q; i++) era[ques[i] = read()] = true;
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++)
        if (!era[i])
            graph[get<0>(edges[i])].emplace_back(get<1>(edges[i]), get<2>(edges[i])),
                graph[get<1>(edges[i])].emplace_back(get<0>(edges[i]), get<2>(edges[i]));
    S.insert(0), dfs(1);
    ans[q + 1] = (int64_t)S.size() << base.siz;
    for (int i = q; i; i--) {
        int x, y;
        int64_t d;
        tie(x, y, d) = edges[ques[i]];
        graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
        if (vis[x] && !vis[y])
            dfs(x);
        else if (!vis[x] && vis[y])
            dfs(y);
        else if (vis[x] && vis[y])
            insert(dep[x] ^ dep[y] ^ d);
        ans[i] = (int64_t)S.size() << base.siz;
    }
    for (int i = 1; i <= q + 1; i++) write(ans[i] - 1), putch('\n');
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
