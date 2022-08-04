/**
 * @file 2737.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-31
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

int fa[maxn], indeg[maxn];
int64_t d[maxn], f[maxn], hson[maxn], g[maxn][2];

void solve(void) {
    int n = read();
    for (int i = 1; i <= n; i++) indeg[fa[i] = read()]++, d[i] = read();
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        f[p] += d[p] - hson[p], hson[fa[p]] = max(hson[fa[p]], d[p]), f[fa[p]] += f[p];
        if (!--indeg[fa[p]]) que.push(fa[p]);
    }
    int64_t answer = 0;
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) continue;
        static vector<int> ring;
        ring.clear(), ring.push_back(i);
        int p = fa[i];
        while (p != i) ring.push_back(p), p = fa[p];
        for (auto i : ring) indeg[i] = 0, f[i] += d[i];
        int tn = ring.size();
        g[0][0] = f[p] - d[ring.back()], g[0][1] = f[p] - hson[p];
        for (int i = 1; i < tn; i++)
            g[i][0] = g[i - 1][0] + f[ring[i]] - d[ring[i - 1]],
            g[i][1] = min(min(g[i - 1][0], g[i - 1][1]) + f[ring[i]] - hson[ring[i]],
                          g[i - 1][1] + f[ring[i]] - d[ring[i - 1]]);
        answer += g[tn - 1][(int)ring.size() != n];
    }
    return write(answer), putch('\n');
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
