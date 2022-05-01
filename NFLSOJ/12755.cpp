/**
 * @file 12755.cpp
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

#define maxn 100005
#define maxlgn 20
#define mod 1000000007

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        p++;
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        p++;
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

int L, R, a[maxn], siz[maxn], use[maxn], fa[maxn][maxlgn], sum[maxn][maxlgn], dep[maxn];
bool vis[maxn];
vector<vector<int>> graph;

int Mod(int x) { return x >= mod ? x - mod : x; }

void dfs1(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (!vis[i] && i != pre) dfs1(i, p), siz[p] += siz[i];
    return;
}
pii dfs2(int p, int tot, int pre = -1) {
    pii ret = {numeric_limits<int>::max(), 0};
    int maxSon = 0;
    for (auto i : graph[p])
        if (!vis[i] && i != pre) ret = min(ret, dfs2(i, tot, p)), maxSon = max(maxSon, siz[i]);
    return min(ret, pii{max(maxSon, tot - siz[p]), p});
}
int findCenter(int x) { return dfs1(x), dfs2(x, siz[x]).second; }

void dfs3(int p, int delt, int dep = 1, int pre = -1) {
    FT.add(dep, delt);
    for (auto i : graph[p])
        if (!vis[i] && i != pre) dfs3(i, delt, dep + 1, p);
    return;
}
int64_t dfs4(int p, int dep = 1, int pre = -1) {
    if (dep + 1 > R) return 0;
    int64_t ret = FT.sum(R - dep - 1) - FT.sum(max(-1, L - dep - 2));
    for (auto i : graph[p])
        if (!vis[i] && i != pre) ret += dfs4(i, dep + 1, p);
    return use[p] = Mod(use[p] + ret % mod), ret;
}
void dfz(int p) {
    vis[p] = true, FT.add(0, +1);
    for (auto i : graph[p])
        if (!vis[i]) dfs3(i, +1);
    int64_t cnt = FT.sum(R - 1) - FT.sum(L - 2);
    for (auto i : graph[p])
        if (!vis[i]) dfs3(i, -1), cnt += dfs4(i), dfs3(i, +1);
    use[p] = Mod(use[p] + (cnt + (L == 1)) / 2 % mod);
    FT.add(0, -1);
    for (auto i : graph[p])
        if (!vis[i]) dfs3(i, -1);
    for (auto i : graph[p])
        if (!vis[i]) dfz(findCenter(i));
    return;
}

void dfs5(int p, int pre = 0) {
    fa[p][0] = pre, sum[p][0] = use[p], dep[p] = dep[pre] + 1;
    for (int i = 1; i < maxlgn; i++)
        fa[p][i] = fa[fa[p][i - 1]][i - 1], sum[p][i] = Mod(sum[p][i - 1] + sum[fa[p][i - 1]][i - 1]);
    for (auto i : graph[p])
        if (i != pre) dfs5(i, p);
    return;
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int ans = 0;
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) ans = Mod(ans + sum[x][i]), x = fa[x][i];
    if (x == y) return Mod(ans + use[x]);
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) ans = Mod(ans + Mod(sum[x][i] + sum[y][i])), x = fa[x][i], y = fa[y][i];
    return Mod(ans + Mod(sum[x][1] + use[y]));
}

void solve(void) {
    int n = read(), m = read();
    L = read(), R = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    graph.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int x = read();
        graph[x].push_back(i), graph[i].push_back(x);
    }
    dfz(findCenter(1)), dfs5(1);
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + 1LL * a[i] * use[i]) % mod;
    while (m--) {
        int x = read(), y = read();
        write(ans = (ans + read<int64_t>() * LCA(x, y)) % mod), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("sumsum.in", "r", stdin), freopen("sumsum.out", "w", stdout);
#endif
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