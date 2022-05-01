/**
 * @file 2462.cpp
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

#define maxn 65
#define maxm 10005
#define mod 11920928955078125
#define phi 9536743164062500

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef pair<int64_t, int64_t> pll;
typedef __int128_t int128_t;

class Poly {
   private:
    int128_t a[23];

   public:
    Poly(int128_t a0 = 0, int128_t a1 = 0) { memset(a, 0, sizeof(a)), a[0] = a0, a[1] = a1; }

    int128_t& operator[](size_t x) { return a[x]; }
    Poly operator*(const Poly& o) const {
        Poly ans;
        for (int i = 0; i < 23; i++)
            for (int j = 0; i + j < 23; j++) ans[i + j] = (ans[i + j] + this->get(i) * o.get(j)) % mod;
        return ans;
    }
    int128_t operator()(int128_t v) const {
        int128_t ans = 0, pv = 1;
        for (int i = 0; i < 23; i++) ans = (ans + pv * this->get(i)) % mod, pv = pv * v % mod;
        return ans;
    }
    int128_t get(size_t x) const { return a[x]; }
};

int w[maxn], v[maxn], dfni[maxn], dfno[maxn], id[maxn], binom[23][23];
tiii edges[maxn];
pll f[maxn][maxm], g[maxm];
vector<pii> graph[maxn];
map<int64_t, pll> FAC;

int M, K;
int64_t MAX;

int128_t Pow(int128_t a, int128_t x) {
    int128_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int128_t Inv(int128_t x) { return Pow(x, phi - 1); }

Poly delt(Poly f, int64_t d) {
    Poly ans;
    int128_t dd = 1;
    for (int i = 0; i < 23; i++, dd = 1)
        for (int j = i; j < 23; j++, dd = dd * d % mod) ans[i] = (ans[i] + f[j] * dd % mod * binom[j][j - i]) % mod;
    return ans;
}
Poly F(int64_t n) {
    if (n < 10) {
        Poly ans(1);
        for (int64_t i = 1; i <= n; i++)
            if (i % 5) ans = ans * Poly(i, 1);
        return ans;
    }
    int64_t a = n / 10;
    Poly ret = F(5 * a), ans = ret * delt(ret, 5 * a);
    for (int64_t i = 10 * a + 1; i <= n; i++)
        if (i % 5) ans = ans * Poly(i, 1);
    return ans;
}
pll fac(int64_t n) {
    if (FAC.count(n)) return FAC[n];
    if (n <= 10) {
        pll ret = {0, 1};
        for (int64_t i = 1; i <= n; i++) ret.second *= i;
        while (ret.second % 5 == 0) ret.first++, ret.second /= 5;
        return FAC[n] = ret;
    }
    pll ret = fac(n / 5);
    return FAC[n] = {ret.first + n / 5, ret.second * F(n)(0) % mod};
}
int128_t Binom(int64_t n, int64_t m) {
    if (n < m) return 0;
    pll p1 = fac(n), p2 = fac(m), p3 = fac(n - m);
    return Pow(5, p1.first - p2.first - p3.first) * p1.second % mod * Inv((int128_t)p2.second * p3.second % mod) % mod;
}

int dfnt = 0;
void dfs(int p, bool lim, int64_t dist = 0, int pre = -1) {
    if (lim && dist * v[p] > MAX) return;
    id[dfni[p] = ++dfnt] = p;
    for (auto i : graph[p])
        if (i.first != pre) dfs(i.first, lim, dist + i.second, p);
    dfno[p] = dfnt;
    return;
}
void dp(void) {
    memset(f, 0, sizeof(f));
    auto merge = [](pll& a, pll b) { return a = (a.first == b.first ? pll{a.first, a.second + b.second} : max(a, b)); };
    if (w[id[1]] <= M) f[1][w[id[1]]] = {v[id[1]], 1};
    for (int i = 1; i < dfnt; i++)
        for (int x = id[i + 1], j = 0; j <= M; j++)
            if (f[i][j].second) {
                if (j + w[x] <= M) merge(f[i + 1][j + w[x]], {f[i][j].first + v[x], f[i][j].second});
                merge(f[dfno[x]][j], f[i][j]);
            }
    return;
}

void solve(void) {
    int n = read();
    M = read(), K = read(), MAX = read<int64_t>();
    for (int i = 1; i <= n; i++) w[i] = read();
    for (int i = 1; i <= n; i++) v[i] = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read(), c = read();
        graph[x].emplace_back(y, c), graph[y].emplace_back(x, c), edges[i] = {x, y, c};
    }
    int64_t maxV = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        dfnt = 0, dfs(i, false), dp();
        for (int i = 0; i <= M; i++) maxV = max(maxV, f[dfnt][i].first);
    }
    for (int i = 1; i <= n; i++) {
        dfnt = 0, dfs(i, true), dp();
        int64_t tot = 0;
        for (int i = 0; i <= M; i++)
            if (f[dfnt][i].first == maxV) tot += f[dfnt][i].second;
        ans = (ans + Binom(tot, K)) % mod;
    }
    auto merge = [](pll a, pll b) { return a.first == b.first ? pll{a.first, a.second + b.second} : max(a, b); };
    for (int i = 1, x, y, c; i < n; i++) {
        tie(x, y, c) = edges[i];
        dfnt = 0, dfs(x, true, c, y), dp();
        g[0] = f[dfnt][0];
        for (int i = 1; i <= M; i++) g[i] = merge(g[i - 1], f[dfnt][i]);
        dfnt = 0, dfs(y, true, c, x), dp();
        int64_t tot = 0;
        for (int i = 0; i <= M; i++)
            if (f[dfnt][i].first + g[M - i].first == maxV) tot += f[dfnt][i].second * g[M - i].second;
        ans = (ans + mod - Binom(tot, K)) % mod;
    }
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < 23; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
