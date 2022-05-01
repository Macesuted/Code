/**
 * @file 3323.cpp
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

#define maxn 5005
#define mod 1000000007

typedef pair<int, int> pii;

vector<vector<int>> graph;
int siz[maxn], n, ans[maxn];
long long fac[maxn], ifac[maxn], f[maxn], g[maxn];
vector<int> rec;

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
long long inv(long long a) { return Pow(a, mod - 2); }
long long binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

pii dfs1(int p, int pre = -1) {
    siz[p] = 1;
    pii ans = {numeric_limits<int>::max(), 0};
    int maxS = 0;
    for (auto i : graph[p])
        if (i != pre) ans = min(ans, dfs1(i, p)), siz[p] += siz[i], maxS = max(maxS, siz[i]);
    return min(ans, pii{max(maxS, n - siz[p]), p});
}
void dfs2(int p, int pre = -1) {
    rec.push_back(p), siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre) dfs2(i, p), siz[p] += siz[i];
    return;
}

void solve(void) {
    n = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    int r = dfs1(1).second;
    dfs2(r);
    for (int i = 0; i < n; i++) ans[rec[i]] = rec[(i + n / 2) % n];
    f[0] = 1;
    for (auto i : graph[r]) {
        int x = siz[i];
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= n - i; j++)
                g[i + j] = (g[i + j] + binom(x, i) * binom(x, i) % mod * fac[i] % mod * f[j]) % mod;
        memcpy(f, g, sizeof(f)), memset(g, 0, sizeof(g));
    }
    long long answer = 0;
    for (int i = 0; i <= n; i++) answer = (answer + ((i & 1) ? mod - 1 : 1) * f[i] % mod * fac[n - i]) % mod;
    for (int i = 1; i <= n; i++) write(ans[i]), putch(" \n"[i == n]);
    write(answer), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tanikaze.in", "r", stdin), freopen("tanikaze.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
