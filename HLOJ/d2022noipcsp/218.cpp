/**
 * @file 218.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
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
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::putch;
using IO::read;
using IO::write;

bool mem1;

#define maxn 200005
#define mod 1000000007

vector<int> graph[maxn];
int dep[maxn], son[maxn];
int64_t F[maxn], *f[maxn], LAZ[maxn], *laz[maxn], g[maxn][2];
vector<int64_t> h[maxn];

void pushDown(int p, int d) {
    if (laz[p][d] == 1) return;
    f[p][d] = f[p][d] * laz[p][d] % mod;
    if (d + 1 < dep[p]) laz[p][d + 1] = laz[p][d + 1] * laz[p][d] % mod;
    laz[p][d] = 1;
    return;
}
void dfs1(int p, int pre = 0) {
    dep[p] = 1, son[p] = 0;
    for (auto i : graph[p])
        if (i != pre) {
            dfs1(i, p), dep[p] = max(dep[p], dep[i] + 1);
            if (dep[i] > dep[son[p]]) son[p] = i;
        }
    return;
}
int dfnt;
void dfs2(int p, int pre = 0) {
    f[p] = &F[++dfnt], laz[p] = &LAZ[dfnt], f[p][0] = laz[p][0] = 1;
    if (son[p]) dfs2(son[p], p);
    for (auto i : graph[p]) {
        if (i == pre || i == son[p]) continue;
        dfs2(i, p);
        int64_t s1 = 1, s2 = 1;
        for (int j = 0; j < dep[i]; j++) {
            pushDown(p, j + 1), pushDown(i, j);
            s1 = (s1 + f[p][j + 1]) % mod;
            f[p][j + 1] = (f[p][j + 1] * s2 + f[i][j] * s1) % mod;
            s2 = (s2 + f[i][j]) % mod;
        }
        if (dep[i] + 1 < dep[p]) laz[p][dep[i] + 1] = laz[p][dep[i] + 1] * s2 % mod;
    }
    return;
}

void solve(void) {
    int n = read();
    for (int i = 1; i <= n; i++) graph[i].clear();
    for (int i = 1, x, y; i < n; i++) x = read(), y = read(), graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1);
    dfnt = 0;
    for (auto i : graph[1]) dfs2(i, 1);
    sort(graph[1].begin(), graph[1].end(), [&](int x, int y) { return dep[x] > dep[y]; });
    int m = graph[1].size();
    h[m].resize(1), h[m][0] = 1;
    for (int i = m - 1; ~i; i--) {
        int p = graph[1][i];
        h[i].resize(dep[p]), h[i][0] = f[p][0] + 1;
        for (int j = 1; j < dep[p]; j++) pushDown(p, j), h[i][j] = (h[i][j - 1] + f[p][j]) % mod;
        for (int j = 0; j < dep[p]; j++) h[i][j] = h[i][j] * h[i + 1][min(j, (int)h[i + 1].size() - 1)] % mod;
    }
    for (int i = 0; i < n; i++) g[i][0] = 1, g[i][1] = 0;
    int64_t ans = 1;
    for (int i = 0; i < m; i++) {
        int p = graph[1][i];
        int64_t sum = 1;
        for (int j = 0; j < dep[p]; j++) {
            ans = (ans + g[j][1] * f[p][j] % mod * h[i + 1][min(j, (int)h[i + 1].size() - 1)]) % mod;
            g[j][1] = (g[j][0] * f[p][j] + g[j][1] * sum) % mod, g[j][0] = g[j][0] * sum % mod;
            sum = (sum + f[p][j]) % mod;
        }
    }
    write(ans), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);
#endif
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