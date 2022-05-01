/**
 * @file grid.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-07
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

#define maxc 100005

typedef pair<int, int> pii;

const pii way4[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n, m;
pii a[maxc];
set<pii> spe, S, vis;
map<pii, int> dfn, low;
vector<set<pii>> nodes;

bool inMap(pii x) { return 1 <= x.first && x.first <= n && 1 <= x.second && x.second <= m; }

void dfs1(pii x, int d) {
    vis.insert(x), S.insert(x);
    for (int i = x.first - d; i <= x.first + d; i++)
        for (int j = x.second - d; j <= x.second + d; j++) {
            pii t = {i, j};
            if (spe.find(t) != spe.end() && vis.find(t) == vis.end()) dfs1(t, d);
        }
    return;
}
void dfs2(pii x) {
    vis.insert(x);
    for (int i = 0; i < 4; i++) {
        pii t = {x.first + way4[i].first, x.second + way4[i].second};
        if (S.find(t) != S.end() && vis.find(t) == vis.end()) dfs2(t);
    }
    return;
}
int dfnt;
bool tarjan(pii x, pii pre = {-1, -1}) {
    dfn[x] = low[x] = ++dfnt;
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        pii t = {x.first + way4[i].first, x.second + way4[i].second};
        if (S.find(t) == S.end()) continue;
        if (dfn.find(t) == dfn.end()) {
            if (tarjan(t, x)) return true;
            cnt++, low[x] = min(low[x], low[t]);
            if (pre != pii{-1, -1} && low[t] >= dfn[x]) return true;
        } else if (t != pre)
            low[x] = min(low[x], dfn[t]);
    }
    return pre == pii{-1, -1} && cnt > 1;
}

void solve(void) {
    n = read(), m = read();
    int c = read();
    spe.clear(), S.clear(), vis.clear(), dfn.clear(), low.clear(), nodes.clear();
    for (int i = 1; i <= c; i++) a[i].first = read(), a[i].second = read(), spe.insert(a[i]);
    if (1LL * n * m - c <= 1) return putstr("-1\n");
    if (1LL * n * m - c == 2) {
        S.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) S.emplace(i, j);
        for (int i = 1; i <= c; i++) S.erase(a[i]);
        pii x = *S.begin(), y = *S.rbegin();
        if (min(abs(x.first - y.first), abs(x.second - y.second)) == 0 &&
            max(abs(x.first - y.first), abs(x.second - y.second)) == 1)
            return putstr("-1\n");
    }
    for (int i = 1; i <= c; i++)
        if (vis.find(a[i]) == vis.end()) dfs1(a[i], 1), nodes.push_back(S), S.clear();
    vis.clear();
    for (auto V : nodes) {
        for (auto i : V)
            for (int x = i.first - 1; x <= i.first + 1; x++)
                for (int y = i.second - 1; y <= i.second + 1; y++) {
                    pii t = {x, y};
                    if (inMap(t) && spe.find(t) == spe.end()) S.insert(t);
                }
        if (S.empty()) continue;
        dfs2(*S.begin());
        if (vis.size() != S.size()) return putstr("0\n");
        vis.clear(), S.clear();
    }
    if (n == 1 || m == 1) return putstr("1\n");
    nodes.clear();
    for (int i = 1; i <= c; i++)
        if (vis.find(a[i]) == vis.end()) dfs1(a[i], 2), nodes.push_back(S), S.clear();
    for (auto V : nodes) {
        for (auto i : V)
            for (int x = i.first - 2; x <= i.first + 2; x++)
                for (int y = i.second - 2; y <= i.second + 2; y++) {
                    pii t = {x, y};
                    if (inMap(t) && spe.find(t) == spe.end()) S.insert(t);
                }
        if (S.empty()) continue;
        dfnt = 0;
        if (tarjan(*S.begin())) return putstr("1\n");
        dfn.clear(), low.clear(), vis.clear(), S.clear();
    }
    return putstr("2\n");
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}